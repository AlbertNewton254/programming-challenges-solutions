/**
 * Crypt kicker
 * pc110204
 * uva843
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int ALPHSIZE = 26;

bool canMap(const string& cipherWord, const string& plainWord,
            vector<char>& reverseKey, vector<int>& changed) {
    for (int i = 0; i < cipherWord.length(); i++) {
        int c = cipherWord[i] - 'a';
        char p = plainWord[i];

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
            changed[c] = 1;
        }
    }

    return true;
}

bool solve(const vector<string>& dict, int wordIndex, const vector<string>& words,
           vector<char>& reverseKey) {
    if (wordIndex >= words.size()) {
        return true;
    }

    string cipherWord = words[wordIndex];
    int len = cipherWord.length();

    for (const string& dictWord : dict) {
        if (dictWord.length() != len) {
            continue;
        }

        vector<int> changed(ALPHSIZE, 0);

        if (canMap(cipherWord, dictWord, reverseKey, changed)) {
            if (solve(dict, wordIndex + 1, words, reverseKey)) {
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

vector<string> splitWords(const string& line) {
    vector<string> words;
    string word;

    for (char c : line) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

void findKey(const vector<string>& dict, const string& crypt,
             vector<char>& reverseKey) {
    vector<string> words = splitWords(crypt);

    if (!solve(dict, 0, words, reverseKey)) {
        fill(reverseKey.begin(), reverseKey.end(), '*');
    }
}

string kickCrypt(const string& crypt, const vector<char>& reverseKey) {
    string uncrypt;

    for (char c : crypt) {
        if (c == ' ') {
            uncrypt += ' ';
        } else {
            int idx = c - 'a';
            if (reverseKey[idx] == '*') {
                uncrypt += '*';
            } else {
                uncrypt += reverseKey[idx];
            }
        }
    }

    return uncrypt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cin.ignore();

    vector<string> dict(n);
    for (int i = 0; i < n; i++) {
        getline(cin, dict[i]);
    }

    string crypt;
    while (getline(cin, crypt)) {
        if (crypt.empty()) continue;

        vector<char> reverseKey(ALPHSIZE, '*');

        findKey(dict, crypt, reverseKey);

        cout << kickCrypt(crypt, reverseKey) << '\n';
    }

    return 0;
}
