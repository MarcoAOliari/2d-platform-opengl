EXECUTAVEL := trabalhocg
MAIN := client/main.cpp
SOURCE := src/*.cpp
FLAGS := -lGL -lGLU -lglut -std=c++11

all:
	g++ -o $(EXECUTAVEL) $(MAIN) $(SOURCE) $(FLAGS)

clean:
	rm -rf $(EXECUTAVEL)