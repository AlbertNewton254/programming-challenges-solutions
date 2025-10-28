/**
 * Australian voting
 * pc110108
 * uva10142
 */

import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;

public class AustralianVoting {
    private static final int MAX_CANDIDATES = 20;
    private static final int MAX_VOTERS = 1000;

    private Scanner scanner;
    private Candidate[] candidates;
    private ArrayList<Voter> voters;

    public AustralianVoting() {
        scanner = new Scanner(System.in);
    }

    private void readCandidates(int n) {
        candidates = new Candidate[n];
        scanner.nextLine();

        for (int i = 0; i < n; i++) {
            candidates[i] = new Candidate(scanner.nextLine());
        }
    }

    private void readVotes(int numCandidates) {
        voters = new ArrayList<>();
        String line;

        while (scanner.hasNextLine() && !(line = scanner.nextLine()).isEmpty()) {
            Voter voter = new Voter(numCandidates);
            String[] parts = line.trim().split("\\s+");

            for (int i = 0; i < numCandidates; i++) {
                voter.preferences[i] = Integer.parseInt(parts[i]) - 1;
            }

            voters.add(voter);
        }
    }

    private void countVotes(int[] counts) {
        Arrays.fill(counts, 0);

        for (Voter voter : voters) {
            int pref = voter.currentPreference;
            while (pref < candidates.length && candidates[voter.preferences[pref]].eliminated) {
                pref++;
            }
            if (pref < candidates.length) {
                counts[voter.preferences[pref]]++;
            }
        }
    }

    private void eliminateCandidates(int[] counts, int minVotes) {
        for (int i = 0; i < candidates.length; i++) {
            if (!candidates[i].eliminated && counts[i] == minVotes) {
                candidates[i].eliminated = true;
            }
        }
    }

    public void run() {
        int cases = Integer.parseInt(scanner.nextLine());

        for (int c = 0; c < cases; c++) {
            if (c > 0) System.out.println();

            int numCandidates = Integer.parseInt(scanner.nextLine());
            readCandidates(numCandidates);
            readVotes(numCandidates);

            while (true) {
                int[] counts = new int[numCandidates];
                countVotes(counts);

                int maxVotes = 0, minVotes = voters.size() + 1;
                int remaining = 0;

                for (int i = 0; i < numCandidates; i++) {
                    if (!candidates[i].eliminated) {
                        remaining++;
                        maxVotes = Math.max(maxVotes, counts[i]);
                        minVotes = Math.min(minVotes, counts[i]);
                    }
                }

                if (maxVotes > voters.size() / 2 || remaining <= 1) {
                    for (int i = 0; i < numCandidates; i++) {
                        if (!candidates[i].eliminated && counts[i] == maxVotes) {
                            System.out.println(candidates[i].name);
                        }
                    }
                    break;
                }

                eliminateCandidates(counts, minVotes);
            }
        }

        scanner.close();
    }
}