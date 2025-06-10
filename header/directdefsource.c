#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "directdef.h"

void go_to(int x, int y) {
	COORD cords;
	cords.X = x;
	cords.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cords);
}
void spawnFood(volatile coordinates* randcoord) {
	srand(time(NULL));
	randcoord->randX = rand() % (LS_MAX+1);
	randcoord->randY = rand() % (NL_MAX+1);
	go_to(randcoord->randX, randcoord->randY);
	printf(FOOD_SYM);
}
void clearSnake(volatile coordinates* coords) {
	go_to(coords->X, coords->Y);
	printf(" ");
}

void checkDir(char _case, volatile coordinates* multi_coords, char moveDir, int* STOP) {
	if(moveDir == 1) {
	switch(_case) {
		case UP:
			if((multi_coords->direction == UP) && (STOP != NULL)) { // check for keypress in same direction as snake, and makes an exeption for NULL
				break;
			}
			if((multi_coords->direction == DOWN) || (multi_coords->Y == 0)) { // make it so it can't turn 180 instantly, also adds logic for walls
				break;
			}
			multi_coords->direction = UP;
			clearSnake(multi_coords);
			multi_coords->Y--;
			break;
			
		
		case DOWN:
			if((multi_coords->direction == DOWN) && (STOP != NULL)) { // check for keypress in same direction as snake, and makes an exeption for NULL
				break;
			}
			if((multi_coords->direction == UP) || (multi_coords->Y == NL_MAX)) { // make it so it can't turn 180 instantly, also adds logic for walls
				break;
			}
			multi_coords->direction = DOWN;
			clearSnake(multi_coords);
			multi_coords->Y++;
			break;
		
		case LEFT:
			if((multi_coords->direction == LEFT) && (STOP != NULL)) { // check for keypress in same direction as snake, and makes an exeption for NULL
				break;
			}
			if((multi_coords->direction == RIGHT) || (multi_coords->X == 0)) { // make it so it can't turn 180 instantly, also adds logic for walls
				break;
			}
			multi_coords->direction = LEFT;
			clearSnake(multi_coords);
			multi_coords->X--;
			break;
		
		case RIGHT:
			if((multi_coords->direction == RIGHT) && (STOP != NULL)) { // check for keypress in same direction as snake, and makes an exeption for NULL
				break;
			}
			if((multi_coords->direction == LEFT) || (multi_coords->X == LS_MAX)) { // make it so it can't turn 180 instantly, also adds logic for walls
				break;
			}
			multi_coords->direction = RIGHT;
			clearSnake(multi_coords);
			multi_coords->X++;
			break;
		
		case ESCAPE:
			*STOP = 1;
	}
	}
	// IF MOVEDIR IS NOT TRUE, THEN JUST CHANGE DIRECTION
	switch(_case) {
		case UP:
			if((multi_coords->direction == DOWN) || (multi_coords->Y == 0)) {break;} // make it so it can't turn 180 instantly, also adds logic for walls
			if(multi_coords->direction == UP) {break;} // breaks if input is same as current direction
			
			multi_coords->direction = UP;
			break;
					
		case DOWN:
			if((multi_coords->direction == UP) || (multi_coords->Y == NL_MAX)) {break;} // make it so it can't turn 180 instantly, also adds logic for walls
			if(multi_coords->direction == DOWN) {break;} // breaks if input is same as current direction
			
			multi_coords->direction = DOWN;
			break;
			
		case LEFT:
			if((multi_coords->direction == RIGHT) || (multi_coords->X == 0)) {break;} // make it so it can't turn 180 instantly, also adds logic for walls
			if(multi_coords->direction == LEFT) {break;} // breaks if input is same as current direction
			
			multi_coords->direction = LEFT;
			break;
			
		case RIGHT:
			if((multi_coords->direction == LEFT) || (multi_coords->X == LS_MAX)) {break;} // make it so it can't turn 180 instantly, also adds logic for walls
			if(multi_coords->direction == RIGHT) {break;} // breaks if input is same as current direction
			
			multi_coords->direction = RIGHT;
			break;
		
		case ESCAPE:
			*STOP = 1;
	}
}