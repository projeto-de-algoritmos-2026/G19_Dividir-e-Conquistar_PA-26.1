CXX = g++
CXXFLAGS = -std=c++17 -O3 -ffast-math -march=native -Wall

# alvo principal
engine: main.o dividir_e_conquistar.o
	$(CXX) $(CXXFLAGS) -o engine main.o dividir_e_conquistar.o

main.o: main.cpp point.h
	$(CXX) $(CXXFLAGS) -c main.cpp

dividir_e_conquistar.o: dividir_e_conquistar.c++ point.h
	$(CXX) $(CXXFLAGS) -x c++ -c dividir_e_conquistar.c++ -o dividir_e_conquistar.o

clean:
	rm -f *.o engine
