#include "help_text.hxx"

const std::string HELP_TEXT =
"\n\
Welcome to four-dimensional polytopes, the analogue of three-\n\
dimensional polyhedra.\n\
\n\
Dragging the left mouse button in the camera window rotates the\n\
polytope in 3D. Likewise the right mouse button rotates in 4D.\n\
\n\
Click on a number field then drag left/right to modify it, or use the\n\
keyboard.\n\
\n\
The spacebar cycles through the current stored configurations, if any\n\
are present.\n\
\n\
* file: Load a new polytope.  The formats accepted are described in\n\
README.topeviewer.\n\
\n\
* camera pos: Change the camera's z-axis position.  Set this to zero\n\
for the effect of being \"on\" the 3-sphere.\n\
\n\
* camera fov: Change the camera's field of view, in degrees.\n\
\n\
* slide color: Shift the hue of all colors.\n\
\n\
* ball radius: Change the size of the balls enclosing the points.\n\
\n\
* tube radius: Change the thickness of the tubes representing edges.\n\
\n\
* clip balls: Show balls which fall within this range of distances\n\
from the origin.\n\
\n\
* clip edges: Show edges whose vertices fall within this range of\n\
distances from the origin.\n\
\n\
* edge lengths: Show edges whose lengths fall within this range.\n\
\n\
* inversion: Move between stereographic and orthographic projections.\n\
The point at infinity is the reciprocal of this value.\n\
\n\
Each mouse button changes the selected value at a different rate; left\n\
button is slowest and right button is fastest.\n\
\n\
You may save the current state by pressing ENTER, which adds a\n\
configuration line to the file.\n\
\n\
Keyboard functions:\n\
q --- quit the application\n\
e --- toggle stars\n\
r --- reset position\n\
f --- toggle full screen\n\
z --- toggle panel\n\
[, ] --- tube resolution\n\
a, s, d, w --- rotate stars\n\
\n\
Closing the camera window will also exit the application.\n\
\n\
Mouse sensitivity may be adjusted with the \"-s\" command-line option.\n\
Default is 0.75 (measured in milliradians per pixel).\n\
\n\
The 'c' key toggles \"Hopf rotations,\" explained in README.4d.\n\
\n\
The stars represent real astronomical data.\n\
\n\
The user interface elements (windows, input fields) were created with\n\
the fltk library (http://www.fltk.org).\n\
\n\
topeviewer is copyright (c) 2006 by James M. Lawrence.\n\
All rights reserved.\n\
<llmjjmll@gmail.com>\n\
                                                                        \n\
                                                                        \n\
                                                                        \n\
                                                                        \n\
                                                                        \n\
" ;

const std::string & help_text()
{
    return HELP_TEXT ;
}

