#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

int main(void) {
	time_t stamp;
	pid_t pid;
	int fd, run;
	char cmd;

	printf("\n[%d]*S*E*R*W*E*R*[%d]\n\n", (int)getpid(), (int)getpid());


	//proba otwarcia lacza do odczytu
	if ((fd = open("pipe", O_RDONLY)) > 0) {
		run = 1;
	}
	else { 
		printf("!.!..nie znaleziono lacza..!.!\n\n"); 
		run = 0; 
	}

	while (run) {
		read(fd, &pid, sizeof(pid_t)); //odczytanie nadawcy
		read(fd, &cmd, sizeof(char)); //odczytanie komendy

		stamp = time(NULL);
		printf("[%d]\t|%c|->%s", (int)pid, cmd, ctime(&stamp));
		if (cmd == 'Q') {
			run = 0;
			close(fd);
		}
	}
	return 0;
}