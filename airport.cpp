/*
#include "dist/json/json.h"
#include "dist/jsoncpp.cpp"
#include <fstream>
#include <iostream>
#include <cmath>
#include "game.cpp"

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <time.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// https://stackoverflow.com/questions/55431552/how-to-iterate-over-a-json-in-json-for-modern-c for code in iterating through the json

GLdouble width, height;
int wd;

int game();

void init();
void initGL();
void display();
void kbd(unsigned char key, int x, int y);
void kbdS(int key, int x, int y);

using namespace std;

int main(int argc, char* argv[]) {

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
    game();
    return 0;
}

int game(){

    cout << "*** Welcome to the Landing Game! ***" << endl;
    cout << "** Based on the image above, choose the runway safest to land on! **" << endl;

    //Random wind Direction
    srand(time(NULL));
    double windDirection = rand() % 360 +1;

    //Random wind Speed
    double windSpeed = rand() % 31;

    cout << "Today's wind speed is: " << windSpeed << " mph" << endl;
    cout << "Today's wind is coming from: " << windDirection << " degrees" << endl;

    //Create Runways
    Runway r13("r13", windSpeed , windDirection, 130);
    Runway r31("r31", windSpeed, windDirection, 310);
    Runway r9("r9", windSpeed, windDirection, 90);
    Runway r27("r27", windSpeed, windDirection, 270);

    if(r13.getHeadWind() < 0){
        cout << r13.getName() << " - Tailwind: " << r13.getHeadWind() * -1 << " mph, Crosswind: "; (r13.getCrossWind() < 0) ? (cout << r13.getCrossWind() * -1 << " mph from left" << endl) : (cout << r13.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r13.getName() << " - Headwind: " << r13.getHeadWind() << " mph, Crosswind: "; (r13.getCrossWind() < 0) ? (cout << r13.getCrossWind() * -1 << " mph from left" << endl) : (cout << r13.getCrossWind() << " mph from right" << endl);
    }
    if(r31.getHeadWind() < 0){
        cout << r31.getName() << " - Tailwind: " << r31.getHeadWind() * -1 << " mph, Crosswind: "; (r31.getCrossWind() < 0) ? (cout << r31.getCrossWind() * -1 << " mph from left" << endl) : (cout << r31.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r31.getName() << " - Headwind: " << r31.getHeadWind() << " mph, Crosswind: "; (r31.getCrossWind() < 0) ? (cout << r31.getCrossWind() * -1 << " mph from left" << endl) : (cout << r31.getCrossWind() << " mph from right" << endl);
    }
    if(r9.getHeadWind() < 0){
        cout << r9.getName() << " - Tailwind: " << r9.getHeadWind() * -1 << " mph, Crosswind: "; (r9.getCrossWind() < 0) ? (cout << r9.getCrossWind() * -1 << " mph from left" << endl) : (cout << r9.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r9.getName() << " - Headwind: " << r9.getHeadWind() << " mph, Crosswind: "; (r9.getCrossWind() < 0) ? (cout << r9.getCrossWind() * -1 << " mph from left" << endl) : (cout << r9.getCrossWind() << " mph from right" << endl);
    }
    if(r27.getHeadWind() < 0){
        cout << r27.getName() << " - Tailwind: " << r27.getHeadWind() * -1 << " mph, Crosswind: "; (r27.getCrossWind() < 0) ? (cout << r27.getCrossWind() * -1 << " mph from left" << endl) : (cout << r27.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r27.getName() << " - Headwind: " << r27.getHeadWind() << " mph, Crosswind: "; (r27.getCrossWind() < 0) ? (cout << r27.getCrossWind() * -1 << " mph from left" << endl) : (cout << r27.getCrossWind() << " mph from right" << endl);
    }


    cout << "r13: " << r13.getDirectionDiff() << endl;
    cout << "r31: " << r31.getDirectionDiff() << endl;
    cout << "r9: " << r9.getDirectionDiff() << endl;
    cout << "r27: " << r27.getDirectionDiff() << endl;

    vector<Runway> runways;
    runways.push_back(r13);
    runways.push_back(r31);
    runways.push_back(r9);
    runways.push_back(r27);

    double lowestVal = abs(r13.getDirectionDiff());
    string correct = "r13";
    for (Runway r : runways){
        if(abs(r.getDirectionDiff()) < lowestVal){
            lowestVal = r.getDirectionDiff();
            correct = r.getName();
            r.setLanding(true);
        }
    }

    cout << "* Based on the information, what runway would be optimal for landing? *"  << endl;
    string ans;
    cin >> ans;
    if (ans == correct){
        cout << "congrats!" << endl;
    }
    else{
        cout << "Oops! Wrong answer :(" << endl;
        cout << "The correct answer is " << correct << endl;
    }


        return 0;
}
void init() {
    width = 600;
    height = 600;

}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    /*
     * Draw here
    */


    //glVertex2d()


/*
void kbd(unsigned char key, int x, int y) {

    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    glutPostRedisplay();

}
void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            break;

        case GLUT_KEY_UP:
            break;

        case GLUT_KEY_LEFT:
            break;

        case GLUT_KEY_RIGHT:
            break;
    }
}
 */