UNIT_CFLAGS := -lcheck -lpthread -lrt -lsubunit


lab_02.out: out/matrix.o
	g++ -o $@ $^ $(UNIT_CFLAGS) 

out/%.o : src/%.cpp inc/*.h 
	mkdir -p out
	g++ -c $< -o $@ $(UNIT_CFLAGS)
