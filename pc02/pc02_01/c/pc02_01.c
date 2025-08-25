/* jolly jumpers
 * pc110201
 * uva10038 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 3000

int is_jolly(int array[MAX_SIZE], int size) {
	int seen_differences[MAX_SIZE-1] = {0};
	
	for (int i = 0; i < size-1; i++) {
		int difference = abs(array[i+1] - array[i]);
		
		if (difference < 1 || difference > size - 1) {
			return 0;
		}
		
		if (seen_differences[difference-1] == 1) {
			return 0;
		}
		
		seen_differences[difference-1] = 1;
	}
	
	return 1;
}

int main(void) {
	int array[MAX_SIZE];
	int size;
	clock_t start, end;
	double cpu_time_used;

	start = clock();

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

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time of execution: %lf seconds\n", cpu_time_used);

	return 0;
}
