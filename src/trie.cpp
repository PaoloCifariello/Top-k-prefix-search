//
//  trie.cpp
//  Top-k-prefix
//
//  Created by Paolo Cifariello on 12/11/15.
//  Copyright © 2015 Paolo Cifariello. All rights reserved.
//

#include "node.cpp"
#include "iterator.cpp"

#include "../lib/rsdic/RSDicBuilder.hpp"
#include "../lib/rsdic/RSDic.hpp"

class Trie {
private:
    size_t SIZE_LIMIT = 99999;
    vector<string> words = vector<string>();
    vector<string> dictionary = vector<string>();
    unique_ptr<Node> head;
    
    void reconstruct() {
        dictionary.insert(dictionary.end(), words.begin(), words.end());
        words.clear();
        
        if (this->head != nullptr)
            this->head->~Node();
        
        /* Remove duplicates */
        sort(dictionary.begin(), dictionary.end());
        dictionary.erase(unique(dictionary.begin(), dictionary.end()), dictionary.end());
        this->head = unique_ptr<Node>(new Node(dictionary, 0, dictionary.size() - 1, 0, false));
    }
public:
    // Trie contructor
    Trie() {
        this->head = unique_ptr<Node>();
    }
    
    void addWord(string word) {
        this->words.push_back(word);
        
        if (this->words.size() > this->SIZE_LIMIT) {
            this->reconstruct();
        }
    }

    void addWord(string word, bool reconstruct) {
        this->words.push_back(word);
        
        if (reconstruct) {
            this->reconstruct();
        }
    }
    
    bool exists(string word) {
        for (int i = 0; i < this->words.size(); i++) {
            if (this->words.at(i).compare(word) == 0)
                return true;
        }
        return false;
    }
    
    Iterator lookup(string p) {
        pair<int, int>* indexes = this->head->lookup(p, 0);
        Iterator it = Iterator(this->dictionary, indexes);
        free(indexes);
        return it;
    }
};