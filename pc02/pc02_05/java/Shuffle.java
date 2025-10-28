/**
 * Shuffle
 * pc110205
 * uva10026
 */

import java.util.Scanner;

class Card {
    int suit;
    int value;

    Card(int suit, int value) {
        this.suit = suit;
        this.value = value;
    }

    Card(Card other) {
        this.suit = other.suit;
        this.value = other.value;
    }
}

public class Shuffle {
    private static final int NSUITS = 4;
    private static final int NCARDS = 13;
    private static final int DECK_SIZE = 52;

    private static final String[] SUIT_NAMES = {"Clubs", "Diamonds", "Hearts", "Spades"};
    private static final String[] VALUE_NAMES = {
        "2", "3", "4", "5", "6", "7", "8", "9", "10",
        "Jack", "Queen", "King", "Ace"
    };

    private int[][] shuffles;

    public Shuffle(int[][] shuffles) {
        this.shuffles = shuffles;
    }

    public void process(Scanner scanner) {
        Card[] oldDeck = new Card[DECK_SIZE];
        Card[] newDeck = new Card[DECK_SIZE];

        for (int i = 0; i < DECK_SIZE; i++) {
            oldDeck[i] = new Card(i / NCARDS, i % NCARDS);
        }

        scanner.nextLine();

        String line;
        while (scanner.hasNextLine()) {
            line = scanner.nextLine();
            if (line.isEmpty()) {
                break;
            }

            String[] parts = line.split("\\s+");
            for (String part : parts) {
                try {
                    int shuffleIdx = Integer.parseInt(part);
                    for (int i = 0; i < DECK_SIZE; i++) {
                        newDeck[i] = new Card(oldDeck[shuffles[shuffleIdx - 1][i] - 1]);
                    }

                    Card[] temp = oldDeck;
                    oldDeck = newDeck;
                    newDeck = temp;
                } catch (NumberFormatException e) {
                }
            }
        }

        for (int i = 0; i < DECK_SIZE; i++) {
            System.out.println(VALUE_NAMES[oldDeck[i].value] + " of " + SUIT_NAMES[oldDeck[i].suit]);
        }
    }
}
