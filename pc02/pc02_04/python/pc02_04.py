"""
Crypt kicker
pc110204
uva843
"""

import sys


def can_map(cipher_word, plain_word, reverse_key, changed):
    """Check if cipher_word can map to plain_word with current reverse_key."""
    for i in range(len(cipher_word)):
        c = ord(cipher_word[i]) - ord('a')
        p = plain_word[i]

        if reverse_key[c] != '*':
            if reverse_key[c] != p:
                return False
        else:
            for j in range(26):
                if reverse_key[j] == p:
                    return False

            reverse_key[c] = p
            changed[c] = True

    return True


def solve(dictionary, word_index, words, reverse_key):
    """Recursively find a valid mapping."""
    if word_index >= len(words):
        return True

    cipher_word = words[word_index]
    word_len = len(cipher_word)

    for dict_word in dictionary:
        if len(dict_word) != word_len:
            continue

        changed = [False] * 26
        reverse_key_copy = reverse_key[:]

        if can_map(cipher_word, dict_word, reverse_key, changed):
            if solve(dictionary, word_index + 1, words, reverse_key):
                return True

        reverse_key[:] = reverse_key_copy

    return False


def split_words(line):
    """Split line into words."""
    return line.split()


def find_key(dictionary, crypt):
    """Find the mapping key for the cryptogram."""
    words = split_words(crypt)
    reverse_key = ['*'] * 26

    if not solve(dictionary, 0, words, reverse_key):
        reverse_key = ['*'] * 26

    return reverse_key


def kick_crypt(crypt, reverse_key):
    """Decrypt the cryptogram using the reverse key."""
    uncrypt = []

    for c in crypt:
        if c == ' ':
            uncrypt.append(' ')
        else:
            idx = ord(c) - ord('a')
            if reverse_key[idx] == '*':
                uncrypt.append('*')
            else:
                uncrypt.append(reverse_key[idx])

    return ''.join(uncrypt)


def main():
    n = int(input())
    dictionary = []
    for _ in range(n):
        dictionary.append(input().strip())

    for line in sys.stdin:
        crypt = line.rstrip('\n')
        if not crypt:
            continue

        reverse_key = find_key(dictionary, crypt)
        print(kick_crypt(crypt, reverse_key))


if __name__ == '__main__':
    main()
