/* hartals
 * pc110203
 * uva10050 */

#include <stdio.h>
#include <stdlib.h>

int calculate_hartal_days(int N, int *h, int P) {
	char *days = (char *)calloc(N + 1, sizeof(char));
	int hartal_days = 0;

	for (int i = 0; i < P; i++) {
		int hartal_param = h[i];

		for (int j = hartal_param; j <= N; j += hartal_param) {
			if (j % 7 != 0 && j % 7 != 6) {
				days[j] = 1;
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		if (days[i] == 1) {
			hartal_days++;
		}
	}

	free(days);

	return hartal_days;
}



int main(void) {
	int T;
	scanf("%d", &T);

	while (T--) {
		int N;
		scanf("%d", &N);

		int P;
		scanf("%d", &P);

		int *h;

		h = (int *)malloc(P * sizeof(int));
		if (!h) {
			free(h);
			return 1;
		}

		for (int i = 0; i < P; i++) {
			scanf("%d", &h[i]);
		}

		int hartal_days = calculate_hartal_days(N, h, P);

		printf("%d\n", hartal_days);
	}

	return 0;
}
