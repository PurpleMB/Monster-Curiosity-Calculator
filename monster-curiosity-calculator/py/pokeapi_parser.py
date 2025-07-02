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
    form_url = dex_entry["url"]
    async with session.get(form_url) as form_response:
        if form_response.status != 200:
            print(f"API Request for {dex_entry["name"]} failed. Error code {api_response.status_code}")
            return None
        form_data = await form_response.json()

    species_url = form_data["species"]["url"]
    async with session.get(species_url) as species_response:
        if species_response.status != 200:
            print(f"API Request for {form_data["species"]["name"]} failed. Error code {species_response.status_code}")
            return None
        species_data = await species_response.json()

    pruned_species_data = prune_pokemon_info(species_data,form_data)
    return pruned_species_data
        

def prune_pokemon_info(species_info, form_info):
    pruned_info = {}


    # basic identification info
    pruned_info["name"] = form_info["name"]
    pruned_info["dex_number"] = species_info["id"]
    pruned_info["generation"] = species_info["generation"]["name"]
    pruned_info["unique_id"] = form_info["id"]
    pruned_info["form_switchable"] = species_info["forms_switchable"]
    pruned_info["color"] = species_info["color"]["name"]
    pruned_info["shape"] = species_info["shape"]["name"]

    # breeding/growth info
    pruned_info["growth_rate"] = species_info["growth_rate"]["name"]
    pruned_info["base_experience"] = form_info["base_experience"]
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
    pruned_info["is_default"] = form_info["is_default"]
    pruned_info["is_baby"] = species_info["is_baby"]
    pruned_info["is_legendary"] = species_info["is_legendary"]
    pruned_info["is_mythical"] = species_info["is_mythical"]
    
    # size info
    pruned_info["weight(kg)"] = form_info["weight"] / 10
    pruned_info["height(m)"] = form_info["height"] / 10
    
    # base stat info
    poke_stats = {}
    stat_total = 0
    for stat in form_info["stats"]:
        poke_stats[stat["stat"]["name"]] = stat["base_stat"]
        stat_total += stat["base_stat"]
    poke_stats["total"] = stat_total
    pruned_info["stats"] = poke_stats
    
    # typing info
    poke_types = {}
    poke_types["primary"] = form_info["types"][0]["type"]["name"]
    if len(form_info["types"]) > 1:
        poke_types["secondary"] = form_info["types"][1]["type"]["name"]
    else:
        poke_types["secondary"] = "-"
    pruned_info["types"] = poke_types
    
    # ability info
    poke_abilities = {}
    abilities = ["-", "-", "-"]

    for ability in form_info["abilities"]:
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
