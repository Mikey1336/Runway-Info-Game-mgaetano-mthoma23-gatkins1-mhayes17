#include "dist/json/json.h"
#include "dist/jsoncpp.cpp"
#include <fstream>
#include <iostream>
#include <cmath>

// https://stackoverflow.com/questions/55431552/how-to-iterate-over-a-json-in-json-for-modern-c for code in iterating through the json

using namespace std;

int info() {
    // Create json file called AirportData.json
    ifstream airportFile("../airportData.json", ifstream::binary);
    Json::Reader reader;
    Json::Value airport;
    reader.parse(airportFile, airport);
    cout << "<div>" << airport["name"].asString() << "</div>" << endl;

    // Create json file called metarData.json
    ifstream weatherFile("../metarData.json", ifstream::binary);
    Json::Reader weatherReader;
    Json::Value weather;
    weatherReader.parse(weatherFile, weather);

    // Print weather data for the given airport with formatting for html
    cout << "<div><h2>" << airport["ident"].asString() << "</h2></div>" << endl;
    cout << "<div><h1>" << airport["name"].asString() << "</h1></div>" << endl;
    cout << "<div><h2>" << weather["meta"]["timestamp"].asString() << "</h2></div>" << endl;

    int windDirection = weather["wind_direction"]["value"].asInt();
    int windSpeed = weather["wind_speed"]["value"].asInt();

    cout << "<div><p>" << "Wind direction: " << endl;
    cout << windDirection << " degrees at " << windSpeed << " kts" << "</p></div>" << endl;

    cout << "<div><h1>" << "Runways: " << "</div></h1>" << endl;
    cout << "<div><table>\n" << endl;

    for (int i = 0; i < airport["runways"].size(); i++) {
        // Calculate the difference in angles between the plane's direction and the wind for strip 1
        Json::Value currentRwy = airport["runways"][i];
        string rwy1 = currentRwy["le_ident"].asString();
        if (rwy1.size() == 3) {
            rwy1.resize(rwy1.size() - 1);
        }
        rwy1 += '0';
        int rwy1Heading = stoi(rwy1);
        int windAngle1 = windDirection - rwy1Heading;

        // Calcualte headwinds and crosswinds for the first strip
        double headwind1 = sin(windAngle1) * weather["wind_speed"]["value"].asInt();
        double crosswind1 = abs(cos(windAngle1) * weather["wind_speed"]["value"].asInt());

        // Print all the info for the first strip
        cout << "<tr><td>" << "Runway: " << currentRwy["le_ident"].asString() << "</td></tr>" << endl;
        if (headwind1 >= 0) {
            cout << "<tr><td>" << "Headwind: " << headwind1 << "</td></tr>" << endl;
        } else {
            cout << "<tr><td>" << "Tailwind: " << -headwind1 << "</td></tr>" << endl;
        }
        cout << "<tr><td>" << "Crosswind: " << crosswind1 << "</td></tr>" << endl;
        cout << "<tr><td>" << "Heading detT: " << currentRwy["le_heading_degT"].asString() << "</td></tr>" << endl;
        cout << "<tr><td>" << "Runway length: " << currentRwy["length_ft"].asString() << "</td></tr>" << endl;
        cout << "<tr><td>" << "Runway width: " << currentRwy["width_ft"].asString() << "</td></tr>" << endl;
        cout << "<tr><td>" << "Inverted runway: " << currentRwy["he_ident"].asString() << "</td></tr>" << endl;

        // Calculate the difference in angles between the plane's direction and the wind for strip 2
        string rwy2 = currentRwy["he_ident"].asString();
        if (rwy2.size() == 3) {
            rwy2.resize(rwy2.size() - 1);
        }
        rwy2 += '0';
        int rwy2Heading = stoi(rwy2);
        int windAngle2 = windDirection - rwy2Heading;

        // Calcualte headwinds and crosswinds for the second strip
        double headwind2 = sin(windAngle2) * windSpeed;
        double crosswind2 = abs(cos(windAngle2) * windSpeed);

        // Print all the info for the second strip
        cout << "<tr><td>" << "Runway: " << currentRwy["he_ident"].asString() << "</td></tr>" << endl;
        if (headwind2 >= 0) {
            cout << "<tr><td>" << "Headwind: " << headwind2 << "</td></tr>" << endl;
        } else {
            cout << "<tr><td>" << "Tailwind: " << -headwind2 << "</td></tr>" << endl;
        }
        cout << "<tr><td>" << "Crosswind: " << crosswind2 << "</td></tr>" << endl;
        cout << "<tr><td>" << "Heading detT: " << currentRwy["he_heading_degT"].asString() << "</td></tr>" << endl;
        cout << "<tr><td>" << "Runway length: " << currentRwy["length_ft"].asString() << "</td></tr>" << endl;
        cout << "<tr><td>" << "Runway width: " << currentRwy["width_ft"].asString() << "</td></tr>" << endl;
        cout << "<tr><td>" << "Inverted runway: " << currentRwy["le_ident"].asString() << "</td></tr>" << endl;
    }

    cout << "</table></div>" << endl;

    return 0;
}

