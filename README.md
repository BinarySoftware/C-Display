# C-Display

A pretty simple, and quite fast C graphical library.

With it you can create amazing ASCII shapes in 
your terminal, first building the display, as a 2D array, then by adding
multiple elements to it, to finally build it - of course as buffer, my primary
goal was to get rid of having to display thousands of lines -> better modify
the display, and at the end of displaying, free the allocated memory.

To see example of usage, open `main.c`

#### Display.h
This is the main library. It provides all necessary elements to run C-Display.
It provides many advantages over printing hardcoded string literals:

- calculable shapes: provide dimensions, poins, char, and it will automatically
calculate and add your shape to buffer
- overlaying shapes - with that i've implemented adding and subtracting shapes, 
just like in way more advanced libraries
- buffer screen building - you can simply update your screen, no need to print
another, and another, and so on screens just to update one point
- forgivable - if shape passes out of screen bounds, it will be simply cut to
bounds
- lightweight - no need to explain that
- automated screen sizing to dimensions of your current console instance -> 
possibility to adjust shapes based on screen size

For all available functions, please check declarations in `display.h`.

#### Animate.h
This is a additional library, built on top of `display.h`. It provides simple 
animations as functions, take it with grain of salt - it exists mostly as POC, 
and to show possibilities of C-Display. It provides Inside-Out and Outside-In 
transition effects.