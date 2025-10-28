"""
Erdos numbers
pc110206
uva10044
"""

import sys
from collections import defaultdict, deque


def get_authors(paper):
    """Extract authors from paper string."""
    colon_pos = paper.find(':')
    author_part = paper[:colon_pos] if colon_pos != -1 else paper

    parts = [p.strip() for p in author_part.split(',') if p.strip()]

    authors = []
    for i in range(0, len(parts) - 1, 2):
        author = f"{parts[i]}, {parts[i + 1]}"
        authors.append(author)

    return authors


def calculate_erdos_numbers(papers, queries):
    """Calculate Erdos numbers for all authors."""
    author_index = {}
    next_index = 0
    graph = defaultdict(list)

    for paper in papers:
        authors = get_authors(paper)

        author_ids = []
        for author in authors:
            if author not in author_index:
                author_index[author] = next_index
                next_index += 1
            author_ids.append(author_index[author])

        for i in range(len(author_ids)):
            for j in range(i + 1, len(author_ids)):
                u, v = author_ids[i], author_ids[j]
                graph[u].append(v)
                graph[v].append(u)

    dist = [-1] * next_index

    if "Erdos, P." in author_index:
        erdos_id = author_index["Erdos, P."]
        queue = deque([erdos_id])
        dist[erdos_id] = 0

        while queue:
            u = queue.popleft()

            for v in graph[u]:
                if dist[v] == -1:
                    dist[v] = dist[u] + 1
                    queue.append(v)

    results = []
    for query in queries:
        if query not in author_index or dist[author_index[query]] == -1:
            results.append(f"{query} infinity")
        else:
            results.append(f"{query} {dist[author_index[query]]}")

    return results


def main():
    lines = sys.stdin.readlines()
    T = int(lines[0].strip())

    line_idx = 1
    scenario = 1

    first = True

    for _ in range(T):
        if not first:
            print()
        first = False

        print(f"Scenario {scenario}")
        scenario += 1

        P = int(lines[line_idx].strip())
        N = int(lines[line_idx + 1].strip())
        line_idx += 2

        papers = []
        for _ in range(P):
            papers.append(lines[line_idx].strip())
            line_idx += 1

        queries = []
        for _ in range(N):
            queries.append(lines[line_idx].strip())
            line_idx += 1

        results = calculate_erdos_numbers(papers, queries)
        for result in results:
            print(result)


if __name__ == '__main__':
    main()
