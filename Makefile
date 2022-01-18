EXECUTAVEL := trabalhocg
CODIGO_FONTE := *.cpp
FLAGS := -lGL -lGLU -lglut

all:
	g++ -o $(EXECUTAVEL) $(CODIGO_FONTE) $(FLAGS)

clean:
	rm -rf $(EXECUTAVEL)