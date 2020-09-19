#include <iostream>
#include <cctype>

using namespace std;

bool has_all_alphabet(string word) {
    for (int i = 'a'; i < 'z'; i++) {
        if (word.find(static_cast<char>(i)) == string::npos) {
            return false;
        }
    }
    return true;
}

bool has_only_char(string word) {
    for (int i = 0; i < static_cast<int>(word.length()); i++) {
        if (!islower(word.at(i)) || isdigit(word.at(i))) {
            return false;
        }
    }
    return true;
}

string encrypt(string key, string word) {
    const int ASCII = 97;

    for (int i = 0; i < static_cast<int>(word.length()); i++) {
        int pos = static_cast<int>(word.at(i)) - ASCII;
        word.at(i) = key.at(pos);
    }


    return word;
}

int main() {
    cout << "Enter the encryption key: ";
    string key;
    cin >> key;

    if (key.length() < 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }

    if (!has_only_char(key)) {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }

    if (!has_all_alphabet(key)) {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return EXIT_FAILURE;
    }

    cout << "Enter the text to be encrypted: ";
    string word;
    cin >> word;

    if (!has_only_char(word)) {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }

    cout << "Encrypted text: " << encrypt(key, word) << endl;

    return EXIT_SUCCESS;
}