#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cctype>
#include <iomanip>

using namespace std;

void display_frequency(const unordered_map<char, int> &freq);
void display_results(const string &cipher, const string &key);
void display_results(const string &cipher, const unordered_map<char, char> &key);
unordered_map<char, char> get_decryption_map(const string &key);

int main()
{
    string ciphertext, clean_cipher, key_input, option;
    unordered_map<char, int> freq;

    cout << "---- Enter Ciphertext ----\n";
    getline(cin, ciphertext);

    // clean ciphertext - make sure only alphabetic characters
    for (const char &ch : ciphertext)
    {
        if (!isalpha(ch))
            continue;
        clean_cipher += ch;
    }

    // get frequency of letters
    for (const char &ch : clean_cipher)
    {
        freq[ch]++;
    }

    // display frequency of letters in ciphertext
    display_frequency(freq);

    cout << "\nHow would you like to decrypt the text?\n";
    cout << "1. Enter full key\n";
    cout << "2. Build key one by one\n";
    getline(cin, option);

    if (option == "1")
    {
        cout << "\n---- Enter key ----\n";
        while (getline(cin, key_input))
        {
            // make the key always be uppercase
            transform(key_input.begin(), key_input.end(), key_input.begin(), ::toupper);

            cout << "\n---- Decryption Results ----\n";
            display_results(clean_cipher, key_input);
            cout << "\n---- Enter new key ----\n";
        }
    }
    else if (option == "2")
    {
        string line;
        unordered_map<char, char> key_builder;

        cout << "\n---- Key builder loop----\n";
        cout << "Enter mapping as 'CipherChar=PlainChar' (ex. C=a)\n";

        // build the map one mapping at time
        while (getline(cin, line))
        {
            char cipher_char = line[0];
            char plain_char = line[2];
            key_builder[toupper(cipher_char)] = plain_char;

            // display results when key is built
            if (key_builder.size() == 26)
            {
                cout << "Key built. Showing results\n";

                display_results(clean_cipher, key_builder);
            }
            // let user choose to display current decryption result
            else    
            {
                string display_opt;
                cout << "Would you like to see the current decryption? Y or N \n";
                getline(cin, display_opt);
                if (display_opt == "Y")
                {
                    display_results(clean_cipher, key_builder);
                }
            }
            cout << "Enter new mapping ['CipherChar=PlainChar' (ex. C=a)]\n";
        }
    }

    return 0;
}

void display_frequency(const unordered_map<char, int> &freq)
{
    cout << "\n---- Frequency of Letters ----\n\n";
    cout << string(20, '-') << endl;
    cout << left << setw(8) << "Letter" << ": " << right << setw(10) << "Frequency" << endl;
    cout << string(20, '-') << endl;

    for (const pair<char, int> &p : freq)
    {
        cout << left << setw(8) << p.first << ": " << right << setw(10) << p.second << endl;
    }
    cout << string(20, '-') << endl;
}

void display_results(const string &cipher, const string &key)
{
    unordered_map<char, char> decrypt_map = get_decryption_map(key);
    for (const char &ch : cipher)
    {
        cout << decrypt_map.at(ch);
    }
    cout << endl;
}

void display_results(const string &cipher, const unordered_map<char, char> &key)
{
    for (const char &ch : cipher)
    {
        if (key.find(ch) != key.end())
        {
            cout << key.at(ch);
        }
        else
        {
            cout << ch;
        }
    }
    cout << endl;
}

unordered_map<char, char> get_decryption_map(const string &key)
{
    unordered_map<char, char> decrypt_map;
    cout << key << endl;
    char base = 'a';

    for (const char &ch : key)
    {
        decrypt_map[ch] = base;
        base++;
    }
    return decrypt_map;
}
