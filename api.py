#!/usr/bin/env python
import json
import sys
import urllib.request

def getAirportData():
    # Create a variable to store the token to allow access to the airport data through the website
    fileIn = open("../../tokens.txt")
    tokens = fileIn.read().split("\n")
    fileIn.close()

    # Allow the user to enter an airport code, then get the website with the id of the passed code
    id = sys.argv[1]
    # id = input("Enter airport icao: ")
    # id = id.strip().upper()[0:4]
    # print(id);

    # This will be the data about the runways at the airport
    airportDataUrl = "https://airportdb.io/api/v1/airport/" + id + "?apiToken=" + tokens[0]

    # Read into json with the information from the given airport
    request1 = urllib.request.Request(airportDataUrl, headers={"User-Agent": "Mozilla/5.0"})
    with urllib.request.urlopen(request1) as response1:
        jsonData = json.loads(response1.read().decode("utf-8"))

    # Copy all the data from jsonData into airportData.json
    with open('airportData.json', 'w') as jsonFile:
        json.dump(jsonData, jsonFile)

    # This will be the data about the weather at the site of the airport
    metarDataUrl = "https://avwx.rest/api/metar/" + id + "?options=&airport=true&reporting=true&format=json&remove=&filter=&onfail=cache"
    headers = {
        'Authorization': 'BEARER ' + tokens[1],
        'User-Agent': 'Mozilla/5.0'
    }

    # Read the data about the weather into jsonData
    request2 = urllib.request.Request(metarDataUrl, headers=headers)
    with urllib.request.urlopen(request2) as response2:
        jsonData = json.loads(response2.read().decode("utf-8"))

    # Copy all the data from jsonData into metarData.json
    with open('metarData.json', 'w') as jsonFile:
        json.dump(jsonData, jsonFile)

    # If both files were read in right, return True
    return response1.getcode() == 200 and response2.getcode() == 200

print(getAirportData())
