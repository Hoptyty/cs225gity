/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream words_file(word_list_fname);
    string word;
    if (words_file.is_open()) {
        while (getline(words_file, word)) {
            string removed_1st = word;
            string removed_2nd = word;
            removed_1st.erase(removed_1st.begin());
            removed_2nd.erase(removed_2nd.begin() + 1);
            if (d.homophones(word, removed_1st) && d.homophones(word, removed_2nd)) {
                ret.push_back(tuple<string, string, string>(word, removed_1st, removed_2nd));
            }
        }
    }
    return ret;
}
