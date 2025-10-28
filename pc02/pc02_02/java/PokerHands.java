/**
 * Poker hands
 * pc110202
 * uva10315
 */

class Card {
    int value;
    int suit;

    public Card(int value, int suit) {
        this.value = value;
        this.suit = suit;
    }
}

public class PokerHands {
    static int charToValue(char c) {
        String values = "23456789TJQKA";
        return values.indexOf(c);
    }

    static int charToSuit(char c) {
        String suits = "CDHS";
        return suits.indexOf(c);
    }

    static void parseInputs(String input, Card[] black, Card[] white) {
        for (int i = 0; i < 5; i++) {
            black[i] = new Card(charToValue(input.charAt(i * 3)),
                                charToSuit(input.charAt(i * 3 + 1)));
            white[i] = new Card(charToValue(input.charAt(15 + i * 3)),
                                charToSuit(input.charAt(15 + i * 3 + 1)));
        }
    }

    static void sortHand(Card[] hand) {
        for (int i = 0; i < 5; i++) {
            for (int j = i + 1; j < 5; j++) {
                if (hand[i].value > hand[j].value) {
                    Card tmp = hand[i];
                    hand[i] = hand[j];
                    hand[j] = tmp;
                }
            }
        }
    }

    static boolean isFlush(Card[] hand) {
        int suit = hand[0].suit;
        for (int i = 1; i < 5; i++) {
            if (hand[i].suit != suit) return false;
        }
        return true;
    }

    static boolean isStraight(Card[] hand) {
        for (int i = 1; i < 5; i++) {
            if (hand[i].value != hand[i - 1].value + 1) {
                if (i == 4 &&
                    hand[0].value == 0 &&
                    hand[1].value == 1 &&
                    hand[2].value == 2 &&
                    hand[3].value == 3 &&
                    hand[4].value == 12) {
                    return true;
                }
                return false;
            }
        }
        return true;
    }

    static void getValueCounts(Card[] hand, int[] counts) {
        for (int i = 0; i < 13; i++) {
            counts[i] = 0;
        }

        for (int i = 0; i < 5; i++) {
            counts[hand[i].value]++;
        }
    }

    static int classifyHand(Card[] hand, int[] tiebreakers) {
        int[] counts = new int[13];
        getValueCounts(hand, counts);

        int pairs = 0;
        int three = 0;
        int four = 0;

        int[] pairValues = new int[2];
        int threeValue = -1;
        int fourValue = -1;

        for (int value = 0; value < 13; value++) {
            if (counts[value] == 4) {
                fourValue = value;
            } else if (counts[value] == 3) {
                threeValue = value;
            } else if (counts[value] == 2) {
                pairValues[pairs++] = value;
            }
        }

        boolean flush = isFlush(hand);
        boolean straight = isStraight(hand);
        int highest = hand[4].value;

        if (straight && flush) {
            tiebreakers[0] = highest;
            return 8;
        }

        if (fourValue != -1) {
            tiebreakers[0] = fourValue;
            return 7;
        }

        if (threeValue != -1 && pairs == 1) {
            tiebreakers[0] = threeValue;
            return 6;
        }

        if (flush) {
            for (int i = 0; i < 5; i++) {
                tiebreakers[i] = hand[4 - i].value;
            }
            return 5;
        }

        if (straight) {
            tiebreakers[0] = highest;
            return 4;
        }

        if (threeValue != -1) {
            tiebreakers[0] = threeValue;
            return 3;
        }

        if (pairs == 2) {
            if (pairValues[0] > pairValues[1]) {
                tiebreakers[0] = pairValues[0];
                tiebreakers[1] = pairValues[1];
            } else {
                tiebreakers[0] = pairValues[1];
                tiebreakers[1] = pairValues[0];
            }
            for (int i = 4; i >= 0; i--) {
                if (hand[i].value != pairValues[0] && hand[i].value != pairValues[1]) {
                    tiebreakers[2] = hand[i].value;
                    break;
                }
            }
            return 2;
        }

        if (pairs == 1) {
            tiebreakers[0] = pairValues[0];
            int idx = 1;
            for (int i = 4; i >= 0; i--) {
                if (hand[i].value != pairValues[0]) {
                    tiebreakers[idx++] = hand[i].value;
                }
            }
            return 1;
        }

        for (int i = 0; i < 5; i++) {
            tiebreakers[i] = hand[4 - i].value;
        }
        return 0;
    }

    static int compareHands(Card[] black, Card[] white) {
        int[] bTie = new int[5];
        int[] wTie = new int[5];

        int bRank = classifyHand(black, bTie);
        int wRank = classifyHand(white, wTie);

        if (bRank < wRank) {
            return 1;
        }

        if (bRank > wRank) {
            return -1;
        }

        for (int i = 0; i < 5; i++) {
            if (bTie[i] > wTie[i]) {
                return 1;
            }

            if (bTie[i] < wTie[i]) {
                return -1;
            }
        }

        return 0;
    }
}
