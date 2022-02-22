CFLAGS := -Wall -Werror -Wvla -pedantic
OBJ := out/polynoms.o out/main.o

lab_2.out : $(OBJ) inc/polynoms.h
	gcc $(CFLAGS) $^ -o $@

out/%.o : src/%.c inc/*.h
	mkdir -p out
	gcc $(CFLAGS) -c $< -o $@