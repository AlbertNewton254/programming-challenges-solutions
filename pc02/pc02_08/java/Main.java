/**
 * Yahtzee
 * pc110208
 * uva10149
 */

import java.util.*;
import java.io.*;

public class Main {
    private static final int TOTAL_ROUNDS = 13;
    private static final int DICES_PER_ROUND = 5;

    public static void main(String[] args) {
        YahtzeeSolver solver = new YahtzeeSolver();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            List<List<Integer>> game_dices = new ArrayList<>();
            boolean valid_game = true;

            for (int i = 0; i < TOTAL_ROUNDS; i++) {
                if (!scanner.hasNextLine()) {
                    valid_game = false;
                    break;
                }

                String line = scanner.nextLine().trim();
                if (line.isEmpty()) {
                    valid_game = false;
                    break;
                }

                String[] tokens = line.split("\\s+");
                if (tokens.length != DICES_PER_ROUND) {
                    valid_game = false;
                    break;
                }

                List<Integer> dice = new ArrayList<>();
                try {
                    for (int j = 0; j < DICES_PER_ROUND; j++) {
                        dice.add(Integer.parseInt(tokens[j]));
                    }
                } catch (NumberFormatException e) {
                    valid_game = false;
                    break;
                }

                game_dices.add(dice);
            }

            if (!valid_game || game_dices.size() != TOTAL_ROUNDS) break;

            List<Integer> result = solver.solve(game_dices);

            for (int i = 0; i < result.size(); i++) {
                System.out.print(result.get(i));
                if (i < result.size() - 1) System.out.print(" ");
            }
            System.out.println();
        }

        scanner.close();
    }
}
