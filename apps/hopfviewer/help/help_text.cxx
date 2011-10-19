#include "help_text.hxx"

const std::string HELP_TEXT =
"\n\
Welcome to the four-dimensional torus.\n\
\n\
Dragging the left mouse button in the camera window rotates the\n\
torus in 3D. Likewise the right mouse button rotates in 4D.\n\
\n\
Click on a number field then drag left/right to modify it, or use the\n\
keyboard.\n\
\n\
* strips/squares:\n\
\n\
strips: Create this number of skinny rectangles across the domain,\n\
preserving the rectangles by skewing.\n\
\n\
squares: Automatically adjust the skew and resolution parameters\n\
to make squares, up to this number.  The field will turn red when\n\
the value is insufficient.\n\
\n\
Strips are suited for fibrous tori and squares for solid tori.\n\
\n\
To disable the strips/squares feature and control resolution\n\
manually (as well as skew), set the value to zero.\n\
\n\
* subdomain: Use a rectangular subset of the domain defined by\n\
these two numbers.\n\
\n\
* winding: For the pair (m,n) the surface winds m times around the\n\
torus in one direction and n times in the other direction.  A full\n\
torus is formed when (m,n) are relatively prime integers.\n\
\n\
* ratio angle: Change the ratio of the radii of the generating\n\
circles.\n\
\n\
* inversion: Move between stereographic and orthographic\n\
projections.  The point at infinity is the reciprocal of this value.\n\
\n\
* scale: Scale the torus as a whole.\n\
\n\
* gap: Modify the spacing between quads.\n\
\n\
* resolution: The number of quads, width and height, of the full\n\
domain.  (Modifiable when strips/squares is disabled.)\n\
\n\
* skew: Lift one edge of the domain while keeping the opposite\n\
edge fixed.  (Modifiable when strips/squares is disabled.)\n\
\n\
* align 4D: Convert the right mouse button to yield 4D rotations\n\
aligned with the torus itself.\n\
\n\
* hide back: Hide quads whose gray side would be showing.\n\
\n\
Each mouse button changes the selected value at a different rate; left\n\
button is slowest and right button is fastest.\n\
\n\
Keyboard functions:\n\
q --- quit the application\n\
e --- toggle stars\n\
r --- reset position\n\
f --- toggle full screen\n\
z --- toggle panel\n\
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
hopfviewer is copyright (c) 2006 by James M. Lawrence.\n\
All rights reserved.\n\
<quixoticsycophant@gmail.com>\n\
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

