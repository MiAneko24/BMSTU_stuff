UNIT_CFLAGS := -lcheck -lpthread -lrt -lsubunit


lab_02.out: out/matrix.o out/base_matrix_class.o
	g++ -o $@ $^ $(UNIT_CFLAGS) 

out/%.o : src/%.cpp inc/*.h 
	mkdir -p out
	g++ -c $< -o $@ $(UNIT_CFLAGS)
