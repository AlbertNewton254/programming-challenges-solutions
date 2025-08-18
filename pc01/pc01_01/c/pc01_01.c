/* the 3 * n + 1 problem
 * pc110101
 * uva100 */

#include <stdio.h>

const int MAX_NUMBER = (int) 1E6;

int is_valid_number(int number) {
	return (number > 0) && (number < MAX_NUMBER);
}

int collatz_length(long long number) {
	int length;

	length = 1;

	while (1) {
		length++;
		
		if (!(number & 1)) {
			number = number >> 1;
		} else {
			number += (number << 1) + 1;
		}
		
		if (number == 1) {
			break;
		}

		

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
	int number1, number2;

	if (scanf("%d%d", &number1, &number2) != 2) {
		return -1;
	}

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

	return 0;
}
