#ifndef KEY_H
#define KEY_H
#include <allegro5/allegro.h>
#define KEY_SEEN 1
#define KEY_DOWN 2
unsigned char key[ALLEGRO_KEY_MAX];
typedef enum { UP, DOWN, LEFT, RIGHT } Direction;
Direction player_direction;

void keyboard_init(void);
void keyboard_update(ALLEGRO_EVENT*);
#endif