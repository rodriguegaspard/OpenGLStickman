#! /bin/sh
gcc -Wall -pedantic -Wno-unused-result -D _DEFAULT_SOURCE -O2 main.c actions.c ppm.o axes.o init.c lumiere.c VM_init.o -lm -lGL -lGLU -lglut -no-pie -o test
./test
