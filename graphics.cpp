#include "graphics.h"
#include "Button.h"
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;
Button game({1, 0, 0}, {100, 100}, 100, 50, "Game");
Button info({1, 0, 0}, {400, 100}, 100, 50, "Runway Finder");


int screen = startScreen;



void init() {
    width = 500;
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

    // TODO: call the Button's draw method.

    game.draw(screen);
    info.draw(screen);

    glFlush();  // Render now
}



// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    if (key == 115){
        screen = confettifyScreen;
        game.draw(screen);
        info.draw(screen);
    }


    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {

}

void cursor(int x, int y) {
    // TODO: If the Button is overlapping with the (x, y) coordinate passed in, call the hover method. Otherwise, call the release method.
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
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    // TODO: If the left button is down and the cursor is overlapping with the Button, call the pressDown method. Otherwise, call the release method.
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

    }


    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && info.isOverlapping(x, y)) {

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
    wd = glutCreateWindow("Confettify!" /* title */ );

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

