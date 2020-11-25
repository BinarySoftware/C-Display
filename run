# compiles all necessary source files
gcc -c -g color.c
gcc -c -g display.c
gcc -c -g animate.c
gcc -c -g main.c

# combines them to package
gcc -o C-Display main.o display.o animate.o color.o

# removes all .o files
rm main.o display.o animate.o color.o

# runs the package
./C-Display
