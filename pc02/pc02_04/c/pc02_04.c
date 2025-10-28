/**
 * Crypt kicker
 * pc110204
 * uva843
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHSIZE 26
#define MAXLETTR 16
#define MAXCHARS 80
#define MAXWORDS (MAXCHARS / 2 + 1)

int split_words(const char *line, char words[][MAXLETTR + 1]) {
	int count = 0;
	int i = 0;

	while (line[i] != '\0') {
		while (line[i] == ' ') {
			i++;
		}
		if (line[i] == '\0') {
			break;
		}

		int j = 0;
		while (line[i] != '\0' && line[i] != ' ' && j < MAXLETTR) {
			words[count][j++] = line[i++];
		}
		words[count][j] = '\0';
		count++;

		while (line[i] != '\0' && line[i] != ' ') {
			i++;
		}
	}

	return count;
}

int can_map(const char *cipher_word, const char *plain_word, char reverse_key[ALPHSIZE], int changed[ALPHSIZE]) {
	for (int i = 0; cipher_word[i] != '\0'; i++) {
		int c = cipher_word[i] - 'a';
		char p = plain_word[i];

		if (reverse_key[c] != '*') {
			if (reverse_key[c] != p) {
				return 0;
			}
		} else {
			for (int j = 0; j < ALPHSIZE; j++) {
				if (reverse_key[j] == p) {
					return 0;
				}
			}

			reverse_key[c] = p;
			changed[c] = 1;
		}
	}

	return 1;
}

int solve(const char **dict, int n, int word_index, char words[][MAXLETTR + 1], int word_count, char reverse_key[ALPHSIZE]) {
	if (word_index >= word_count) {
		return 1;
	}

	char *cipher_word = words[word_index];
	int len = strlen(cipher_word);

	for (int i = 0; i < n; i++) {
		if (strlen(dict[i]) != len) {
			continue;
		}

		int changed[ALPHSIZE] = {0};

		if (can_map(cipher_word, dict[i], reverse_key, changed)) {
			if (solve(dict, n, word_index + 1, words, word_count, reverse_key)) {
				return 1;
			}
		}

		for (int j = 0; j < ALPHSIZE; j++) {
			if (changed[j]) {
				reverse_key[j] = '*';
			}
		}
	}

	return 0;
}


void find_key(const char **dict, int n, const char *crypt, char reverse_key[ALPHSIZE]) {
	char words[50][MAXLETTR + 1];
	int word_count = split_words(crypt, words);

	if (!solve(dict, n, 0, words, word_count, reverse_key)) {
		for (int i = 0; i < ALPHSIZE; i++) {
			reverse_key[i] = '*';
		}
	}
}

void kick_crypt(const char *crypt, const char reverse_key[ALPHSIZE], char *uncrypt) {
	int i = 0;
	int j = 0;

	while (crypt[i] != '\0') {
		if (crypt[i] == ' ') {
			uncrypt[j++] = ' ';
			i++;
		} else {
			int idx = crypt[i] - 'a';
			if (reverse_key[idx] == '*') {
				uncrypt[j++] = '*';
			} else {
				uncrypt[j++] = reverse_key[idx];
			}
			i++;
		}
	}
	
	uncrypt[j] = '\0';

	printf("%s\n", uncrypt);
}


int main(void) {
	int n;
	if (scanf("%d", &n) != 1) {
		return 1;
	}

	char *last;

	char **dict = (char **)malloc(n * sizeof(char*));
	if (dict == NULL) {
		free(dict);
		return 1;
	}

	for (int i = 0; i < n; i++) {
		dict[i] = (char*)malloc((MAXLETTR + 1) * sizeof(char));
		if (dict[i] == NULL) {
			free(dict[i]);
			return 1;
		}

		if (scanf("%16s%*c", dict[i]) != 1) {
			return 1;
		}
	}
	
	char crypt[MAXCHARS + 1];
	char uncrypt[MAXCHARS + 1];

	while (fgets(crypt, MAXCHARS + 1, stdin) != NULL) {
		last = strchr(crypt, '\n');
		if (last != NULL) {
			*last = '\0';
		}

		char reverse_key[ALPHSIZE];

		for (int i = 0; i < ALPHSIZE; i++) {
			reverse_key[i] = '*';
		}

		find_key((const char **)dict, n, crypt, reverse_key);

		kick_crypt(crypt, reverse_key, uncrypt);
	}

	for (int i = 0; i < n; i++) {
		free(dict[i]);
	}

	free(dict);

	return 0;
}
