/**
 * The 3 * n + 1 problem
 * pc110101
 * uva100
 */

#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 1000000

int memo[MAX_NUMBER + 10];

void init_memo(void) {
	memset(memo, 0, sizeof(memo));
	memo[1] = 1;
}

int is_valid_number(int number) {
	return (number > 0) && (number < MAX_NUMBER);
}

long long next_collatz(long long number) {
	return (number & 1) ? number + (number << 1) + 1 : number >> 1;
}

int collatz_length(long long number) {
	if (number == 1) return 1;

	if (is_valid_number(number) && memo[number] != 0) {
		return memo[number];
	}

	int length = 1 + collatz_length(next_collatz(number));

	if (is_valid_number(number)) {
		memo[number] = length;
	}

	return length;
}

int max_collatz_length(int first_number, int second_number) {
	int start = (first_number < second_number) ? first_number : second_number;
	int end = first_number + second_number - start;
	int max_length = 0;

	for (int number = start; number <= end; number++) {
		int curr_length = collatz_length(number);
		if (curr_length > max_length) {
			max_length = curr_length;
		}
	}

	return max_length;
}

int main(void) {
	init_memo();
	collatz_length(MAX_NUMBER);

	int first_number, second_number;
	while (1) {
		int scan_result = scanf("%d%d", &first_number, &second_number);
		if (scan_result == EOF) break;
		if (scan_result != 2) return -1;

		if (!is_valid_number(first_number) || !is_valid_number(second_number)) {
			return -1;
		}

		if (first_number > second_number) {
			int tmp_number = first_number;
			first_number = second_number;
			second_number = tmp_number;
		}

		printf("%d %d %d\n", first_number, second_number, max_collatz_length(first_number, second_number));
	}
	
	return 0;
}