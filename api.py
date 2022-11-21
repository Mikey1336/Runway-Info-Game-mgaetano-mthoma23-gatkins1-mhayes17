#!/usr/bin/env python
import requests
import sys
import json
from sys import argv

def getAirportData():
    # Create a variable to store the token to allow access to the airport data through the website
    fileIn = open("../tokens.txt")
    tokens = fileIn.read().split("\n")
    fileIn.close()

    id = sys.argv[1]
    # id = input("Enter airport icao: ")
    # id = id.strip().upper()[0:4]

    # This will be the data about the runways at the airport
    airportDataUrl = "https://airportdb.io/api/v1/airport/" + id + "?apiToken=" + tokens[0]

    # Read into json with the information from the given airport
    response1 = requests.get(airportDataUrl)
    jsonData = response1.json()

    # Copy all the data from jsonData into airportData.json
    with open('../airportData.json', 'w') as jsonFile:
        json.dump(jsonData, jsonFile)

    # This will be the data about the weather at the site of the airport
    metarDataUrl = "https://avwx.rest/api/metar/" + id + "?options=&airport=true&reporting=true&format=json&remove=&filter=&onfail=cache"
    headers = {
        'Authorization': 'BEARER ' + tokens[1]
    }

    # Read the data about the weather into jsonData
    response2 = requests.request('GET', metarDataUrl, headers=headers)
    jsonData = response2.json()

    # Copy all the data from jsonData into metarData.json
    with open('../metarData.json', 'w') as jsonFile:
        json.dump(jsonData, jsonFile)

    # If both files were read in right, return True
    return response1.status_code == 200 and response2.status_code == 200

print(getAirportData())
