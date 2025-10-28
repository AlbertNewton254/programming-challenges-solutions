/**
 * Contests scoreboard
 * pc110207
 * uva10258
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int id;
	int solved;
	int penalty;
} contestant_result_t;

typedef struct {
	int solved;
	int penalty;
	int participated;
	int wrong[10];
	int solvedFlag[10];
} contestant_t;

int compare_contestants(const void *a, const void *b) {
	contestant_result_t *ca = (contestant_result_t *)a;
	contestant_result_t *cb = (contestant_result_t *)b;

	if (cb->solved != ca->solved) {
		return cb->solved - ca->solved;
	}

	if (ca->penalty != cb->penalty) {
		return ca->penalty - cb->penalty;
	}

	return ca->id - cb->id;
}

void contestant_init(contestant_t *c) {
	c->solved = 0;
	c->penalty = 0;
	c->participated = 0;
	memset(c->wrong, 0, sizeof(c->wrong));
	memset(c->solvedFlag, 0, sizeof(c->solvedFlag));
}

void contestant_submit(contestant_t *c, int problem, int time, char verdict) {
	c->participated = 1;
	int idx = problem - 1;

	if (verdict == 'I') {
		if (!c->solvedFlag[idx]) {
			c->wrong[idx]++;
		}
	} else if (verdict == 'C') {
		if (!c->solvedFlag[idx]) {
			c->solvedFlag[idx] = 1;
			c->solved++;
			c->penalty += time + 20 * c->wrong[idx];
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);

	int is_first = 1;

	while (T--) {
		if (!is_first) {
			printf("\n");
		}
		is_first = 0;

		contestant_t teams[101];
		for (int i = 0; i <= 100; i++) {
			contestant_init(&teams[i]);
		}

		char line[256];
		while (fgets(line, sizeof(line), stdin)) {
			if (line[0] == '\n') {
				break;
			}

			int t, p, time;
			char verdict;

			if (sscanf(line, "%d%d%d %c", &t, &p, &time, &verdict) == 4) {
				contestant_submit(&teams[t], p, time, verdict);
			}
		}

		contestant_result_t scoreboard[101];
		int count = 0;

		for (int i = 1; i <= 100; i++) {
			if (teams[i].participated) {
				scoreboard[count].id = i;
				scoreboard[count].solved = teams[i].solved;
				scoreboard[count].penalty = teams[i].penalty;
				count++;
			}
		}

		qsort(scoreboard, count, sizeof(contestant_result_t), compare_contestants);

		for (int i = 0; i < count; i++) {
			printf("%d %d %d\n", scoreboard[i].id, scoreboard[i].solved, scoreboard[i].penalty);
		}
	}

	return 0;
}
