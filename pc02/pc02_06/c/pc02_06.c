/* erdos numbers
 * pc110206
 * uva10044 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_P		100
#define MAX_N		100
#define MAXLEN		100
#define HASH_SIZE	1009
#define MAX_AUTHORS	2048

/* Linked list for handling imperfect hashing */
typedef struct node_t {
	char name[MAXLEN];
	int index;
	struct node_t *next;
} node_t;

unsigned int hash(const char *str) {
	unsigned int h = 0;

	while (*str) {
		h = (h << 5) + h + (unsigned char)*str;
		str++;
	}

	return h % HASH_SIZE;
}

int get_index(const char *name, int *next_index, node_t *table[HASH_SIZE]) {
	unsigned int h = hash(name);

	for (node_t *cur = table[h]; cur; cur = cur->next) {
		if (!strcmp(cur->name, name)) return cur->index; /* If already in list return index */
	}

	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	if (!new_node) return -1;

	strncpy(new_node->name, name, MAXLEN - 1);
	new_node->name[MAXLEN - 1] = '\0';
	new_node->index = (*next_index)++; /* Side effect updates value stored in next_index (pointer) */
	new_node->next = table[h];
	table[h] = new_node; /* Insert at first position of index list relative to hash h */

	return new_node->index;
}

int find_index(const char *name, node_t *table[HASH_SIZE]) {
	unsigned int h = hash(name);

	for (node_t *cur = table[h]; cur; cur = cur->next) {
		if (!strcmp(cur->name, name)) return cur->index;
	}

	return -1;
}

/* Linked list representation of adjacency matrix
 * that represent co-authorship */
typedef struct neighbor_t {
	int index; /* Index given by hash index */
	struct neighbor_t *next;
} neighbor_t;

void add_edge(int u, int v, neighbor_t **graph) {
	if (u == v) return;

	neighbor_t *new_node = (neighbor_t *)malloc(sizeof(neighbor_t));
	if (!new_node) return;

	new_node->index = v;
	new_node->next = graph[u];
	graph[u] = new_node;
}

/* Trim util */
void trim(char *str) {
	char *p = str;
	while (isspace(*p)) p++;

	char *end = p + strlen(p) - 1;
	while (end >= p && isspace(*end)) *(end--) = '\0';

	memmove(str, p, strlen(p) + 1);
}

/* Parse papers titles to find authors */
int find_authors(const char *paper, char authors[][MAXLEN]) {
	char buf[MAXLEN];
	strncpy(buf, paper, sizeof(buf) - 1);
	buf[sizeof(buf) - 1] = '\0';

	char *colon = strchr(buf, ':');
	if (colon) *colon = '\0';

	char *token;
	char parts[MAX_AUTHORS][MAXLEN];
	int count = 0;

	token = strtok(buf, ",");
	while (token && count < MAX_AUTHORS) {
		trim(token);

		if (*token) {
			strncpy(parts[count], token, MAXLEN - 1);
			parts[count][MAXLEN - 1] = '\0';
			count++;
		}

		token = strtok(NULL, ",");
	}

	int author_count = 0;
	for (int i = 0; i + 1 < count; i += 2) {
		char last[MAXLEN], first[MAXLEN];

		strncpy(last, parts[i], MAXLEN - 1);
		last[MAXLEN - 1] = '\0';

		strncpy(first, parts[i + 1], MAXLEN - 1);
		first[MAXLEN - 1] = '\0';

		trim(last);
		trim(first);

		if (*last && *first) {
			snprintf(authors[author_count], MAXLEN, "%s, %s", last, first);
			authors[author_count][MAXLEN - 1] = '\0';
			author_count++;
		}
	}

	return author_count;
}

/* Main function */
int main(void) {
	int T;
	if (scanf("%d", &T) != 1) return 0;

	int is_first = 1;
	while (1) {
		if (!T) break;

		if (!is_first) printf("\n");
		is_first = 1;

		printf("Scenario %d\n", T--);

		int P, N;
		if (scanf("%d %d", &P, &N) != 2) break;
		getchar();

		node_t *table[HASH_SIZE] = {NULL};
		neighbor_t **graph = (neighbor_t **)calloc(MAX_AUTHORS, sizeof(neighbor_t *));
		int next_index = 0;

		char line[MAXLEN];
		for (int i = 0; i < P; i++) {
			fgets(line, sizeof(line), stdin);
			line[strcspn(line, "\n")] = '\0';

			char authors[MAX_AUTHORS][MAXLEN];
			int n = find_authors(line, authors);

			int ids[MAX_AUTHORS];

			for (int j = 0; j < n; j++) {
				ids[j] = get_index(authors[j], &next_index, table);
			}

			for (int j = 0; j < n; j++) {
				for (int k = j + 1; k < n; k++) {
					add_edge(ids[j], ids[k], graph);
					add_edge(ids[k], ids[j], graph);
				}
			}
		}

		char queries[MAX_N][MAXLEN];

		for (int i = 0; i < N; i++) {
			fgets(queries[i], MAXLEN, stdin);
			queries[i][strcspn(queries[i], "\n")] = '\0';
			trim(queries[i]);
		}

		int erdos = find_index("Erdos, P.", table);

		int *dist = (int *)malloc(next_index * sizeof(int));
		for (int i = 0; i < next_index; i++) {
			dist[i] = -1;
		}

		/* BFS */
		if (erdos != -1) {
			int *queue = (int *)malloc(next_index * sizeof(int));
			int front = 0; int rear = 0;

			queue[rear++] = erdos;
			dist[erdos] = 0;

			while (front < rear) {
				int u = queue[front++];

				for (neighbor_t *cur = graph[u]; cur; cur = cur->next) {
					if (dist[cur->index] == -1) {
						dist[cur->index] = dist[u] + 1;
						queue[rear++] = cur->index;
					}
				}
			}

			free(queue);
		}

		for (int i = 0; i < N; i++) {
			int idx = find_index(queries[i], table);

			if (idx == -1 || dist[idx] == -1) {
				printf("%s infinity\n", queries[i]);
			} else {
				printf("%s %d\n", queries[i], dist[idx]);
			}
		}

		free (dist);

		for (int i = 0; i < HASH_SIZE; i++) {
			for (node_t *cur = table[i]; cur; ) {
				node_t *tmp = cur;
				cur = cur->next;
				free(tmp);
			}
		}

		for (int i = 0; i < MAX_AUTHORS; i++) {
			for (neighbor_t *cur = graph[i]; cur; ) {
				neighbor_t *tmp = cur;
				cur = cur->next;
				free(tmp);
			}
		}
		free(graph);
	}

	return 0;
}
