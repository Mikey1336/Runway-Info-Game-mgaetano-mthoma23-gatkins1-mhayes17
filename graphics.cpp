#include "graphics.h"
#include "Button.h"
#include "Runway.h"
//#include "airport.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
using namespace std;

GLdouble width, height;
int wd;

//Buttons for runwaysScreen
Button game({1, 0, 0}, {100, 100}, 100, 50, "Game");
Button info({.133, .545, .133}, {400, 100}, 100, 50, "Runway Finder");
//Buttons for gameScreen
Button play({.1, .6, .1}, {300, 50}, 100, 50, "Play!");
Button br9({.3, .3, .3}, {85, 250}, 100, 50, "r9");
Button br27({.3, .3, .3}, {465, 250}, 100, 50, "r27");
Button br31({.3, .3, .3}, {450, 380}, 100, 50, "r31");
Button br13({.3, .3, .3}, {100, 100}, 100, 50, "r13");

enum screensEnum{
    startScreen,
    runwaysScreen,
    endScreen,
    gameScreen,
    infoScreen,
    prestoNoButton,
    prestoButton,
    gameStart,
};

screensEnum screen = startScreen;
string ans = "default";

//Function to run game
string gameR(){
    //Random Seed
    srand(time(NULL));
    //Random wind Direction
    double windDirection = rand() % 360 + 1;
    //Random wind Speed
    double windSpeed = rand() % 31;
    //Output start message
    cout << "*** Welcome to the Landing Game! ***" << endl;
    cout << "** Based on the image above, choose the runway safest to land on! **" << endl;
    //Out put wind stats
    cout << "Today's wind speed is: " << windSpeed << " mph" << endl;
    cout << "Today's wind is coming from: " << windDirection << " degrees" << endl;
    //Create Runways
    Runway r13("r13", windSpeed, windDirection, 130);
    Runway r31("r31", windSpeed, windDirection, 310);
    Runway r9("r9", windSpeed, windDirection, 90);
    Runway r27("r27", windSpeed, windDirection, 270);
    //Calculations for headwind/crosswind
    if (r13.getHeadWind() < 0) {
        cout << r13.getName() << " - Tailwind: " << r13.getHeadWind() * -1 << " mph, Crosswind: ";
        (r13.getCrossWind() < 0) ? (cout << r13.getCrossWind() * -1 << " mph from left" << endl) : (cout
                << r13.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r13.getName() << " - Headwind: " << r13.getHeadWind() << " mph, Crosswind: ";
        (r13.getCrossWind() < 0) ? (cout << r13.getCrossWind() * -1 << " mph from left" << endl) : (cout
                << r13.getCrossWind() << " mph from right" << endl);
    }
    if (r31.getHeadWind() < 0) {
        cout << r31.getName() << " - Tailwind: " << r31.getHeadWind() * -1 << " mph, Crosswind: ";
        (r31.getCrossWind() < 0) ? (cout << r31.getCrossWind() * -1 << " mph from left" << endl) : (cout
                << r31.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r31.getName() << " - Headwind: " << r31.getHeadWind() << " mph, Crosswind: ";
        (r31.getCrossWind() < 0) ? (cout << r31.getCrossWind() * -1 << " mph from left" << endl) : (cout
                << r31.getCrossWind() << " mph from right" << endl);
    }
    if (r9.getHeadWind() < 0) {
        cout << r9.getName() << " - Tailwind: " << r9.getHeadWind() * -1 << " mph, Crosswind: ";
        (r9.getCrossWind() < 0) ? (cout << r9.getCrossWind() * -1 << " mph from left" << endl) : (cout
                << r9.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r9.getName() << " - Headwind: " << r9.getHeadWind() << " mph, Crosswind: ";
        (r9.getCrossWind() < 0) ? (cout << r9.getCrossWind() * -1 << " mph from left" << endl) : (cout
                << r9.getCrossWind() << " mph from right" << endl);
    }
    if (r27.getHeadWind() < 0) {
        cout << r27.getName() << " - Tailwind: " << r27.getHeadWind() * -1 << " mph, Crosswind: ";
        (r27.getCrossWind() < 0) ? (cout << r27.getCrossWind() * -1 << " mph from left" << endl) : (cout
                << r27.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r27.getName() << " - Headwind: " << r27.getHeadWind() << " mph, Crosswind: ";
        (r27.getCrossWind() < 0) ? (cout << r27.getCrossWind() * -1 << " mph from left" << endl) : (cout
                << r27.getCrossWind() << " mph from right" << endl);
    }
    //DISPLAY direction diff between the way the wind is coming from and the direction the runway is facing
    cout << "r13: " << r13.getDirectionDiff() << endl;
    cout << "r31: " << r31.getDirectionDiff() << endl;
    cout << "r9: " << r9.getDirectionDiff() << endl;
    cout << "r27: " << r27.getDirectionDiff() << endl;
    //Add runways to vector
    vector<Runway> runways;
    runways.push_back(r13);
    runways.push_back(r31);
    runways.push_back(r9);
    runways.push_back(r27);
    //Find the runway with the difference between direction and wind direction and make that the correct answer
    double lowestVal = abs(r13.getDirectionDiff());
    string correct = "r13";
    for (Runway r: runways) {
        if (abs(r.getDirectionDiff()) < lowestVal) {
            lowestVal = r.getDirectionDiff();
            correct = r.getName();
            r.setLanding(true);
        }
    }
    //print select message
    cout << "* Based on the information, select the runway that would be optimal for landing? *" << endl;
    //return correct ans
    return correct;
}


void init() {
    width = 550;
    height = 500;
    srand(time(0));
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 0.1f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Switch statement to display different screens
    switch(screen) {
        //when screen is start print message to enter program
        case startScreen: {
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
            break;
        }

        //once in program and on runwaysScreen print buttons
        case runwaysScreen: {
            game.draw(screen);
            info.draw(screen);
            break;
        }

        //if game is clicked display game screen
        case gameScreen: {
            //draw first runway
            glColor3d(198 / 255.0, 192 / 255.0, 107 / 255.0);
            glBegin(GL_QUADS);
            glVertex2f(100, 200);
            glVertex2f(450, 200);
            glVertex2f(450, 300);
            glVertex2f(100, 300);
            glEnd();
            //draw second runway
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

            glBegin(GL_LINES);
            glVertex2f(425, 250);
            glVertex2f(350, 250);
            glEnd();

            glBegin(GL_TRIANGLE_STRIP);
            glVertex2f(350, 230);
            glVertex2f(350, 270);
            glVertex2f(325, 250);
            glEnd();

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

            glBegin(GL_LINES);
            glVertex2f(125, 250);
            glVertex2f(200, 250);
            glEnd();

            glBegin(GL_TRIANGLE_STRIP);
            glVertex2f(200, 230);
            glVertex2f(200, 270);
            glVertex2f(230, 250);
            glEnd();


            //draw buttons to select runway
            br9.draw(screen);
            br27.draw(screen);
            br31.draw(screen);
            br13.draw(screen);
            play.draw(screen);
            break;
        }

        //when info screen is clicked
        case infoScreen: {

           cout << "nice" << endl;
            break;
        }

        //when end screen is displayed
        case endScreen: {
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
            break;
        }
        case prestoNoButton: {

            break;
        }
    }


    glFlush();  // Render now
}




// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    if (key == 10 && screen == gameScreen) {

    }
    if (key == 115){
        screen = runwaysScreen;
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {

    switch(key) {

        case GLUT_KEY_RIGHT:
            screen = gameScreen;
            game.setRunway(2);
            game.draw(screen);
            break;
        case GLUT_KEY_UP:
            screen = gameScreen;
            game.setRunway(1);
            game.draw(screen);
            break;
        case GLUT_KEY_LEFT:
            screen = gameScreen;
            game.setRunway(4);
            game.draw(screen);
            break;
        case GLUT_KEY_DOWN:
            screen = gameScreen;
            game.setRunway(3);
            game.draw(screen);
            break;
    }

}

void cursor(int x, int y) {
    // If either Button is overlapping with the (x, y) coordinate passed in, call the hover method. Otherwise, call the release method.
    //Game cursor listener
    if (game.isOverlapping(x, y)) {
        game.hover();
    } else {
        game.release();
    }
    glutPostRedisplay();

    //Info Cursor listener
    if (info.isOverlapping(x, y)) {
        info.hover();
    } else {
        info.release();
    }
    glutPostRedisplay();

    //Runway Cursor Listeners
    if (br9.isOverlapping(x, y)) {
        br9.hover();
    } else {
        br9.release();
    }
    glutPostRedisplay();

    if (br27.isOverlapping(x, y)) {
        br27.hover();
    } else {
        br27.release();
    }
    glutPostRedisplay();

    if (br31.isOverlapping(x, y)) {
        br31.hover();
    } else {
        br31.release();
    }
    glutPostRedisplay();

    if (br13.isOverlapping(x, y)) {
        br13.hover();
    } else {
        br13.release();
    }
    glutPostRedisplay();

    if (play.isOverlapping(x, y)) {
        play.hover();
    } else {
        play.release();
    }
    glutPostRedisplay();

}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    //  If the left button is down and the cursor is overlapping with either Button, call the pressDown method. Otherwise, call the release method.
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && game.isOverlapping(x, y)) {
        game.pressDown();
    } else {
        game.release();
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && info.isOverlapping(x, y)) {
        info.pressDown();
    } else {
        info.release();
    }

//If left button is up and cursor is over either one call matching function
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && game.isOverlapping(x, y)) {
        screen = gameScreen;

    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && info.isOverlapping(x, y)) {
        screen = infoScreen;
        info.draw(screen);
    }

    //Mouse Listeners for the game
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && play.isOverlapping(x, y)) {
        play.pressDown();
    } else {
        play.release();
    }

    //ONCE PLAY BUTTON HAS BEEN CLICKED RUN GAME FUNCTION
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && play.isOverlapping(x, y)) {
        screen = gameScreen;
        ans = gameR();
        cout << ans << endl;
    }
    //Listeners for runway buttons
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && br9.isOverlapping(x, y)) {
        game.pressDown();
    } else {
        game.release();
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && br27.isOverlapping(x, y)) {
        game.pressDown();
    } else {
        game.release();
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && br13.isOverlapping(x, y)) {
        game.pressDown();
    } else {
        game.release();
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && br31.isOverlapping(x, y)) {
        game.pressDown();
    } else {
        game.release();
    }
    //if the correct button is clicked print winner and go to end screen
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && br9.isOverlapping(x,y) && ans == br9.getLabel()){
        cout << ans << endl;
        cout << "winner" << endl;
        screen = endScreen;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && br27.isOverlapping(x,y) && ans == br27.getLabel()){
        cout << ans << endl;
        cout << "winner" << endl;
        screen = endScreen;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && br13.isOverlapping(x,y) && ans == br13.getLabel()){
        cout << ans << endl;
        cout << "winner" << endl;
        screen = endScreen;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && br31.isOverlapping(x,y) && ans == br31.getLabel()){
        cout << ans << endl;
        cout << "winner" << endl;
        screen = endScreen;
    }

    glutPostRedisplay();

}

void timer(int dummy) {
    
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("RUNWAYS!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();

    return 0;
}

