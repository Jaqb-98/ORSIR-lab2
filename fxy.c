#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>    
#include <math.h>

int main(void) {
	int pid, status;
	int one[2], two[2];
	double x = 1.0, y = 1.0;

	printf("\t[%d] nadrzedny, start\n\n", (int)getpid());


	// aby wykonac komunikacje dwukierunkowa potrzebne sa dwa kanaly
	if (pipe(one) < 0 || pipe(two) < 0) {
		printf("blad otwarcia laczy\n");
		exit(1);
	}

	switch (pid = (int)fork()) {
	case -1:
		perror("blad inicjacji potomka");
		exit(1);
		break;
	case 0:
		printf("\t[%d] potomek, start\n\n", (int)getpid());
		close(one[1]); close(two[0]); //zamykamy odczyt z pierwszego kanalu i zapis do drugiego
		read(one[0], (void*)&x, sizeof(double)); //czytamy to co proces nadrzedny chce przekazac
		printf("\t[%d] otrzymal x=%f\n", (int)getpid(), x);
		y = x * M_PI;
		printf("\t[%d] wykonal f(x)=y, wysyla y=%f\n", (int)getpid(), y);

		write(two[1], (void*)&y, sizeof(double)); //wysylamy wynik do procesu nadrzednego
		printf("\t[%d] potomek, stop\n\n", (int)getpid());
		exit(0);
	default:
		close(one[0]); close(two[1]); //zamykamu zapis do pierwszego kanalu i odczyt z drugiego
		printf("\t[%d] wysyla do potomka [%d]x=%f\n\n", (int)getpid(), pid, x);
		write(one[1], (void*)&x, sizeof(double)); // wyslanie danych do procesu potomnego

		read(two[0], (void*)&y, sizeof(double)); //czekanie na wynik
		wait(&status);
		printf("\t[%d] potomek, zwroil sterowanie kod powrotu[% d]\n", pid, status);

		printf("\t[%d] otrzymaly=%f\n", (int)getpid(), y);
		printf("\n\t[%d] nadrzeny, stop\n", (int)getpid());
	}

	return 0;
}