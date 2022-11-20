# M4OEP-mgaetano-mthoma23-gatkins1-mhayes17
Welcome to the Runway program!

This program was created by Matt Gaetano, Matt Thomas, Gabe Atkins, and Mikey Hayes.

-In order to run this program you will need a python interpretor installed in your c++ compiler
as well as a freeGlut.dll in your project.  

The purpose of this program is to use the graphics module in two unique and different ways.  The first
aspect of the program is a game in which the user can select the correct runway to land on given some random 
wind conditions.  The second aspect is a window in which the user can select an airport using a four-digit
code and then be presented with real time information and a picture of the airport runway orientation.  The 
game works by generating a random wind speed and direction then calculates the optimal runway to land on 
depending on which way which runway faces the closest to the direction the wind is coming from.  Two runways 
are displayed along with 5 buttons; 4 representing each runway and 1 play button.  Clicking the play button 
is what calls the game function and then outputs the runway statistics to the console, it is then up to the 
user to click the button for the runway with the safest landing conditions.  

Module 4 concepts:
-Used OpenGL and GLUT frameworks 
-Drawing to draw buttons and runways
-Keyboard Listener to enter program from start
-Mouse listeners to select menu options and game choices
-Button and Quad classes included
-Timer 

Future Additions:
This program has lots of possibilities for future improvements.  The first option for improvements would be
just an overall graphics and visual improvement such as background images and more aesthetically pleasing color 
selections.  Another idea would be to make the game a little more complicated and harder such as having to land 
an image of a plane on the correct runway.

Grade:
Main Program (40 pts)
Keyboard listener for start screen (10 pts)
Mouse listener for runways screen (10 pts)
Mouse listener for game screen (10 pts)
Quad class (10 pts)
Button class (10 pts)
Runway class (10 pts)
Airport class (10 pts)
~110 pts