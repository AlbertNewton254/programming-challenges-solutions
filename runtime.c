#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <path_to_binary>\n", argv[0]);
		return 1;
	}

	char *file_path = argv[1];
	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC, &start);
	system(file_path);
	clock_gettime(CLOCK_MONOTONIC, &end);

	double elapsed_ms = (end.tv_sec - start.tv_sec) * 1000.0 
						+ (end.tv_nsec - start.tv_nsec) / 1e6;

	printf("Time spent: %.3f milliseconds\n", elapsed_ms);

	return 0;
}

