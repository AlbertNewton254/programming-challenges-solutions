/**
 * Crypt kicker
 * pc110204
 * uva843
 */

import java.util.List;
import java.util.Arrays;

public class CryptKicker {
    private static final int ALPHSIZE = 26;
    private List<String> dictionary;

    public CryptKicker(List<String> dictionary) {
        this.dictionary = dictionary;
    }

    private boolean canMap(String cipherWord, String plainWord, char[] reverseKey, boolean[] changed) {
        for (int i = 0; i < cipherWord.length(); i++) {
            int c = cipherWord.charAt(i) - 'a';
            char p = plainWord.charAt(i);

            if (reverseKey[c] != '*') {
                if (reverseKey[c] != p) {
                    return false;
                }
            } else {
                for (int j = 0; j < ALPHSIZE; j++) {
                    if (reverseKey[j] == p) {
                        return false;
                    }
                }

                reverseKey[c] = p;
                changed[c] = true;
            }
        }

        return true;
    }

    private boolean solve(int wordIndex, String[] words, char[] reverseKey) {
        if (wordIndex >= words.length) {
            return true;
        }

        String cipherWord = words[wordIndex];
        int len = cipherWord.length();

        for (String dictWord : dictionary) {
            if (dictWord.length() != len) {
                continue;
            }

            boolean[] changed = new boolean[ALPHSIZE];

            if (canMap(cipherWord, dictWord, reverseKey, changed)) {
                if (solve(wordIndex + 1, words, reverseKey)) {
                    return true;
                }
            }

            for (int j = 0; j < ALPHSIZE; j++) {
                if (changed[j]) {
                    reverseKey[j] = '*';
                }
            }
        }

        return false;
    }

    private String[] splitWords(String line) {
        return line.split(" ");
    }

    public String solve(String crypt) {
        String[] words = splitWords(crypt);
        char[] reverseKey = new char[ALPHSIZE];
        Arrays.fill(reverseKey, '*');

        if (!solve(0, words, reverseKey)) {
            Arrays.fill(reverseKey, '*');
        }

        return kickCrypt(crypt, reverseKey);
    }

    private String kickCrypt(String crypt, char[] reverseKey) {
        StringBuilder uncrypt = new StringBuilder();

        for (char c : crypt.toCharArray()) {
            if (c == ' ') {
                uncrypt.append(' ');
            } else {
                int idx = c - 'a';
                if (reverseKey[idx] == '*') {
                    uncrypt.append('*');
                } else {
                    uncrypt.append(reverseKey[idx]);
                }
            }
        }

        return uncrypt.toString();
    }
}
