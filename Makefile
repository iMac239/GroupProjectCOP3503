ImageManipulator : UI.cpp Image.cpp
	g++ `pkg-config --cflags opencv` UI.cpp Image.cpp `pkg-config --libs opencv` -o ImageManipulator.out
