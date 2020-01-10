# C-Display

### A pretty simple, and quite fast 2D graphical library for C & Terminal.

With it you can create amazing ASCII shapes in 
your terminal, first building the display matrix, on size of your current console
, then you can add multiple elements to it, just by calling appropriate functions, 
to finally build it - of course as buffer, my primary goal was to get rid of 
having to display thousands of lines -> better modify the display, 
and at the end of displaying, free the allocated memory.

Hardcoding No Mo.

To see example of usage, open `main.c`

### Display.h
This is the main library. It provides all necessary elements to run C-Display.
It provides many advantages over printing hardcoded string literals:

- calculable shapes: provide dimensions, important points, char, color, and it 
will automatically calculate and add your shape to buffer, what's more, shapes
can be complex, and still display properly, with appropriate colors. 
- overlaying shapes - with that i've implemented adding and subtracting shapes, 
just like in way more advanced libraries, the last shape added stays on top.
- buffer screen building - you can simply update your screen, no need to print
another, and another, and so on screens just to update one point
- forgivable - if shape passes out of screen bounds, it will be simply cut to
bounds
- lightweight - no need to explain that.
- automated screen sizing to dimensions of your current console instance -> 
possibility to adjust shapes based on screen size

There are two modes of rendering:
- Color - Displays all shapes with their beautiful colors, but because of how
primitive this method has to be to actually work in terminal, it takes more CPU
time, still, there is almost no use case for high-FPS graphics in terminal, 
and this library is targeted mostly to create nice screens, and not advanced 
animations. Still, for ex. Snake game should run fine.
- Mono - This one is <b>really</b> fast, compared to Color mode. For example, the
test bench took about 47.182 seconds to complete in Color mode, but only 18.652
in Mono - it was 2.53x as fast, due to how rendering is constructed - there is 
only one call to `printf()` and there are no calls to 'setColor()' or 
'resetColor()' whatsoever, as it only displays every shape in terminal's default
 color.

For all available functions, please check declarations in `display.h`.

### Animate.h
This is a additional library, built on top of `display.h`. It provides simple 
animations as functions, take it with grain of salt - it exists mostly as POC, 
and to show possibilities of C-Display. It provides Inside-Out and Outside-In 
transition effects.

### Color.h
Provides functions for setting color in terminal, randomizing it, and getting 
back to default. Every color possible for console is a part of `enum Color`.