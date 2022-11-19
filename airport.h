#include "dist/json/json.h"
#include "dist/jsoncpp.cpp"
#include <fstream>
#include <iostream>
#include <cmath>

// https://stackoverflow.com/questions/55431552/how-to-iterate-over-a-json-in-json-for-modern-c for code in iterating through the json

using namespace std;

struct point2D {
    double x;
    double y;

    /* Constructors */
    point2D();
    point2D(double x, double y);

    /* Overloaded Operator */
    friend std::ostream& operator << (std::ostream& outs, const point2D &p);
};

vector<vector<double>> getRwyPoints() {
//    string icao;
//    cout << "Enter ICAO: ";
//    getline(cin, icao);
    string icao = "KBTV";
    string command = "python ../api.py " + icao;
    system(command.c_str());

    // Create json file called AirportData.json
    ifstream airportFile("../airportData.json", ifstream::binary);
    Json::Reader reader;
    Json::Value airport;
    reader.parse(airportFile, airport);

    // Create json file called metarData.json
    ifstream weatherFile("../metarData.json", ifstream::binary);
    Json::Reader weatherReader;
    Json::Value weather;
    weatherReader.parse(weatherFile, weather);

    int windDirection = weather["wind_direction"]["value"].asInt();
    int windSpeed = weather["wind_speed"]["value"].asInt();

    cout << "Wind is " << windDirection << " at " << windSpeed << endl;

    double latitude0 = stod(airport["runways"][0]["le_latitude_deg"].asString());
    double longitude0 = stod(airport["runways"][0]["le_longitude_deg"].asString());

    vector<vector<double>> rwyPoints;

    for (int i = 0; i < airport["runways"].size(); i++) {
        // Calculate the difference in angles between the plane's direction and the wind for strip 1
        Json::Value currentRwy = airport["runways"][i];
        string rwy1 = currentRwy["le_ident"].asString();
        int rwyWidth = stoi(currentRwy["width_ft"].asString()) / 50;
        int rwyLength = stoi(currentRwy["length_ft"].asString()) / 50;

        if (rwy1.size() == 3) {
            rwy1.resize(rwy1.size() - 1);
        }
        rwy1 += '0';
        int rwyHeading = stoi(rwy1);

        cout << "Runway " << i + 1 << ": " << rwy1 << endl;

        cout << "Points: ";

        double originY = (stod(currentRwy["le_latitude_deg"].asString()) - latitude0) * 1000;
        double originX = (stod(currentRwy["le_longitude_deg"].asString()) - longitude0) * 1000;

        double p1x = originX - rwyWidth * cos(rwyHeading - 90);
        double p1y = originY + rwyWidth * sin(rwyHeading - 90);
        rwyPoints.push_back({p1x, p1y});

        rwyPoints.push_back({originX, originY});
//        double p2x = originX;
//        double p2y = originY;

        rwyPoints.push_back({originX - rwyLength * sin(rwyHeading - 90), originY + rwyLength * cos(rwyHeading - 90)});
//        double p3x = originX - rwyLength * sin(rwyHeading - 90);
//        double p3y = originY + rwyLength * cos(rwyHeading - 90);

        rwyPoints.push_back({p1x - rwyLength * sin(rwyHeading - 90), p1y + rwyLength * cos(rwyHeading - 90)});
//        double p4x = p1x - rwyLength * sin(rwyHeading - 90);
//        double p4y = p1y + rwyLength * cos(rwyHeading - 90);

//        cout << p1x << ", " << p1y << endl;
//        cout << p2x << ", " << p2y << endl;
//        cout << p3x << ", " << p3y << endl;
//        cout << p4x << ", " << p4y << endl;
        cout << "Width: " << rwyWidth << endl;
        cout << "Length: " << rwyLength << endl << endl;
    }

    double lowestX = 0, lowestY = 0;
    for (int i = 0; i < rwyPoints.size(); i++) {
        lowestX = min(rwyPoints[i][0], lowestX);
        lowestY = min(rwyPoints[i][1], lowestY);
        cout << rwyPoints[i][0] << ", " << rwyPoints[i][1] << endl;
    }

    for (int i = 0; i < rwyPoints.size(); i++) {
        rwyPoints[i][0] -= lowestX;
        rwyPoints[i][1] -= lowestY;
        cout << rwyPoints[i][0] << ", " << rwyPoints[i][1] << endl;
    }

    for (int i = 0; i < rwyPoints.size(); i++) {
        if (i % 4 == 0) {
            cout << "Runway " << i / 4 + 1 << endl;
        }
        cout << rwyPoints[i][0] << ", " << rwyPoints[i][1] << endl;
    }

    return rwyPoints;
}