#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "./header/directdef.h"

// --- TODO ---
// SNAKE DOUBLE JUMPS, LEAVING A CORPSE IN THE PLACE IT WOULD BE
// I WANT TO MAKE IT DOUBLE JUMP IN THE X-AXIS INSTEAD OF LONGER SLEEP IN THE Y-AXIS (MAYBE)
// uhh i forgor what else i wanted to fix and add, but have fun
// also figure out how to make snake longer (if too difficult, watch coding train video again)

HANDLE pause;
const int MAX_LENGTH = (NL_MAX*LS_MAX)-1;
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

DWORD WINAPI move(LPVOID lpParam) {
	volatile coordinates** multi_coords = (volatile coordinates**) lpParam;
	WaitForSingleObject(pause, INFINITE);
	CloseHandle(pause);
	short Length = 0;
	while(1) {
		clearSnake(multi_coords[MAX_LENGTH-Length]);
		for(int i = MAX_LENGTH; i > MAX_LENGTH - Length; i--) {
		multi_coords[i-1]->X = multi_coords[i]->X;
		multi_coords[i-1]->Y = multi_coords[i]->Y;
		}
		checkDir(multi_coords[MAX_LENGTH]->direction, multi_coords[MAX_LENGTH], 1, NULL);
		for(int i = MAX_LENGTH-Length; i <= MAX_LENGTH; i++) {
			go_to(multi_coords[i]->X, multi_coords[i]->Y);
			printf(SNAKE_SYM);
		}
		switch(multi_coords[MAX_LENGTH]->direction) { // decide how to sleep (haahahaha funny im tired rn)
			case LEFT:
				Sleep(SLEEP_TIME);
				break;
			case RIGHT:
				Sleep(SLEEP_TIME);
				break;
			case UP: // change SLEEP_TIME if it's UP or DOWN
				Sleep(SLEEP_TIME*2);
				break;
			case DOWN:
				Sleep(SLEEP_TIME*2);
				break;
		}
		if((multi_coords[MAX_LENGTH]->randX == multi_coords[MAX_LENGTH]->X) && (multi_coords[MAX_LENGTH]->randY == multi_coords[MAX_LENGTH]->Y)) { // check if coords match, eat food and spawn new
			Length = multi_coords[MAX_LENGTH]->length++;
			spawnFood(multi_coords[MAX_LENGTH]);
		}
	}
	return 0;
}

int main() {
volatile coordinates** multi_coords = (volatile coordinates**) malloc(sizeof(coordinates*)*MAX_LENGTH+1); // allocating double pointer
for(int i = 0; i <= MAX_LENGTH; i++) { // allocating each struct
	multi_coords[i] = malloc(sizeof(coordinates));
}
if(multi_coords == NULL) {
	printf("ERROR ALLOCATING MEMORY\n");
	return -1;
}
multi_coords[MAX_LENGTH]->X = LS_MAX/2;
multi_coords[MAX_LENGTH]->Y = 2;
multi_coords[MAX_LENGTH]->length = 0;
multi_coords[MAX_LENGTH]->direction = -1;
int stop = 0;
pause = CreateEvent(NULL, TRUE, FALSE, NULL);

hidecursor();

system("cls");
go_to(multi_coords[MAX_LENGTH]->X, multi_coords[MAX_LENGTH]->Y); // set cursor to coordinates
printf(SNAKE_SYM);

spawnFood(multi_coords[MAX_LENGTH]); // spawn food at random coordinates (TODO: GET BETTER RANDOM COORDINATES)
HANDLE thread_2 = CreateThread(NULL, 0, move, (LPVOID) multi_coords, 0, NULL); // start new thread
if(thread_2 == NULL) {
	printf("ERROR: Could not create thread\n");
	return -1;
}
checkDir(getch(), multi_coords[MAX_LENGTH], 0, &stop); // check first move
SetEvent(pause); // signal pause over, so second thread can get moving

while(1) {
	go_to(multi_coords[MAX_LENGTH]->X, multi_coords[MAX_LENGTH]->Y);
	printf(SNAKE_SYM);
	checkDir(getch(), multi_coords[MAX_LENGTH], 0, &stop);
	if(stop) {
		system("cls");
		printf("FINAL LENGTH: %d\n", multi_coords[MAX_LENGTH]->length);
		for(int i = 0; i <= MAX_LENGTH; i++) { // freeing each struct
			free((coordinates*) multi_coords[i]); // have to do (coordinates *) to avoid compiler warning
		}
		free((coordinates **) multi_coords); // have to do (coordinates **) to avoid compiler warning
		CloseHandle(thread_2);
		return 0;
	}
	
}

}