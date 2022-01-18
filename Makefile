EXECUTAVEL := trabalhocg
CODIGO_FONTE := *.cpp
FLAGS := -lGL -lGLU -lglut -std=c++11

all:
	g++ -o $(EXECUTAVEL) $(CODIGO_FONTE) $(FLAGS)

clean:
	rm -rf $(EXECUTAVEL)