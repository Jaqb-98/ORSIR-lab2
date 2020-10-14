#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

int main(void) {
	FILE* stream;
	char buffer[LINE_MAX];
	int run;

	int empty(char*);

	if ((stream = fopen("channel", "r+"))) {
		run = 1;
	}
	else {
		run = 0;
		perror("!.!..blad otwarcia lacza..!.!");
	}

	while (run) {
		bzero((void*)buffer, LINE_MAX); //usuwa dane z buffora
		fgets(buffer, LINE_MAX, stdin);//czyta linie ze strumienia i przekazuje do buffora
		if (!empty(buffer)) {
			fprintf(stream, "%s", buffer);
			fflush(stream);
		}
		else {
			fclose(stream);
			break;
		}

		fgets(buffer, LINE_MAX, stream);
		if (!empty(buffer)) {
			fprintf(stdout, "%s", buffer);
			fflush(stream);
		}
	}
	return 0;
}


int empty(char* string) {
	while (*string) {
		if (isalnum(*string++)) {
			return 0;
		}
	}
	return 1;
}