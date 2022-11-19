#include "Quad.h"
#include "graphics.h"
#include "runway.h"
#include <string>
#include <iostream>
#include <cmath>
#include "airport.h"
#include <vector>


using namespace std;



Quad::Quad() {
    fill = {0, 0, 0};
    center = {0, 0};
    width = 50;
    height = 50;
}

Quad::Quad(color fill, point center, unsigned int width, unsigned int height) {
    this->fill = fill;
    this->center = center;
    this->width = width;
    this->height = height;
}

int Quad::getCenterX() const {
    return center.x;
}

int Quad::getLeftX() const {
    return center.x - (width / 2);
}

int Quad::getRightX() const {
    return center.x + (width / 2);
}

int Quad::getCenterY() const {
    return center.y;
}

int Quad::getTopY() const {
    return center.y - (height / 2);
}

int Quad::getBottomY() const {
    return center.y + (height / 2);
}

point Quad::getCenter() const {
    return center;
}

double Quad::getRed() const {
    return fill.red;
}

double Quad::getGreen() const {
    return fill.green;
}

double Quad::getBlue() const {
    return fill.blue;
}

color Quad::getFill() const {
    return fill;
}

unsigned int Quad::getWidth() const {
    return width;
}

unsigned int Quad::getHeight() const {
    return height;
}

void Quad::setColor(double red, double green, double blue) {
    fill = {red, green, blue};
}

void Quad::setColor(color fill) {
    this->fill = fill;
}

void Quad::move(int deltaX, int deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}

void Quad::resize(unsigned int width,unsigned int height) {
    this->width = width;
    this->height = height;
}

void Quad::setRunway(int newRunway) {
    selectedRunway = newRunway;
}

int Quad::getRunway() const {
    return selectedRunway;
}

void Quad::draw(int screen) const {
    //if enum == start screen, display start screen
    if (screen == startScreen) {
        glBindTexture(GL_TEXTURE_2D, 0);
        glColor3f(0, 0, 1);
        string displayString = "PRESS 's' TO ENTER RUNWAY EDUCATION PROGRAM";
        glRasterPos2f(130, 100);
        int len = displayString.length();
        string lenString;
        int i;

        for (i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, displayString[i]);
        }
        //if enum == runways screen, display runways screen
    } else if (screen == runwaysScreen) {
        // Don't forget to set the color to the fill field
        // Set drawing color to fill color
        glColor3f(fill.red, fill.green, fill.blue);
        // Draw rectangle
        glBegin(GL_QUADS);
        // Draw center point
        glVertex2i(getLeftX(), getTopY());
        glVertex2i(getLeftX(), getBottomY());
        glVertex2i(getRightX(), getBottomY());
        glVertex2i(getRightX(), getTopY());
        // End quad
        glEnd();
        //if enum == end screen, display end screen
    } else if (screen == endScreen) {
        glBindTexture(GL_TEXTURE_2D, 0);
        glColor3f(0, 0, 1);
        string displayString = "YOU HAVE COMPLETED THE GAME. CONGRATULATIONS";
        glRasterPos2f(90, 100);
        int len = displayString.length();
        string lenString;
        int i;
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, displayString[i]);
        }
        //if enum == presto no button, remove the button
        //if enum == presto button, set enum to confettify screen and draw again.
    } else if (screen == prestoNoButton || screen == prestoButton) {
        if (screen == prestoNoButton) {
            glColor3f(0.0f, 0.0f, 0.0f);
        } else {
            screen = runwaysScreen;
            draw(screen);
        }

    } else if (screen == gameStart) {
        glBindTexture(GL_TEXTURE_2D, 0);
        glColor3f(0, 0, 1);
        string displayString1 = "WIND IS COMING FROM SOME DIRECTION AT SOME SPEED";
        string displayString2 = "USE THE ARROW KEYS TO CHOOSE THE CORRECT RUNWAY TO LAND ON";
        glRasterPos2f(80, 100);
        int len1 = displayString1.length();
        int i;
        for (i = 0; i < len1; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, displayString1[i]);
        }

        glRasterPos2f(40, 120);
        int len2 = displayString2.length();
        for (i = 0; i < len2; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, displayString2[i]);
        }
    }

    else if (screen == gameScreen) {

        string runwayUp = "RUNWAY 13";
        string runwayLeft = "RUNWAY 9";
        string runwayDown = "RUNWAY 31";
        string runwayRight = "RUNWAY 27";

        if (getRunway() == 1) {

            glColor3d(198 / 255.0, 192 / 255.0, 107 / 255.0);

            glBegin(GL_QUADS);
            glVertex2f(100, 200);
            glVertex2f(450, 200);
            glVertex2f(450, 300);
            glVertex2f(100, 300);
            glEnd();

//            x' = x*cos(t) - y*sin(t)
//            y' = x*sin(t) + y*cos(t)
            double angle = 0.698132;
            glBegin(GL_QUADS);
            glVertex2f(500 - (100 * cos(angle) - 200 * sin(angle)) - 178,
                       500 - (100 * sin(angle) + 200 * cos(angle)) + 115);
            glVertex2f(500 - (450 * cos(angle) - 200 * sin(angle)) - 178,
                       500 - (450 * sin(angle) + 200 * cos(angle)) + 115);
            glVertex2f(500 - (450 * cos(angle) - 300 * sin(angle)) - 178,
                       500 - (450 * sin(angle) + 300 * cos(angle)) + 115);
            glVertex2f(500 - (100 * cos(angle) - 300 * sin(angle)) - 178,
                       500 - (100 * sin(angle) + 300 * cos(angle)) + 115);
            glEnd();

            glColor3d(0, 0, 0);
            glBegin(GL_LINES);
            glVertex2f(100 - (100 * cos(angle) - 200 * sin(angle)), 135);
            glVertex2f(100 - (100 * cos(angle) - 200 * sin(angle)) + 57.4533332339, 135 + 48.2090707265);
            glEnd();

            glBegin(GL_TRIANGLE_STRIP);
            glVertex2f(100 - (100 * cos(angle) - 200 * sin(angle)) + 57.4533332339 + 12.8557521937
                     , 135 + 48.2090707265 - 15.3208888624);
            glVertex2f(100 - (100 * cos(angle) - 200 * sin(angle)) + 57.4533332339 - 12.8557521937
                    , 135 + 48.2090707265 + 15.3208888624);
            glVertex2f(100 - (100 * cos(angle) - 200 * sin(angle)) + 57.4533332339 + 16.0696902422
                    , 135 + 48.2090707265 + 19.151111078);
            glEnd();

            glColor3f(0, 1, 0);
            glRasterPos2f(80, 100);
            int lenUp = runwayUp.length();
            int i;
            for (i = 0; i < lenUp; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayUp[i]);
            }
            glColor3f(1, 0, 0);
            glRasterPos2f(25, 240);
            int lenLeft = runwayLeft.length();
            for (i = 0; i < lenLeft; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayLeft[i]);
            }
            glColor3f(1, 0, 0);
            glRasterPos2f(265, 400);
            int lenDown = runwayDown.length();
            for (i = 0; i < lenDown; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayDown[i]);
            }
            glColor3f(1, 0, 0);
            glRasterPos2f(400, 180);
            int lenRight = runwayRight.length();
            for (i = 0; i < lenRight; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayRight[i]);
            }

        }
        else if (getRunway() == 2) {

            glColor3d(198 / 255.0, 192 / 255.0, 107 / 255.0);

            glBegin(GL_QUADS);
            glVertex2f(100, 200);
            glVertex2f(450, 200);
            glVertex2f(450, 300);
            glVertex2f(100, 300);
            glEnd();

//            x' = x*cos(t) - y*sin(t)
//            y' = x*sin(t) + y*cos(t)
            double angle = 0.698132;
            glBegin(GL_QUADS);
            glVertex2f(500 - (100 * cos(angle) - 200 * sin(angle)) - 178,
                       500 - (100 * sin(angle) + 200 * cos(angle)) + 115);
            glVertex2f(500 - (450 * cos(angle) - 200 * sin(angle)) - 178,
                       500 - (450 * sin(angle) + 200 * cos(angle)) + 115);
            glVertex2f(500 - (450 * cos(angle) - 300 * sin(angle)) - 178,
                       500 - (450 * sin(angle) + 300 * cos(angle)) + 115);
            glVertex2f(500 - (100 * cos(angle) - 300 * sin(angle)) - 178,
                       500 - (100 * sin(angle) + 300 * cos(angle)) + 115);
            glEnd();

            glColor3d(0, 0, 0);
            glBegin(GL_LINES);
            glVertex2f(425, 250);
            glVertex2f(350, 250);
            glEnd();

            glBegin(GL_TRIANGLE_STRIP);
            glVertex2f(350, 230);
            glVertex2f(350, 270);
            glVertex2f(325, 250);
            glEnd();

            glColor3f(1, 0, 0);
            glRasterPos2f(80, 100);
            int lenUp = runwayUp.length();
            int i;
            for (i = 0; i < lenUp; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayUp[i]);
            }
            glColor3f(1, 0, 0);
            glRasterPos2f(25, 240);
            int lenLeft = runwayLeft.length();
            for (i = 0; i < lenLeft; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayLeft[i]);
            }
            glColor3f(1, 0, 0);
            glRasterPos2f(265, 400);
            int lenDown = runwayDown.length();
            for (i = 0; i < lenDown; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayDown[i]);
            }
            glColor3f(0, 1, 0);
            glRasterPos2f(400, 180);
            int lenRight = runwayRight.length();
            for (i = 0; i < lenRight; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayRight[i]);
            }
        } else if (getRunway() == 3) {

            glColor3d(198 / 255.0, 192 / 255.0, 107 / 255.0);

            glBegin(GL_QUADS);
            glVertex2f(100, 200);
            glVertex2f(450, 200);
            glVertex2f(450, 300);
            glVertex2f(100, 300);
            glEnd();

//            x' = x*cos(t) - y*sin(t)
//            y' = x*sin(t) + y*cos(t)
            double angle = 0.698132;
            glBegin(GL_QUADS);
            glVertex2f(500 - (100 * cos(angle) - 200 * sin(angle)) - 178,
                       500 - (100 * sin(angle) + 200 * cos(angle)) + 115);
            glVertex2f(500 - (450 * cos(angle) - 200 * sin(angle)) - 178,
                       500 - (450 * sin(angle) + 200 * cos(angle)) + 115);
            glVertex2f(500 - (450 * cos(angle) - 300 * sin(angle)) - 178,
                       500 - (450 * sin(angle) + 300 * cos(angle)) + 115);
            glVertex2f(500 - (100 * cos(angle) - 300 * sin(angle)) - 178,
                       500 - (100 * sin(angle) + 300 * cos(angle)) + 115);
            glEnd();

            glColor3d(0, 0, 0);
            glBegin(GL_LINES);
            glVertex2f(340 - (100 * cos(angle) - 200 * sin(angle)), 342);
            glVertex2f(340 - (100 * cos(angle) - 200 * sin(angle)) - 57.4533332339, 342 - 48.2090707265);
            glEnd();

            glBegin(GL_TRIANGLE_STRIP);
            glVertex2f(340 - (100 * cos(angle) - 200 * sin(angle)) - 57.4533332339 + 12.8557521937
                       ,342 - 48.2090707265 - 15.3208888624);
            glVertex2f(340 - (100 * cos(angle) - 200 * sin(angle)) - 57.4533332339 - 12.8557521937
                    ,342 - 48.2090707265 + 15.3208888624);
            glVertex2f(340 - (100 * cos(angle) - 200 * sin(angle)) - 57.4533332339 - 16.0696902422
                    ,342 - 48.2090707265 - 19.151111078);
            glEnd();

            glColor3f(1, 0, 0);
            glRasterPos2f(80, 100);
            int lenUp = runwayUp.length();
            int i;
            for (i = 0; i < lenUp; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayUp[i]);
            }
            glColor3f(1, 0, 0);
            glRasterPos2f(25, 240);
            int lenLeft = runwayLeft.length();
            for (i = 0; i < lenLeft; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayLeft[i]);
            }
            glColor3f(0, 1, 0);
            glRasterPos2f(265, 400);
            int lenDown = runwayDown.length();
            for (i = 0; i < lenDown; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayDown[i]);
            }
            glColor3f(1, 0, 0);
            glRasterPos2f(400, 180);
            int lenRight = runwayRight.length();
            for (i = 0; i < lenRight; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayRight[i]);
            }
        } else if (getRunway() == 4) {

            glColor3d(198 / 255.0, 192 / 255.0, 107 / 255.0);

            glBegin(GL_QUADS);
            glVertex2f(100, 200);
            glVertex2f(450, 200);
            glVertex2f(450, 300);
            glVertex2f(100, 300);
            glEnd();

//            x' = x*cos(t) - y*sin(t)
//            y' = x*sin(t) + y*cos(t)
            double angle = 0.698132;
            glBegin(GL_QUADS);
            glVertex2f(500 - (100 * cos(angle) - 200 * sin(angle)) - 178,
                       500 - (100 * sin(angle) + 200 * cos(angle)) + 115);
            glVertex2f(500 - (450 * cos(angle) - 200 * sin(angle)) - 178,
                       500 - (450 * sin(angle) + 200 * cos(angle)) + 115);
            glVertex2f(500 - (450 * cos(angle) - 300 * sin(angle)) - 178,
                       500 - (450 * sin(angle) + 300 * cos(angle)) + 115);
            glVertex2f(500 - (100 * cos(angle) - 300 * sin(angle)) - 178,
                       500 - (100 * sin(angle) + 300 * cos(angle)) + 115);
            glEnd();

            glColor3d(0, 0, 0);
            glBegin(GL_LINES);
            glVertex2f(125, 250);
            glVertex2f(200, 250);
            glEnd();

            glBegin(GL_TRIANGLE_STRIP);
            glVertex2f(200, 230);
            glVertex2f(200, 270);
            glVertex2f(230, 250);
            glEnd();

            glColor3f(1, 0, 0);
            glRasterPos2f(80, 100);
            int lenUp = runwayUp.length();
            int i;
            for (i = 0; i < lenUp; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayUp[i]);
            }
            glColor3f(0, 1, 0);
            glRasterPos2f(25, 240);
            int lenLeft = runwayLeft.length();
            for (i = 0; i < lenLeft; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayLeft[i]);
            }
            glColor3f(1, 0, 0);
            glRasterPos2f(265, 400);
            int lenDown = runwayDown.length();
            for (i = 0; i < lenDown; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayDown[i]);
            }
            glColor3f(1, 0, 0);
            glRasterPos2f(400, 180);
            int lenRight = runwayRight.length();
            for (i = 0; i < lenRight; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, runwayRight[i]);
            }
        }
    } else if (screen == gameEnd) {
        srand(time(NULL));
        double windDirection = rand() % 360 + 1;
        //Random wind Speed
        double windSpeed = rand() % 31;
        //Create Runways
        Runway r13("r13", windSpeed , windDirection, 130);
        Runway r31("r31", windSpeed, windDirection, 310);
        Runway r9("r9", windSpeed, windDirection, 90);
        Runway r27("r27", windSpeed, windDirection, 270);

        vector<Runway> runways;
        runways.push_back(r13);
        runways.push_back(r31);
        runways.push_back(r9);
        runways.push_back(r27);
        double lowestVal = abs(r13.getDirectionDiff());
        string correct;
        for (Runway r : runways){
            if(abs(r.getDirectionDiff()) < lowestVal){
                lowestVal = r.getDirectionDiff();
                correct = r.getName();
                r.setLanding(true);
            }
        }
    }


    else if (screen == infoScreen) {
        glColor3d(198 / 255.0, 192 / 255.0, 107 / 255.0);

        glBegin(GL_LINE_LOOP);

        vector<vector<double>> points;
        points = getRwyPoints();
        for (int i = 0; i < points.size(); i++) {
            double x = points[i][0];
            double y = points[i][1];



        }


    }
}