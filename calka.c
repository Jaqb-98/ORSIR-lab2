#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main(void)
{
	//deklaracje zmiennych i funkcji
	int pid, status;
	double sine(double);
	double quad(unsigned int, double, double, double (*)(double));
	unsigned int n;
	double a, b, I;
	int fd[2]; //desktyptory do zapisu fd[0] i odczytu fd[1]

	//przypisanie wartosci do zmiennych
	a = 0.0, b = 1.0, I = 0.0;
	n = 3200;

	//proba nawiazania polaczenia nienazwanego
	if (pipe(fd) < 0)
	{
		printf("...blad otwarcia lacza\n");
		exit(1);
	}

	//tworzenie procesu potomnego przy uzyciu fork()
	switch (fork())
	{
	case -1:
		perror("<!> blad inicjacji potomka");
		exit(1);
		break;
	case 0:
		close(fd[0]);   //zamkniecie odczytu
		I = quad(n, a, b, sine);
		printf("[%d] wartosc calki %19.6f\n", (int)getpid(), I);
		write(fd[1], (void*)&I, sizeof(double)); //zapisujemy do kanalu wartosc calki
		exit(0);
	default:
		close(fd[1]); //zamkniecie zapisu
		printf("[%d] wykonuje, wazne rzeczy...\n", (int)getpid());
		read(fd[0], (void*)&I, sizeof(double)); //odczytywana jest wartosc zapisana przez potomka
		pid = (int)wait(&status);
		printf("[%d] zakonczyl z kodem %d\n", pid, status);
		printf("[%d] otrzymal wartosc %16.6f\n", (int)getpid(), I);
	}
	return 0;
}


//metoda do obliczania calki metoda trapezow
double quad(unsigned int n, double a, double b, double (*fun)(double))
{
	unsigned int k;
	double xk, sum;
	sum = fun(a) + fun(b);
	for (k = 1; k < n; k++)
	{
		xk = a + (b - a) * k / n;
		sum += 2.0 * fun(xk);
	}
	return ((b - a) / (2.0 * n) * sum);
}

//calkowana funkcja
double sine(double x)
{
	return sin(2 * M_PI * x) * exp(-x);
}