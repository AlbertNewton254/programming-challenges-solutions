/**
 * Erdos numbers
 * pc110206
 * uva10044
 */

import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Queue;
import java.util.LinkedList;

public class ErdosCalculator {
    private Map<String, Integer> authorIndex;
    private List<List<Integer>> graph;
    private int nextIndex;
    private int[] dist;

    public ErdosCalculator() {
        this.authorIndex = new HashMap<>();
        this.graph = new ArrayList<>();
        this.nextIndex = 0;

        for (int i = 0; i < 10000; i++) {
            this.graph.add(new ArrayList<>());
        }
    }

    public void addPaper(String paper) {
        List<Integer> authorIds = getAuthors(paper);

        for (int i = 0; i < authorIds.size(); i++) {
            for (int j = i + 1; j < authorIds.size(); j++) {
                int u = authorIds.get(i);
                int v = authorIds.get(j);
                graph.get(u).add(v);
                graph.get(v).add(u);
            }
        }
    }

    private List<Integer> getAuthors(String paper) {
        List<Integer> authorIds = new ArrayList<>();
        int colonPos = paper.indexOf(':');
        String authorPart = (colonPos != -1) ? paper.substring(0, colonPos) : paper;

        String[] parts = authorPart.split(",");
        List<String> trimmedParts = new ArrayList<>();

        for (String part : parts) {
            String trimmed = part.trim();
            if (!trimmed.isEmpty()) {
                trimmedParts.add(trimmed);
            }
        }

        for (int i = 0; i + 1 < trimmedParts.size(); i += 2) {
            String author = trimmedParts.get(i) + ", " + trimmedParts.get(i + 1);

            if (!authorIndex.containsKey(author)) {
                authorIndex.put(author, nextIndex++);
            }
            authorIds.add(authorIndex.get(author));
        }

        return authorIds;
    }

    public void calculateDistances() {
        this.dist = new int[nextIndex];
        for (int i = 0; i < nextIndex; i++) {
            dist[i] = -1;
        }

        if (authorIndex.containsKey("Erdos, P.")) {
            int erdosId = authorIndex.get("Erdos, P.");
            Queue<Integer> q = new LinkedList<>();
            q.offer(erdosId);
            dist[erdosId] = 0;

            while (!q.isEmpty()) {
                int u = q.poll();

                for (int v : graph.get(u)) {
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.offer(v);
                    }
                }
            }
        }
    }

    public int getDistance(String author) {
        if (!authorIndex.containsKey(author)) {
            return -1;
        }

        int id = authorIndex.get(author);
        return dist[id];
    }
}
