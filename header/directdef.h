#include <windows.h>

#ifndef _DIRECTDEF_H_
#define _DIRECTDEF_H_

//getch definitions
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define ESCAPE 27

//size definitions
#define NL_MAX 20 // max newlines
#define LS_MAX 50 // Max leading space

//symbol definitions
#define SNAKE_SYM "s"
#define FOOD_SYM "f"

//time definitions
#define SLEEP_TIME 80 //ms

//struct definitions
typedef struct {
	char direction;
	short X, randX;
	short Y, randY;
	short length;
} coordinates;

//function definitions
void go_to(int x, int y);
void spawnFood(volatile coordinates* randcoord);
void clearSnake(volatile coordinates* coords);
void checkDir(char _case, volatile coordinates* coords, char moveDir, int* STOP);

#endif