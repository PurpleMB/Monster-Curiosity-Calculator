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
    if ability_info is None:
        print("Ability information not provided.")
        return None

    tasks = []
    for ability_entry in ability_info["results"]:
        task = asyncio.create_task(get_ability_names(session, ability_entry))
        tasks.append(task)
    ability_name_maps = await asyncio.gather(*tasks)

    ability_map = {"-" : "None"}
    for name_mapping in ability_name_maps:
        ability_map |= name_mapping

    return ability_map

# Creates the mapping of raw -> pretty name for a single ability
async def get_ability_names(session, ability_entry):
    raw_name = ability_entry["name"]

    ability_url = ability_entry["url"]
    ability_data = await request_json_async(session, ability_url)

    if ability_data is None:
        print(f"Request for ability '{raw_name}' failed.")
        return {raw_name : raw_name}

    pretty_names = ability_data["names"]
    english_pretty_name = next((pretty_name["name"] for pretty_name in pretty_names if pretty_name["language"]["name"] == "en"), "")

    return {raw_name : english_pretty_name}

# Forms a map for converting version-groups to generations
# This is done because generation is simply a more commonly used data point
async def form_version_map(session, versions_info):
    if versions_info is None:
        print("Versions information not provided.")
        return None

    tasks = []
    for version_entry in versions_info["results"]:
        task = asyncio.create_task(get_version_gen(session, version_entry))
        tasks.append(task)
    version_gen_maps = await asyncio.gather(*tasks)

    versions_map = {}
    for version_mapping in version_gen_maps:
        versions_map |= version_mapping

    return versions_map

# Creates the mapping of version-group -> generation for a single version group
async def get_version_gen(session, version_entry):
    version_name = version_entry["name"]

    version_url = version_entry["url"]
    version_data = await request_json_async(session, version_url)

    if version_data is None:
        print(f"Request for version '{version_name}' failed.")
        return {version_name : version_name}

    generation_name = version_data["generation"]["name"]

    return {version_name : generation_name}

# Creates tasks to form individual monster entries and compiles them into a list
# Filters out failed entries before returning list
async def gather_monsters_data(session, monsters_info, ability_name_map, generation_map):
    if monsters_info is None:
        print("Monsters information not provided.")
        return None

    tasks = []
    for monster_entry in monsters_info["results"]:
        task = asyncio.create_task(get_monster_data(session, monster_entry, ability_name_map, generation_map))
        tasks.append(task)
    monsters_data = await asyncio.gather(*tasks)

    # Prune entries that failed for any reason
    monsters_data = list(filter(None, monsters_data)) 

    return monsters_data

# Obtains all required data about monster before it down to form a dictionary entry
async def get_monster_data(session, monster_entry, ability_map, versions_map):
    # Some monsters, particularly new ones, will have incomplete info and not possess information about their form, species, etc.
    monster_url = monster_entry["url"]
    try:
        monster_data = await request_json_async(session, monster_url)
        if monster_data is None:
            return None
    except:
        return None

    try:
        species_url = monster_data["species"]["url"]
        species_data = await request_json_async(session, species_url)
        if species_data is None:
            return None
    except:
        return None

    try:
        form_url = monster_data["forms"][0]["url"]
        form_data = await request_json_async(session, form_url)
        if species_data is None:
            return None
    except:
        return None

    pretty_name = {
        "pretty_name" : form_monster_pretty_name(species_data, form_data)
    }

    monster_pruned_data = prune_monster_data(monster_data, ability_map)
    species_pruned_data = prune_species_data(species_data)
    form_pruned_data = prune_form_data(form_data, versions_map)

    url_data = {
        "monster_url": monster_url,
        "species_url": species_url,
        "form_url": form_url
    }

    combo_pruned_data = pretty_name | monster_pruned_data | species_pruned_data | form_pruned_data | url_data

    return combo_pruned_data

# Forms a "pretty" name for the monster, which requires different data depending on if the monster is a variant of an existing monster
def form_monster_pretty_name(species_data, form_data):
    pretty_name = ""

    # Base form API entries have a pretty name in the species data
    if form_data["id"] == species_data["id"]:
        pretty_name = next((name["name"] for name in species_data["names"] if name["language"]["name"] == "en"), "")
    # Monster variants require their more-specific name held in the form data
    else:
        try:
            pretty_name = next((name["name"] for name in form_data["names"] if name["language"]["name"] == "en"), "")
        # This is here to handle Koraidon/Miraidon, which for some reason don't have English pretty names in their form name data.
        except:
            pretty_base_name = ""
            for species_name in species_data["names"]:
                if(species_name["language"]["name"] == "en"):
                    pretty_base_name = species_name["name"]
            pretty_form_name = ""
            for form_name in form_data["form_names"]:
                if(form_name["language"]["name"] == "en"):
                    pretty_form_name = form_name["name"]
            pretty_name = f"{pretty_base_name} ({pretty_form_name})"

    # Some characters need to be replaced due to ImGui's character system
    pretty_name = pretty_name.replace("%", "%%")
    pretty_name = pretty_name.replace(u"\u2018", "\'")
    pretty_name = pretty_name.replace(u"\u2019", "\'")
    pretty_name = pretty_name.replace(u"\u2640", " (F)")
    pretty_name = pretty_name.replace(u"\u2642", " (M)")

    return pretty_name

def prune_monster_data(monster_data, ability_map):
    pruned_data = {}

    pruned_data["name"] = monster_data["name"]
    pruned_data["unique_id"] = monster_data["id"]
    pruned_data["base_experience"] = monster_data["base_experience"]

    # Converting booleans to 0/1 as that plays nicer with the SQLite database
    pruned_data["is_default"] = int(monster_data["is_default"])
 
    # BST isn't in API data and must be manually calculate
    stat_total = 0
    for stat in monster_data["stats"]:
        stat_name = stat["stat"]["name"]
        stat_value = stat["base_stat"]

        pruned_data[stat_name] = stat_value
        stat_total += stat_value
    pruned_data["base_stat_total"] = stat_total

    # I am forming the database to uses "-" instead of nulls for non-values
    pruned_data["primary_type"] = monster_data["types"][0]["type"]["name"]
    try:
        pruned_data["secondary_type"] = monster_data["types"][1]["type"]["name"]
    except:
        pruned_data["secondary_type"] = "-"

    # Abilities require consulting the map to get pretty names
    abilities = ["-", "-", "-"]
    for ability in monster_data["abilities"]:
        ability_name = ability["ability"]["name"]
        # This check is here because some API entries have abilties repeated for some reason
        if not ability_name in abilities:
            abilities[ability["slot"]-1] = ability_name
    pruned_data["first_ability"]  = abilities[0]
    pruned_data["second_ability"] = abilities[1]
    pruned_data["hidden_ability"] = abilities[2]

    pruned_data["pretty_first_ability"] = ability_map[abilities[0]]
    pruned_data["pretty_second_ability"] = ability_map[abilities[1]]
    pruned_data["pretty_hidden_ability"] = ability_map[abilities[2]]

    # API uses 1/10th m/kg as its units. I want just 1 m/kg.
    pruned_data["height(m)"] = monster_data["height"] / 10
    # This condition is specifically for E-Max Eternatus, which logically should be sorted as having a very high weight instead of a very low weight.
    if monster_data["weight"] != 0:
        pruned_data["weight(kg)"] = monster_data["weight"] / 10
    else:
        pruned_data["weight(kg)"] = 9999.9

    return pruned_data


def prune_species_data(species_data):
    pruned_data = {}

    pruned_data["dex_number"] = species_data["id"]
    pruned_data["color"] = species_data["color"]["name"]
    pruned_data["shape"] = species_data["shape"]["name"]

    pruned_data["growth_rate"] = species_data["growth_rate"]["name"]
    pruned_data["base_happiness"] = species_data["base_happiness"]
    pruned_data["catch_rate"] = species_data["capture_rate"]
    pruned_data["hatch_counter"] = species_data["hatch_counter"]
    pruned_data["gender_rate"] = species_data["gender_rate"]

    # Converting booleans to 0/1 as that plays nicer with the SQLite database
    pruned_data["dimorphic"] = int(species_data["has_gender_differences"])
    pruned_data["is_baby"] = int(species_data["is_baby"])
    pruned_data["is_legendary"] = int(species_data["is_legendary"])
    pruned_data["is_mythical"] = int(species_data["is_mythical"])
    pruned_data["form_switchable"] = int(species_data["forms_switchable"])

    # I am forming the database to uses "-" instead of nulls for non-values
    pruned_data["primary_egg_group"] = species_data["egg_groups"][0]["name"]
    try:
        pruned_data["secondary_egg_group"] = species_data["egg_groups"][1]["name"]
    except:
        pruned_data["secondary_egg_group"] = "-"

    return pruned_data


def prune_form_data(form_data, versions_map):
    pruned_data = {}

    version_group = form_data["version_group"]["name"]
    pruned_data["generation"] = versions_map[version_group]

    return pruned_data

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

    monster_file_name = json_directory + "mccdata.json"
    with open(monster_file_name, "w") as monster_file:
        json.dump(monsters_data, monster_file, indent = 4)
    print(f"JSON data saved to '{json_directory}'")

    end_time = time.time()
    print(f"Time Taken: {end_time - start_time} seconds")

if __name__ == '__main__':
    asyncio.run(main())
