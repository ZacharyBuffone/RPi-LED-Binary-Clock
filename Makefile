LED-Test: LED-Test.o DisplayManager.o FontGenerator.o PixelMatrix.o librgbmatrix.a
	g++ -Wall --std=c++11 -pthread LED-Test.o DisplayManager.o FontGenerator.o PixelMatrix.o librgbmatrix.a -o LED-Test
LED-Test.o: LED-Test.cpp
	g++ -Wall --std=c++11 LED-Test.cpp -c -o LED-Test.o

DisplayManager.o: DisplayManager.cpp DisplayManager.h
	g++ -Wall --std=c++11 DisplayManager.h DisplayManager.cpp -c
FontGenerator.o: FontGenerator.cpp FontGenerator.h
	g++ -Wall --std=c++11 FontGenerator.h FontGenerator.cpp -c
PixelMatrix.o: PixelMatrix.cpp PixelMatrix.h
	g++ -Wall --std=c++11 PixelMatrix.h PixelMatrix.cpp -c


	
