CFLAGS := -Wall -Werror -Wvla -pedantic -lm
OBJ := out/spline.o out/main.o out/scan.o out/polynomNewton.o

lab_3.out : $(OBJ) inc/*.h
	gcc $(CFLAGS) $^ -o $@

out/%.o : src/%.c inc/*.h
	mkdir -p out
	gcc $(CFLAGS) -c $< -o $@