This is a python script used to query [PokeAPI](https://pokeapi.co/) and refine down the obtained data. 
The data is saved to json files located at '../resources/jsons/', which are processed to form
the SQLite database that are primarily used by MCC.

Eventually, I would like to add Python integration to the C++ segment of the codebase to allow
this script to be re-run within the C++ program.
