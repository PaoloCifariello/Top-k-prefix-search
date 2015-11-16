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
    size_t SIZE_LIMIT = 1000;
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
        
        /* creates the succint data structure */
        rsdic::RSDicBuilder rsdb;
        rsdb.PushBack(1);
        succintTree(this->head, rsdb);
        rsdic::RSDic rsd;
        rsdb.Build(rsd);
        cout << rsd.num() << endl;
    }
    
    /* Creation of the succinct data structure */
    void succintTree(unique_ptr<Node>& node, rsdic::RSDicBuilder& rsdb) {
        if (node != nullptr) {
            if (node->leftnode != nullptr)
                rsdb.PushBack(1);
            if (node->eqnode != nullptr)
                rsdb.PushBack(1);
            if (node->rightnode != nullptr)
                rsdb.PushBack(1);
        }

        rsdb.PushBack(0);
        
        if (node->leftnode != nullptr)
            succintTree(node->leftnode, rsdb);
        if (node->eqnode != nullptr)
            succintTree(node->eqnode, rsdb);
        if (node->rightnode != nullptr)
            succintTree(node->rightnode, rsdb);
    }
public:
    /* 
     *  Trie contructor
     */
    Trie() {
        this->head = unique_ptr<Node>();
    }
    
    /**
     *  Add word to the collection
     */
    void addWord(string word) {
        this->words.push_back(word);
        
        if (this->words.size() > this->SIZE_LIMIT) {
            this->reconstruct();
        }
    }

    /**
     *  Add word to the collection and trigger the reconstruction if true is passed
     */
    void addWord(string word, bool reconstruct) {
        this->words.push_back(word);
        
        if (reconstruct) {
            this->reconstruct();
        }
    }
    
    Iterator lookup(string p) {
        pair<int, int>* indexes = this->head->lookup(p, 0);
        Iterator it = Iterator(this->dictionary, indexes);
        free(indexes);
        return it;
    }
};