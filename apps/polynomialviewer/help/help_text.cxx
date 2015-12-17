#include "help_text.hxx"

const std::string HELP_TEXT =
"\n\
Real curves of polynomials.\n\
\n\
Given a complex polynomial with real coefficients,\n\
\n\
    f: C --> C\n\
\n\
there is a set of curves on the domain which yield values of f(z)\n\
which are strictly real,\n\
\n\
    f: {curves in C} --> R\n\
\n\
To approximate these curves, choose a small epsilon and show only\n\
the portion of the surface for which\n\
\n\
    abs(imag(f(z))) < epsilon\n\
\n\
The coordinates plotted are\n\
\n\
    ( real part of z, imaginary part of z, real part of f(z) )\n\
\n\
The roots of f(z) are colored in red.\n\
\n\
Click on a number field then drag left/right to modify it, or use the\n\
keyboard.\n\
\n\
* order: The order of the polynomial (the highest power).\n\
\n\
* coefficient: Choose a coefficient then modify its value.\n\
\n\
* epsilon: As described above.\n\
\n\
* scale Re{f(z)}: Multiply the real part of f(z) by this value.\n\
\n\
* scale color: Change the color gradient around the roots.\n\
\n\
* resolution: The number of quads, width and height.\n\
\n\
* plane size: (Self-explanatory.)\n\
\n\
* plane fade: (Self-explanatory.)\n\
\n\
* axes: Show/hide the domain axes.\n\
\n\
Each mouse button changes the selected value at a different rate; left\n\
button is slowest and right button is fastest.\n\
\n\
The user interface elements (windows, input fields) were created with\n\
the fltk library (http://www.fltk.org).\n\
\n\
polynomialviewer is copyright (c) 2006 by James M. Lawrence.\n\
All rights reserved.\n\
<llmjjmll@gmail.com>\n\
                                                                        \n\
                                                                        \n\
" ;

const std::string & help_text()
{
    return HELP_TEXT ;
}

