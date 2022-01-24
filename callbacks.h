#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "ConfiguracoesJogo.h"

extern ConfiguracoesJogo config;

void keyPress(unsigned char key, int x, int y);

void keyup(unsigned char key, int x, int y);

void ResetKeyStatus();

void renderScene(void);

void init(void);

void idle(int value);

void mouse (int button, int state, int x, int y);

void motion (int x, int y);

#endif /* CALLBACKS_H */