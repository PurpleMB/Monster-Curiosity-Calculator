import json
import time
import asyncio
import aiohttp
import requests

base_url = "https://pokeapi.co/api/v2/"

def gather_species_data():
    pokedex_url = f"{base_url}/pokemon?limit=100000&offset=0"
    api_response = requests.get(pokedex_url)

    if api_response.status_code != 200:
        print(f"API Request for dex info failed. Error code {api_response.status_code}")
        return None
    
    pokedex_data = api_response.json()
    return pokedex_data

async def gather_pokemon_data(session, species_data):
    tasks = []
    for dex_entry in species_data["results"]:
        task = asyncio.create_task(get_pokemon_info(session, dex_entry))
        tasks.append(task)

    pokedex_data = await asyncio.gather(*tasks)
    return pokedex_data

async def get_pokemon_info(session, dex_entry):
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

    pruned_species_data = prune_pokemon_info(species_data, poke_data, form_data, url_data)
    return pruned_species_data
        

def prune_pokemon_info(species_info, poke_info, form_info, url_info):
    pruned_info = {}


    # basic identification info
    pruned_info["name"] = poke_info["name"]
    pruned_info["dex_number"] = species_info["id"]
    pruned_info["generation"] = species_info["generation"]["name"]
    pruned_info["unique_id"] = poke_info["id"]
    pruned_info["form_switchable"] = species_info["forms_switchable"]
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
    pruned_info["dimorphic"] = species_info["has_gender_differences"]

    egg_groups = {}
    egg_groups["primary"] = species_info["egg_groups"][0]["name"]
    if len(species_info["egg_groups"]) > 1:
        egg_groups["secondary"] = species_info["egg_groups"][1]["name"]
    else:
        egg_groups["secondary"] = "-"
    pruned_info["egg_groups"] = egg_groups

    
    # classification info
    pruned_info["is_default"] = poke_info["is_default"]
    pruned_info["is_baby"] = species_info["is_baby"]
    pruned_info["is_legendary"] = species_info["is_legendary"]
    pruned_info["is_mythical"] = species_info["is_mythical"]
    
    # size info
    pruned_info["weight(kg)"] = poke_info["weight"] / 10
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

    for ability in poke_info["abilities"]:
        abilities[ability["slot"]-1] = ability["ability"]["name"]

    poke_abilities["first"] = abilities[0]
    poke_abilities["second"] = abilities[1]
    poke_abilities["hidden"] = abilities[2]

    pruned_info["abilities"] = poke_abilities
    

    return pruned_info


async def main():
    start_time = time.time()

    species_data = gather_species_data()

    #pokemon_data = gather_pokemon_data(species_data)
    async with aiohttp.ClientSession() as session:
        pokemon_data = await gather_pokemon_data(session, species_data)

    filename = "./mccdata.json"
    with open(filename, "w") as file:
        json.dump(pokemon_data, file, indent = 4)

    print(f"JSON data saved to '{filename}'")

    end_time = time.time()
    print(f"Time Taken: {end_time - start_time} seconds")

if __name__ == '__main__':
    asyncio.run(main())
