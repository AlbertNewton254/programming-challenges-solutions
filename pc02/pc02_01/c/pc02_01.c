/**
 * Jolly jumpers
 * pc110201
 * uva10038
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 3000

int is_jolly(int array[MAX_SIZE], int size) {
	int seen_differences[MAX_SIZE - 1] = {0};

	for (int i = 0; i < size - 1; i++) {
		int difference = abs(array[i + 1] - array[i]);

		if (difference < 1 || difference > size - 1) {
			return 0;
		}

		if (seen_differences[difference - 1] == 1) {
			return 0;
		}

		seen_differences[difference - 1] = 1;
	}

	return 1;
}

int main(void) {
	int array[MAX_SIZE];
	int size;

	while (scanf("%d", &size) != EOF) {
		for (int i = 0; i < size; i++) {
			scanf("%d", &array[i]);
		}

		if (is_jolly(array, size)) {
			printf("Jolly\n");
		} else {
			printf("Not jolly\n");
		}
	}

	return 0;
}
