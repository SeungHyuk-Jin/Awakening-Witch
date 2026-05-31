#ifndef INIT_H
#define INIT_H
#define _CRT_SECURE_NO_WARNINGS
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
#include "object.h"
#include "hud.h"

void reset_game_state(void);
void init(void);
void reset_keyboard_event(void);
#endif