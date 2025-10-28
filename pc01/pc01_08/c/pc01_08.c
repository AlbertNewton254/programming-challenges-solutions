/**
 * Australian voting
 * pc110108
 * uva10142
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CANDIDATES 20
#define MAX_VOTERS 1000
#define MAX_NAME_LEN 100

typedef struct {
	char name[MAX_NAME_LEN];
	int eliminated;
} candidate_t;

typedef struct {
	int preferences[MAX_CANDIDATES];
	int current_preference;
} voter_t;

void read_candidates(candidate_t *candidates_p, int n) {
	char line[MAX_NAME_LEN];

	for (int i = 0; i < n; i++) {
		if (fgets(line, sizeof(line), stdin) == NULL)
			break;
		line[strcspn(line, "\n")] = 0;
		strcpy(candidates_p[i].name, line);
		candidates_p[i].eliminated = 0;
	}
}

void read_votes(voter_t *voters_p, int *num_voters_p, int num_candidates) {
	char line[MAX_NAME_LEN];

	*num_voters_p = 0;

	while (fgets(line, sizeof(line), stdin) != NULL && line[0] != '\n') {
		char *token = strtok(line, " \n");
		int pref = 0;

		while (token != NULL && pref < num_candidates) {
			voters_p[*num_voters_p].preferences[pref++] = atoi(token) - 1;
			token = strtok(NULL, " \n");
		}
		voters_p[*num_voters_p].current_preference = 0;
		(*num_voters_p)++;
	}
}

void count_votes(const voter_t *voters_p, const candidate_t *candidates_p,
		int num_voters, int num_candidates, int *counts_p) {
	memset(counts_p, 0, sizeof(int) * num_candidates);

	for (int i = 0; i < num_voters; i++) {
		int pref = voters_p[i].current_preference;

		while (pref < num_candidates &&
		       candidates_p[voters_p[i].preferences[pref]].eliminated) {
			pref++;
		}
		if (pref < num_candidates) {
			counts_p[voters_p[i].preferences[pref]]++;
		}
	}
}

void eliminate_candidates(candidate_t *candidates_p, int num_candidates,
		const int *counts_p, int min_votes) {
	for (int i = 0; i < num_candidates; i++) {
		if (!candidates_p[i].eliminated && counts_p[i] == min_votes) {
			candidates_p[i].eliminated = 1;
		}
	}
}

int main(void) {
	int cases;

	if (scanf("%d\n", &cases) != 1)
		return 1;

	for (int c = 0; c < cases; c++) {
		if (c > 0)
			printf("\n");

		int num_candidates;

		if (scanf("%d\n", &num_candidates) != 1)
			break;

		candidate_t candidates[MAX_CANDIDATES];
		read_candidates(candidates, num_candidates);

		voter_t voters[MAX_VOTERS];
		int num_voters;
		read_votes(voters, &num_voters, num_candidates);

		while (1) {
			int counts[MAX_CANDIDATES] = {0};
			count_votes(voters, candidates, num_voters, num_candidates, counts);

			int max_votes = 0, min_votes = num_voters + 1;
			int remaining = 0;

			for (int i = 0; i < num_candidates; i++) {
				if (!candidates[i].eliminated) {
					remaining++;
					if (counts[i] > max_votes)
						max_votes = counts[i];
					if (counts[i] < min_votes)
						min_votes = counts[i];
				}
			}

			if (max_votes > num_voters / 2 || remaining <= 1) {
				for (int i = 0; i < num_candidates; i++) {
					if (!candidates[i].eliminated &&
					    counts[i] == max_votes) {
						printf("%s\n", candidates[i].name);
					}
				}
				break;
			}

			eliminate_candidates(candidates, num_candidates, counts, min_votes);
		}
	}

	return 0;
}