/**
 * Poker hands
 * pc110202
 * uva10315
 */

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            Card[] black = new Card[5];
            Card[] white = new Card[5];
            PokerHands.parseInputs(input, black, white);

            PokerHands.sortHand(black);
            PokerHands.sortHand(white);

            int result = PokerHands.compareHands(black, white);

            switch (result) {
                case 1:
                    System.out.println("Black wins.");
                    break;
                case -1:
                    System.out.println("White wins.");
                    break;
                default:
                    System.out.println("Tie.");
            }
        }

        scanner.close();
    }
}
