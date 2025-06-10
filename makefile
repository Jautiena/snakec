build:
	gcc snake.c "./header/directdefsource.c" -Wall -o2 -s -o snake.exe

clean:
	del snake.exe