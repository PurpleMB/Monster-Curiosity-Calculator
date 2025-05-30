import json
import time
import asyncio
import aiohttp
import requests

base_url = "https://pokeapi.co/api/v2/"

def gather_species_data():
    species_url = f"{base_url}/pokemon-species"
    api_response = requests.get(species_url)

    if api_response.status_code != 200:
        print(f"API Request for species info failed. Error code {api_response.status_code}")
        return None
    
    species_data = api_response.json()
    return species_data

async def gather_pokemon_data(session, species_data):
    species_count = species_data["count"]
    tasks = []
    for poke_id in range(species_count):
        task = asyncio.create_task(get_pokemon_info(session, poke_id + 1))
        tasks.append(task)

    pokedex_data = await asyncio.gather(*tasks)
    return pokedex_data

async def get_pokemon_info(session, pokemon_id):
    poke_url = f"{base_url}/pokemon/{pokemon_id}"
    async with session.get(poke_url) as api_response:
        if api_response.status != 200:
            print(f"API Request for {pokemon_id} failed. Error code {api_response.status_code}")
            return None

        pokemon_data = await api_response.json()
        pruned_data = prune_pokemon_info(pokemon_data)
        return pruned_data

def prune_pokemon_info(pokemon_info):
    pruned_info = {}

    # basic identification info
    pruned_info["name"] = pokemon_info["name"]
    pruned_info["id"] = pokemon_info["id"]

    # size info
    pruned_info["weight(kg)"] = pokemon_info["weight"] / 10
    pruned_info["height(m)"] = pokemon_info["height"] / 10

    # base stat info
    poke_stats = {}
    stat_total = 0
    for stat in pokemon_info["stats"]:
        poke_stats[stat["stat"]["name"]] = stat["base_stat"]
        stat_total += stat["base_stat"]
    poke_stats["total"] = stat_total
    pruned_info["stats"] = poke_stats

    # typing info
    poke_types = {}
    poke_types["primary"] = pokemon_info["types"][0]["type"]["name"]
    if len(pokemon_info["types"]) > 1:
        poke_types["secondary"] = pokemon_info["types"][1]["type"]["name"]
    else:
        poke_types["secondary"] = "-"
    pruned_info["types"] = poke_types

    # ability info
    poke_abilities = {}
    abilities = ["-", "-", "-"]

    for ability in pokemon_info["abilities"]:
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
