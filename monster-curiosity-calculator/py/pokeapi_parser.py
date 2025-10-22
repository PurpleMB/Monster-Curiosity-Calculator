import json
import time
import asyncio
import aiohttp
import requests

async def request_json_async(session, request_url):
    try:
        async with session.get(request_url) as request_response:
            if request_response.status != 200:
                print(f"API request for '{request_url}' using session '{session}' failed")
                print(f"Error Code: {request_response.status_code}")
                return None
            return await request_response.json()
    except:
        print(f"Could not connect to '{request_url}' with session '{session}'")
        return None

def request_json_synced(request_url):
    try:
        request_response = requests.get(request_url)
        if request_response.status_code != 200:
            print(f"API request for '{request_url}' failed")
            print(f"Error Code: {request_response.status_code}")
            return None
        return request_response.json()
    except:
        print(f"Could not connect to '{request_url}'")
        return None

# A request for a general category of information returns a list of urls to entries of that category
def get_category_info(api_url, category_name, limit = 20000, offset = 0):
    query_url = f"{api_url}/{category_name}?limit={limit}&offset={offset}"

    category_info = request_json_synced(query_url)

    return category_info 

# Forms a map for converting raw ability names to pretty ability names
async def form_ability_map(session, ability_info):
    if(ability_info is None):
        print("Ability information not provided.")
        return None

    ability_map = {"-" : "None"}

    tasks = []
    for ability_entry in ability_info["results"]:
        task = asyncio.create_task(get_ability_names(session, ability_entry))
        tasks.append(task)
    ability_name_maps = await asyncio.gather(*tasks)

    for name_mapping in ability_name_maps:
        ability_map |= name_mapping

    return ability_map

# Creates the mapping of raw -> pretty name for a single ability
async def get_ability_names(session, ability_entry):
    raw_name = ability_entry["name"]

    ability_url = ability_entry["url"]
    ability_data = await request_json_async(session, ability_url)

    if(ability_data is None):
        print(f"Request for ability '{raw_name}' failed.")
        return {raw_name : raw_name}

    pretty_names = ability_data["names"]
    english_pretty_name = next((pretty_name["name"] for pretty_name in pretty_names if pretty_name["language"]["name"] == "en"), "")

    return {raw_name : english_pretty_name}

# Forms a map for converting version-groups to generations
# This is done because generation is simply a more commonly used data point
async def form_version_map(session, versions_info):
    if(versions_info is None):
        print("Versions information not provided.")
        return None

    versions_map = {}

    tasks = []
    for version_entry in versions_info["results"]:
        task = asyncio.create_task(get_version_info(session, version_entry))
        tasks.append(task)
    version_gen_maps = await asyncio.gather(*tasks)

    for version_mapping in version_gen_maps:
        versions_map |= version_mapping

    return versions_map

# Creates the mapping of version-group -> generation for a single version group
async def get_version_info(session, version_entry):
    version_name = version_entry["name"]

    version_url = version_entry["url"]
    version_data = await request_json_async(session, version_url)

    if(version_data is None):
        print(f"Request for version '{version_name}' failed.")
        return {version_name : version_name}

    generation_name = version_data["generation"]["name"]

    return {version_name : generation_name}

# This function takes in the list of urls generated in the above function.
# It generates asynchronous requests gathering the data for each one before
# gathering all request results.
# The return of this function is a fully pruned dictionary of information.
async def gather_monsters_data(session, monsters_info, ability_name_map, generation_map):
    if(monsters_info is None):
        print("Monsters information not provided.")
        return None

    tasks = []
    for monster_entry in monsters_info["results"]:
        task = asyncio.create_task(get_monster_data(session, monster_entry, ability_name_map, generation_map))
        tasks.append(task)
    monsters_data = await asyncio.gather(*tasks)

    return monsters_data

# This is a helper function responsible for compiling the data for one monster.
# It generates async requests for info about the monster, its overall species,
# and its form before passing all of that data to a pruning function.
# The return of this function is a dictionary of prepared info for one monster.
async def get_monster_data(session, monster_entry, ability_map, versions_map):
    monster_url = monster_entry["url"]
    monster_data = await request_json_async(session, monster_url)

    # Legends:ZA creatures are currently lacking data, ignore them for now
    if monster_data["id"] > 10277:
        return None

    species_url = monster_data["species"]["url"]
    species_data = await request_json_async(session, species_url)

    form_url = monster_data["forms"][0]["url"]
    form_data = await request_json_async(session, form_url)

    url_data = {
        "monster": monster_url,
        "species": species_url,
        "form": form_url
    }

    pruned_monster_data = prune_monster_info(species_data, monster_data, form_data, url_data, ability_map, versions_map)
    return pruned_monster_data
        
# This helper function is responsible for taking in the raw data of a
# monster, its form, and its species and then re-organizing and pruning that
# data to be convenient for later parsing into an SQL database.
def prune_monster_info(species_info, monster_info, form_info, url_info, ability_map, versions_map):
    pruned_info = {}


    # basic identification info
    pruned_info["name"] = monster_info["name"]
    pruned_info["dex_number"] = species_info["id"]
    #pruned_info["generation"] = species_info["generation"]["name"]
    version_group = form_info["version_group"]["name"]
    pruned_info["generation"] = versions_map[version_group]
    pruned_info["unique_id"] = monster_info["id"]
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
    pruned_info["monster_url"] = url_info["monster"]
    pruned_info["form_url"] = url_info["form"]

    # breeding/growth info
    pruned_info["growth_rate"] = species_info["growth_rate"]["name"]
    pruned_info["base_experience"] = monster_info["base_experience"]
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
    pruned_info["is_default"] = 1 if monster_info["is_default"] else 0
    pruned_info["is_baby"] = 1 if species_info["is_baby"] else 0
    pruned_info["is_legendary"] = 1 if species_info["is_legendary"] else 0
    pruned_info["is_mythical"] = 1 if species_info["is_mythical"] else 0
    
    # size info
    # This condition is for E-max Eternatuss, which has an unknown weight of "0", I am choosing to treat its weight as very large instead for more logical sorting compared to other known weights
    raw_weight = monster_info["weight"]
    if  raw_weight != 0:
        pruned_info["weight(kg)"] = raw_weight / 10
    else:
        pruned_info["weight(kg)"] = 9999.9
    pruned_info["height(m)"] = monster_info["height"] / 10
    
    # base stat info 
    base_stats = {}
    stat_total = 0
    for stat in monster_info["stats"]:
        base_stats[stat["stat"]["name"]] = stat["base_stat"]
        stat_total += stat["base_stat"]
    base_stats["total"] = stat_total
    pruned_info["stats"] = base_stats
    
    # typing info
    monster_types = {}
    monster_types["primary"] = monster_info["types"][0]["type"]["name"]
    if len(monster_info["types"]) > 1:
        monster_types["secondary"] = monster_info["types"][1]["type"]["name"]
    else:
        monster_types["secondary"] = "-"
    pruned_info["types"] = monster_types
    
    # ability info
    monster_abilities = {}
    abilities = ["-", "-", "-"]
    pretty_monster_abilities = {}
    pretty_abilities = ["None", "None", "None"]

    for ability in monster_info["abilities"]:
        ability_name = ability["ability"]["name"]
        # API contains erroneous duplicate abilities?
        if not ability_name in abilities:
            abilities[ability["slot"]-1] = ability_name

    monster_abilities["first"] = abilities[0]
    monster_abilities["second"] = abilities[1]
    monster_abilities["hidden"] = abilities[2]

    pretty_monster_abilities["first"] = ability_map[abilities[0]]
    pretty_monster_abilities["second"] = ability_map[abilities[1]]
    pretty_monster_abilities["hidden"] = ability_map[abilities[2]]

    pruned_info["abilities"] = monster_abilities
    pruned_info["pretty_abilities"] = pretty_monster_abilities
    

    return pruned_info


async def main():
    start_time = time.time()

    api_url = "https://pokeapi.co/api/v2"
    json_directory = "../resources/jsons/"

    # Gathers data to create map of raw ability names -> pretty ability names.
    # This could be done during the main info gathering sequence, but
    # doing it now is more simple to understand.
    ability_name = "ability"
    ability_info = get_category_info(api_url, ability_name)
    async with aiohttp.ClientSession() as session:
        ability_map = await form_ability_map(session, ability_info)

    ability_file_name = json_directory + "abilities.json"
    with open(ability_file_name, "w") as ability_file:
        json.dump(ability_map, ability_file, indent = 4)

    # Gathers data to create map of version-group -> generation.
    # Reasoning for doing this here is the same as for ability mapping.
    versions_name = "version-group"
    versions_info = get_category_info(api_url, versions_name)
    async with aiohttp.ClientSession() as session:
        versions_map = await form_version_map(session, versions_info)

    versions_file_name = json_directory + "versions.json"
    with open(versions_file_name, "w") as versions_file:
        json.dump(versions_map, versions_file, indent = 4)

    # Main information gathering takes place here. 
    monsters_name = "pokemon"
    monsters_info = get_category_info(api_url, monsters_name)
    async with aiohttp.ClientSession() as session:
        monsters_data = await gather_monsters_data(session, monsters_info, ability_map, versions_map)

    if(monsters_info is not None):
        # Prune entries that failed for any reason
        monsters_data = list(filter(None, monsters_data)) 

    monster_file_name = json_directory + "mccdata.json"
    with open(monster_file_name, "w") as monster_file:
        json.dump(monsters_data, monster_file, indent = 4)
    print(f"JSON data saved to '{json_directory}'")

    end_time = time.time()
    print(f"Time Taken: {end_time - start_time} seconds")

if __name__ == '__main__':
    asyncio.run(main())
