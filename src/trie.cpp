//
//  trie.cpp
//  Top-k-prefix
//
//  Created by Paolo Cifariello on 12/11/15.
//  Copyright © 2015 Paolo Cifariello. All rights reserved.
//

#include "node.cpp"
#include "iterator.cpp"

class Trie {
private:
    size_t SIZE_LIMIT = 5;
    vector<string> words = vector<string>();
    vector<string> dictionary = vector<string>();
    unique_ptr<Node> head;
    
    void reconstruct() {
        dictionary.insert(dictionary.end(), words.begin(), words.end());
        words.clear();
        
        if (this->head != nullptr)
            this->head->~Node();
        this->head = unique_ptr<Node>(new Node(dictionary, 0, dictionary.size() - 1, 0, true));
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
    
    bool exists(string word) {
        for (int i = 0; i < this->words.size(); i++) {
            if (this->words.at(i).compare(word) == 0)
                return true;
        }
        return false;
    }
    
    Iterator lookup(string p) {
        pair<int, int>* indexes = this->head->lookup(p, 0);
        return Iterator(this->dictionary, indexes);
    }
};