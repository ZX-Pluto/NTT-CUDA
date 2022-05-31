OBJS = nwc_ntt.o my_hexl.o
main: $(OBJS)
		g++ -o my_cfntt $(OBJS)
nwc_ntt.o: nwc_ntt.cpp my_hexl.h
		g++ -c nwc_ntt.cpp
my_hexl.o: my_hexl.cpp my_hexl.h
		g++ -c my_hexl.cpp
clean:
		rm my_cfntt $(OBJS)