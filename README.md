# C-Display

### A pretty simple, and quite fast 2D graphical library for C & Terminal.

With it you can create amazing ASCII shapes in 
your terminal, first building the display matrix, on size of your current console
, then you can add multiple elements to it, just by calling appropriate functions, 
to finally build it - of course as buffer, my primary goal was to get rid of 
having to display thousands of lines -> better modify the display, 
and at the end of displaying, free the allocated memory.

Hardcoding No Mo.

To see example of usage, open `main.c`.
To test, simply run with `./run.sh`

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
- Color - Displays all shapes with their beautiful colors, I've managed to optimise
it, so it really changes color only if it is necessary, and it won't reset color
on every printing, as each shape must define it's color, there is no need to get
back to default color, so in my test bench, it's now 2.5x as fast, there is no
noticeable difference between Color or Mono mode when it comes to FPS. It just 
looks better, and allows you to create smooth animations, beautiful display models
or even games, like snake, or space invaders.
- Mono - This one is as fast as it can be. For example, the test bench took about 
19.6 seconds to complete in Color mode, but only 18.6 in Mono - it was 1.06x as fast,
because of how I managed to optimize color mode, there is no noticeable difference
between those two rendering modes, so i leave Mono mode only for ones who would 
really need it. There is only one call to `printf()` per all `buildDisplay()` 
and there are no calls to 'setColor()' or 'resetColor()' whatsoever, as it only 
displays every shape in terminal's default color.

For all available functions, please check declarations in `display.h`.

### Animate.h
This is a additional library, built on top of `display.h`. It provides simple 
animations as functions, take it with grain of salt - it exists mostly as POC, 
and to show possibilities of C-Display. It provides Inside-Out and Outside-In 
transition effects.

### Color.h
Provides functions for setting color in terminal, randomizing it, and getting 
back to default. Every color possible for console is a part of `enum Color`.