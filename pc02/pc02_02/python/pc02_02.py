"""
Poker hands
pc110202
uva10315
"""


class Card:
    def __init__(self, value, suit):
        self.value = value
        self.suit = suit


def char_to_value(c):
    """Convert card value character to integer."""
    values = "23456789TJQKA"
    return values.index(c)


def char_to_suit(c):
    """Convert card suit character to integer."""
    suits = "CDHS"
    return suits.index(c)


def parse_inputs(input_str):
    """Parse 10 cards from input string into black[5] and white[5]."""
    black = []
    white = []

    for i in range(5):
        black.append(Card(char_to_value(input_str[i * 3]),
                         char_to_suit(input_str[i * 3 + 1])))
        white.append(Card(char_to_value(input_str[15 + i * 3]),
                         char_to_suit(input_str[15 + i * 3 + 1])))

    return black, white


def sort_hand(hand):
    """Sort hand by card value."""
    hand.sort(key=lambda card: card.value)


def is_flush(hand):
    """Check if hand is a flush."""
    suit = hand[0].suit
    for i in range(1, 5):
        if hand[i].suit != suit:
            return False
    return True


def is_straight(hand):
    """Check if hand is a straight."""
    for i in range(1, 5):
        if hand[i].value != hand[i - 1].value + 1:
            if (i == 4 and
                hand[0].value == 0 and
                hand[1].value == 1 and
                hand[2].value == 2 and
                hand[3].value == 3 and
                hand[4].value == 12):
                return True
            return False
    return True


def get_value_counts(hand):
    """Get count of each card value."""
    counts = [0] * 13
    for card in hand:
        counts[card.value] += 1
    return counts


def classify_hand(hand):
    """Classify hand and return (rank, tiebreakers)."""
    counts = get_value_counts(hand)

    pairs = []
    three_value = -1
    four_value = -1

    for value in range(13):
        if counts[value] == 4:
            four_value = value
        elif counts[value] == 3:
            three_value = value
        elif counts[value] == 2:
            pairs.append(value)

    flush = is_flush(hand)
    straight = is_straight(hand)
    highest = hand[4].value

    tiebreakers = [0] * 5

    if straight and flush:
        tiebreakers[0] = highest
        return 8, tiebreakers

    if four_value != -1:
        tiebreakers[0] = four_value
        return 7, tiebreakers

    if three_value != -1 and len(pairs) == 1:
        tiebreakers[0] = three_value
        return 6, tiebreakers

    if flush:
        for i in range(5):
            tiebreakers[i] = hand[4 - i].value
        return 5, tiebreakers

    if straight:
        tiebreakers[0] = highest
        return 4, tiebreakers

    if three_value != -1:
        tiebreakers[0] = three_value
        return 3, tiebreakers

    if len(pairs) == 2:
        if pairs[0] > pairs[1]:
            tiebreakers[0] = pairs[0]
            tiebreakers[1] = pairs[1]
        else:
            tiebreakers[0] = pairs[1]
            tiebreakers[1] = pairs[0]

        for i in range(4, -1, -1):
            if hand[i].value != pairs[0] and hand[i].value != pairs[1]:
                tiebreakers[2] = hand[i].value
                break

        return 2, tiebreakers

    if len(pairs) == 1:
        tiebreakers[0] = pairs[0]
        idx = 1
        for i in range(4, -1, -1):
            if hand[i].value != pairs[0]:
                tiebreakers[idx] = hand[i].value
                idx += 1

        return 1, tiebreakers

    for i in range(5):
        tiebreakers[i] = hand[4 - i].value

    return 0, tiebreakers


def compare_hands(black, white):
    """Compare two hands and return winner."""
    b_rank, b_tie = classify_hand(black)
    w_rank, w_tie = classify_hand(white)

    if b_rank > w_rank:
        return "Black"

    if b_rank < w_rank:
        return "White"

    for i in range(5):
        if b_tie[i] > w_tie[i]:
            return "Black"

        if b_tie[i] < w_tie[i]:
            return "White"

    return "Tie"


def main():
    import sys
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue

        black, white = parse_inputs(line)
        sort_hand(black)
        sort_hand(white)

        result = compare_hands(black, white)

        if result == "Black":
            print("Black wins.")
        elif result == "White":
            print("White wins.")
        else:
            print("Tie.")


if __name__ == '__main__':
    main()
