#include <stdio.h>
#include <limits.h>

int main(void) {
	FILE* stream;
	char buffer[LINE_MAX];
	int run;

	if ((stream = fopen("channel", "r+"))) {
		run = 1;
	}
	else {
		run = 0;
		perror("blad otwarcia lacza");
	}

	while (run) {
		if (fgets(buffer, 256, stream)) {
			fprintf(stream, "%s", buffer);
			fflush(stream);
		}
	}
	return 0;
}