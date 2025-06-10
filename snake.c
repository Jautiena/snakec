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

DWORD WINAPI move(LPVOID lpParam) {
	volatile coordinates* multi_coords = (volatile coordinates*) lpParam;
	while(1) {
		WaitForSingleObject(pause, INFINITE);
		clearSnake(multi_coords);
		checkDir(multi_coords->direction, multi_coords, NULL);
		go_to(multi_coords->X, multi_coords->Y);
		printf(SNAKE_SYM);
		switch(multi_coords->direction) { // decide how to sleep (haahahaha funny im tired rn)
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
		if((multi_coords->randX == multi_coords->X) && (multi_coords->randY == multi_coords->Y)) {
		multi_coords->length++;
		spawnFood(multi_coords);
	}
	}
	return 0;
}

int main() {
volatile coordinates* multi_coords = (coordinates*) malloc(sizeof(coordinates));
multi_coords->X = LS_MAX/2;
multi_coords->Y = 2;
multi_coords->length = 1;
multi_coords->direction = -1;
int stop = 0;
pause = CreateEvent(NULL, TRUE, FALSE, NULL);

system("cls");
go_to(multi_coords->X, multi_coords->Y); // set cursor to coordinates

spawnFood(multi_coords); // spawn food at random coordinates (TODO: GET BETTER RANDOM COORDINATES)
HANDLE thread1 = CreateThread(NULL, 0, move, (coordinates*) multi_coords, 0, NULL);

while(1) {
	go_to(multi_coords->X, multi_coords->Y);
	printf(SNAKE_SYM);
	checkDir(getch(), multi_coords, &stop);
	SetEvent(pause);
	if(stop) {
		system("cls");
		free((coordinates *) multi_coords); // have to do (coordinates *) to avoid volatile warning
		CloseHandle(thread1);
		return 0;
	}
	
}

}