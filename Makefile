SRC = main.cpp \
	  Image.cpp \
	  Scene.cpp \
	  Camera.cpp

OBJ = $(SRC:.cpp=.o)
CFLAGS = -std=c++11 -O2 -w -lGLU -lGLEW -lglut -lGL -lpthread

.cpp.o:
	g++ -c $< $(CFLAGS)

all: test

test: $(OBJ)
	g++ $(OBJ) -g -o rasterizer $(CFLAGS)

clean:
	rm -f *.o raytracer *.ppm
