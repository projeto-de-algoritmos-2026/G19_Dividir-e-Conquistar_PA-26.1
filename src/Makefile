CXX = g++
CXXFLAGS = -std=c++17 -O3 -ffast-math -march=native -Wall -pthread

# alvo principal
engine: main.o dividir_e_conquistar.o
	$(CXX) $(CXXFLAGS) -o engine main.o dividir_e_conquistar.o

main.o: main.cpp point.h
	$(CXX) $(CXXFLAGS) -c main.cpp

dividir_e_conquistar.o: dividir_e_conquistar.cpp point.h
	$(CXX) $(CXXFLAGS) -c dividir_e_conquistar.cpp -o dividir_e_conquistar.o

clean:
	rm -f *.o engine
