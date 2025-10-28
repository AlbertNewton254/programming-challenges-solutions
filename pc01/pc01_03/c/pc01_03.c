/**
 * The trip
 * pc110103
 * uva10137
 */

#include <stdio.h>
#include <math.h>

const int MAX_STUDENTS = 1000;
const double MAX_MONEY = 10000.00;

double round_to_cent(double value) {
	return round(value * 100) / 100;
}

double calculate_exchange(double money[], int students) {
	double total = 0.0;
	for (int i = 0; i < students; i++) {
		total += money[i];
	}

	double avg = total / students;
	double avg_rounded = round_to_cent(avg);

	double positive_diff = 0.0;
	double negative_diff = 0.0;

	for (int i = 0; i < students; i++) {
		double diff = money[i] - avg_rounded;
		diff = round_to_cent(diff);
		if (diff > 0) {
			positive_diff += diff;
		} else {
			negative_diff += -diff;
		}
	}

	return (positive_diff < negative_diff) ? positive_diff : negative_diff;
}

int main(void) {
	double money[MAX_STUDENTS];
	int students;

	while (1) {
		if (scanf("%d", &students) != 1 || students == 0) {
			break;
		}

		for (int i = 0; i < students; i++) {
			scanf("%lf", &money[i]);
			money[i] = round_to_cent(money[i]);
		}

		double exchange = calculate_exchange(money, students);
		printf("$%.2lf\n", exchange);
	}

	return 0;
}