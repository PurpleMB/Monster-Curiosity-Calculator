import json
import time
import asyncio
import aiohttp
import requests

base_url = "https://pokeapi.co/api/v2/"

def get_ability_urls():
    ability_url = f"{base_url}/ability?limit=500&offset=0"
    api_response = requests.get(ability_url)

    if api_response.status_code != 200:
        print(f"API Request for ability info failed. Error code {api_response.status_code}")
        return None

    ability_data = api_response.json()
    return ability_data

async def gather_ability_data(session, ability_data):
    tasks = []
    ability_map = {"-" : "None"}
    for ability_entry in ability_data["results"]:
        task = asyncio.create_task(get_ability_info(session, ability_entry, ability_map))
        tasks.append(task)

    await asyncio.gather(*tasks)
    return ability_map

async def get_ability_info(session, ability_entry, ability_map):
    ability_url = ability_entry["url"]
    async with session.get(ability_url) as ability_response:
        if ability_response.status != 200:
            print(f"API Request for {ability_entry["name"]} failed. Error code {ability_response.status_code}")
            return None
        ability_data = await ability_response.json()

    raw_name = ability_entry["name"]
    pretty_name = ""
    for ability_name in ability_data["names"]:
        if(ability_name["language"]["name"] == "en"):
            pretty_name = ability_name["name"]

    ability_map[raw_name] = pretty_name

def get_generation_urls():
    generation_url = f"{base_url}/generation?limit=20&offset=0"
    api_response = requests.get(generation_url)

    if api_response.status_code != 200:
        print(f"API Request for generation info failed. Error code {api_response.status_code}")
        return None

    generation_data = api_response.json()
    return generation_data

async def gather_generation_data(session, generation_data):
    tasks = []
    generation_map = {}
    for generation_entry in generation_data["results"]:
        task = asyncio.create_task(get_version_group_info(session, generation_entry, generation_map))
        tasks.append(task)

    await asyncio.gather(*tasks)
    return generation_map

async def get_version_group_info(session, generation_entry, generation_map):
    generation_url = generation_entry["url"]
    async with session.get(generation_url) as generation_response:
        if generation_response.status != 200:
            print(f"API Request for {generation_entry["name"]} failed. Error code {generation_response.status_code}")
            return None
        generation_data = await generation_response.json()

    for version_group in generation_data["version_groups"]:
        generation_map[version_group["name"]] = generation_data["name"]

# This function gathers the links for information on all pokemon.
# It does not query those links, but merely gathers them all in an array.
def gather_species_data():
    pokedex_url = f"{base_url}/pokemon?limit=100000&offset=0"
    api_response = requests.get(pokedex_url)

    if api_response.status_code != 200:
        print(f"API Request for dex info failed. Error code {api_response.status_code}")
        return None
    
    pokedex_data = api_response.json()
    return pokedex_data

# This function takes in the list of urls generated in the above function.
# It generates asynchronous requests gathering the data for each one before
# gathering all request results.
# The return of this function is a fully pruned dictionary of information.

async def gather_pokemon_data(session, species_data, ability_name_map, generation_map):
    tasks = []
    for dex_entry in species_data["results"]:
        task = asyncio.create_task(get_pokemon_info(session, dex_entry, ability_name_map, generation_map))
        tasks.append(task)

    pokedex_data = await asyncio.gather(*tasks)
    return pokedex_data

# This is a helper function responsible for compiling the data for one pokemon.
# It generates async requests for info about the pokemon, its overall species,
# and its form before passing all of that data to a pruning function.
# The return of this function is a dictionary of prepared info for one pokemon.
async def get_pokemon_info(session, dex_entry, ability_name_map, generation_map):
    poke_url = dex_entry["url"]
    async with session.get(poke_url) as poke_response:
        if poke_response.status != 200:
            print(f"API Request for {dex_entry["name"]} failed. Error code {poke_response.status_code}")
            return None
        poke_data = await poke_response.json()

    species_url = poke_data["species"]["url"]
    async with session.get(species_url) as species_response:
        if species_response.status != 200:
            print(f"API Request for {poke_data["species"]["name"]} failed. Error code {species_response.status_code}")
            return None
        species_data = await species_response.json()

    form_url = poke_data["forms"][0]["url"]
    async with session.get(form_url) as form_response:
        if form_response.status != 200:
            print(f"API Request for {poke_data["forms"][0]["url"]} failed. Error code {form_response.status_code}")
            return None
        form_data = await form_response.json()

    url_data = {
        "poke": poke_url,
        "species": species_url,
        "form": form_url
    }

    pruned_species_data = prune_pokemon_info(species_data, poke_data, form_data, url_data, ability_name_map, generation_map)
    return pruned_species_data
        
# This helper function is responsible for taking in the raw data of a
# pokemon, its form, and its species and then re-organizing and pruning that
# data to be convenient for later parsing into an SQL database.
def prune_pokemon_info(species_info, poke_info, form_info, url_info, ability_name_map, generation_map):
    pruned_info = {}


    # basic identification info
    pruned_info["name"] = poke_info["name"]
    pruned_info["dex_number"] = species_info["id"]
    #pruned_info["generation"] = species_info["generation"]["name"]
    version_group = form_info["version_group"]["name"]
    pruned_info["generation"] = generation_map[version_group]
    pruned_info["unique_id"] = poke_info["id"]
    pruned_info["form_switchable"] = 1 if species_info["forms_switchable"] else 0
    pruned_info["color"] = species_info["color"]["name"]
    pruned_info["shape"] = species_info["shape"]["name"]
    
    # pretty name generation
    pretty_name = ""
    if form_info["id"] == species_info["id"]:
        for species_name in species_info["names"]:
            if(species_name["language"]["name"] == "en"):
                pretty_name = species_name["name"]
    else:
        name_found = False
        for form_name in form_info["names"]:
            if(form_name["language"]["name"] == "en"):
                pretty_name = form_name["name"]
                name_found = True
        if not name_found:
            # this is only here for annoying Koraidon/Miraidon forms
            pretty_base_name = ""
            for species_name in species_info["names"]:
                if(species_name["language"]["name"] == "en"):
                    pretty_base_name = species_name["name"]
            pretty_form_name = ""
            for form_name in form_info["form_names"]:
                if(form_name["language"]["name"] == "en"):
                    pretty_form_name = form_name["name"]
            pretty_name = f"{pretty_base_name} ({pretty_form_name})"

    pretty_name = pretty_name.replace("%", "%%")
    pretty_name = pretty_name.replace(u"\u2018", "\'")
    pretty_name = pretty_name.replace(u"\u2019", "\'")
    pretty_name = pretty_name.replace(u"\u2640", " (F)")
    pretty_name = pretty_name.replace(u"\u2642", " (M)")
    pruned_info["pretty_name"] = pretty_name

    # API source info
    pruned_info["species_url"] = url_info["species"]
    pruned_info["poke_url"] = url_info["poke"]
    pruned_info["form_url"] = url_info["form"]

    # breeding/growth info
    pruned_info["growth_rate"] = species_info["growth_rate"]["name"]
    pruned_info["base_experience"] = poke_info["base_experience"]
    pruned_info["base_happiness"] = species_info["base_happiness"]
    pruned_info["catch_rate"] = species_info["capture_rate"]
    pruned_info["hatch_counter"] = species_info["hatch_counter"]
    pruned_info["gender_rate"] = species_info["gender_rate"]
    pruned_info["dimorphic"] = 1 if species_info["has_gender_differences"] else 0

    egg_groups = {}
    egg_groups["primary"] = species_info["egg_groups"][0]["name"]
    if len(species_info["egg_groups"]) > 1:
        egg_groups["secondary"] = species_info["egg_groups"][1]["name"]
    else:
        egg_groups["secondary"] = "-"
    pruned_info["egg_groups"] = egg_groups

    
    # classification info
    pruned_info["is_default"] = 1 if poke_info["is_default"] else 0
    pruned_info["is_baby"] = 1 if species_info["is_baby"] else 0
    pruned_info["is_legendary"] = 1 if species_info["is_legendary"] else 0
    pruned_info["is_mythical"] = 1 if species_info["is_mythical"] else 0
    
    # size info
    # This condition is for E-max Eternatuss, which has an unknown weight of "0", I am choosing to treat its weight as very large instead for more logical sorting compared to other known weights
    raw_weight = poke_info["weight"]
    if  raw_weight != 0:
        pruned_info["weight(kg)"] = raw_weight / 10
    else:
        pruned_info["weight(kg)"] = 9999.9
    pruned_info["height(m)"] = poke_info["height"] / 10
    
    # base stat info
    poke_stats = {}
    stat_total = 0
    for stat in poke_info["stats"]:
        poke_stats[stat["stat"]["name"]] = stat["base_stat"]
        stat_total += stat["base_stat"]
    poke_stats["total"] = stat_total
    pruned_info["stats"] = poke_stats
    
    # typing info
    poke_types = {}
    poke_types["primary"] = poke_info["types"][0]["type"]["name"]
    if len(poke_info["types"]) > 1:
        poke_types["secondary"] = poke_info["types"][1]["type"]["name"]
    else:
        poke_types["secondary"] = "-"
    pruned_info["types"] = poke_types
    
    # ability info
    poke_abilities = {}
    abilities = ["-", "-", "-"]
    pretty_poke_abilities = {}
    pretty_abilities = ["None", "None", "None"]

    for ability in poke_info["abilities"]:
        ability_name = ability["ability"]["name"]
        # API contains erroneous duplicate abilities?
        if not ability_name in abilities:
            abilities[ability["slot"]-1] = ability_name

    poke_abilities["first"] = abilities[0]
    poke_abilities["second"] = abilities[1]
    poke_abilities["hidden"] = abilities[2]

    pretty_poke_abilities["first"] = ability_name_map[abilities[0]]
    pretty_poke_abilities["second"] = ability_name_map[abilities[1]]
    pretty_poke_abilities["hidden"] = ability_name_map[abilities[2]]

    pruned_info["abilities"] = poke_abilities
    pruned_info["pretty_abilities"] = pretty_poke_abilities
    

    return pruned_info


async def main():
    start_time = time.time()

    ability_data = get_ability_urls()
    async with aiohttp.ClientSession() as session:
        ability_name_map = await gather_ability_data(session, ability_data)

    filename = "../data/abilities.json"
    with open(filename, "w") as file:
        json.dump(ability_name_map, file, indent = 4)

    generation_data = get_generation_urls()
    async with aiohttp.ClientSession() as session:
        generation_map = await gather_generation_data(session, generation_data)

    filename = "../data/generations.json"
    with open(filename, "w") as file:
        json.dump(generation_map, file, indent = 4)

    species_data = gather_species_data()
    async with aiohttp.ClientSession() as session:
        pokemon_data = await gather_pokemon_data(session, species_data, ability_name_map, generation_map)

    filename = "../data/mccdata.json"
    with open(filename, "w") as file:
        json.dump(pokemon_data, file, indent = 4)

    print(f"JSON data saved to '{filename}'")

    end_time = time.time()
    print(f"Time Taken: {end_time - start_time} seconds")

if __name__ == '__main__':
    asyncio.run(main())
