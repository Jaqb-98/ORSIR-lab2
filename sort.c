#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>             

int main() {
	int fd[2];
	int pid, status;
	FILE* stream;

	if (pipe(fd) < 0) {
		printf("blad otwarcia lacza\n");
		exit(1);
	}

	switch ((pid = (int)fork()))
	{
	case -1:
		perror("blad inicjacji potomka");
		exit(1);
		break;
	case 0:
		printf("<!>\tpotomek [%d] startuje\n", (int)getpid());
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO); // funkcja dup2(int old, int new) powoduje utworzenie kopii deskryptora i wskazuje na co go skopiowac
		close(fd[0]);
		printf("-----------------------\n");
		//wywolanie funkcji systemowej do sortowania
		execl("/usr/bin/sort", "sort", "--reverse", (char*)NULL);
	default:
		close(fd[0]);
		stream = fdopen(fd[1], "w"); // przypisanie strumienia plikowego deskryptorowi

		//wysylamy sformatowany wynik do strumienia
		fprintf(stream, "\tAaaaa\n");
		fprintf(stream, "\tBbbbb\n");
		fprintf(stream, "\tCcccc\n");
		fprintf(stream, "\tDdddd\n");

		fflush(stream);

		close(fd[1]);

		wait(&status); //oczekiwanie na zakonczenie pracy potomka

		printf("---------------------------\n");
		printf("\t potomek [%d] zakonczyl dzialanie i zwrocil [%d] \n", pid, status);

	}

	return 0;
}