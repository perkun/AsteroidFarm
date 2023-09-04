#!/bin/python

import os
import json
import copy

with open('compile_commands.json', 'r') as file:
    cmpdb = json.load(file)


outCmpDb = []

for entry in cmpdb:
    outCmpDb.append(entry)

    file, extension = os.path.splitext(entry["file"])

    # exclude vendor and tests folders
    if "vendor" in file or "tests" in file:
        continue

    if extension == ".cpp":
        newEntry = copy.deepcopy(entry)
        newEntry["file"] = file + ".h"
        newEntry["output"] = ""
        outCmpDb.append(newEntry)

with open("compile_commands.json", "w") as outFile:
    json.dump(outCmpDb, outFile)
