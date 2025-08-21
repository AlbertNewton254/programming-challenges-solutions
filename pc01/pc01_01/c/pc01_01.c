/* the 3 * n + 1 problem
 * pc110101
 * uva100 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_NUMBER 1000000

int memo[MAX_NUMBER + 10];

int init_memo(void) {
	memset(memo, 0, sizeof(memo));
	memo[1] = 1;
}

int is_valid_number(int number) {
	return (number > 0) && (number < MAX_NUMBER);
}

long long next_collatz(long long number) {
	if (!(number & 1)) {
		return number >> 1;
	} else {
		return number + (number << 1) + 1;
	}
}

int collatz_length(long long number) {
	if (number == 1) {
		return 1;
	}

	if (is_valid_number(number) && memo[number] != 0) {
		return memo[number];
	}

	int length = 1 + collatz_length(next_collatz(number));

	if (is_valid_number(number)) {
		memo[number] = length;
	}

	return length;
}

int max_collatz_length(int number1, int number2) {
	int start, end;
	int max_length;

	start = (number1 < number2) ? number1 : number2;
	end = number1 + number2 - start;
	max_length = 0;

	for (int number = start; number <= end; number++) {
		if (collatz_length(number) > max_length) {
			max_length = collatz_length(number);
		}
	}

	return max_length;
}

int main(void) {
	clock_t start, end;
	double cpu_time_used;
	
	start = clock();

	init_memo();
	collatz_length(MAX_NUMBER);

	int number1, number2;

	while (1) {
		int scan = scanf("%d%d", &number1, &number2);

		if (scan == EOF) {
			break;
		} else if (scan == 2) {

			if (!(is_valid_number(number1)) || !(is_valid_number(number2))) {
				return -1;
			}

			if (number1 > number2) {
				int tmp;

				tmp = number1;
				number1 = number2;
				number2 = tmp;
			}
	
			printf("%d %d %d\n", number1, number2, max_collatz_length(number1, number2));
		} else {
			return -1;
		}
	}

	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time of execution: %lf seconds\n", cpu_time_used);

	return 0;
}
