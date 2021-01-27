/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream word_file(filename);
    string word;
    if (word_file.is_open()) {
        while (getline(word_file, word)) {
            dict[word];
            vector<int> char_freq(26, 0);
            for (char letter : word) {
                char_freq[letter - 'a']++;
            }
            f[char_freq].push_back(word);
        }
    }
    for (auto& word_anagrams : dict) {
        word = word_anagrams.first;
        vector<int> char_freq(26,0);
        for (char letter : word) {
            char_freq[letter - 'a']++;
        }
        //dict[word] = f[char_freq];
        word_anagrams.second = f[char_freq];
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (auto word : words) {
        dict[word];
        vector<int> char_freq(26, 0);
        for (char letter : word) {
            char_freq[letter - 'a']++;
        }
        f[char_freq].push_back(word);
    }
    for (auto& word_anagrams : dict) {
        string word = word_anagrams.first;
        vector<int> char_freq(26,0);
        for (char letter : word) {
            char_freq[letter - 'a']++;
        }
        word_anagrams.second = f[char_freq];
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */    
    vector<int> char_freq(26,0);
    for (char letter : word) {
        char_freq[letter - 'a']++;
    }
    auto temp = f.find(char_freq);
    auto lookup = dict.find(word);
    if (lookup != dict.end()) {
        if (lookup -> second.size() < 2)
            return vector<string>();
        return lookup -> second;
    }
    else
        return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> all_anagrams;
    for (auto charFreq_anagram : f) {
        if (charFreq_anagram.second.size() > 1)
            all_anagrams.push_back(charFreq_anagram.second);
    }
    return all_anagrams;
}
