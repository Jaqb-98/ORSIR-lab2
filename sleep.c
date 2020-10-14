#include <stdio.h>
#include <unistd.h>

int main(void) {
	printf("1"); fflush(stdout); sleep(1);
	printf("2"); fflush(stdout); sleep(1);
	printf("3"); fflush(stdout); sleep(1);
	printf("4"); fflush(stdout); sleep(1);
	printf("5"); fflush(stdout); sleep(1);


	printf(" koniec\n");

	return 0;
}