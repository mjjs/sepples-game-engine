libglad.a: glad.o
	llvm-ar-11 rc libglad.a glad.o

glad.o: src/glad.c include/glad/glad.h
	gcc -c -Iinclude -o $@ $<
