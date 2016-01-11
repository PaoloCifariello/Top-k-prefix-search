/*
 * Copyright 2016 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#include "trie.h"

class Trie {
private:
    size_t SIZE_LIMIT = 1000;
    vector<string> words = vector<string>();
    vector<string> dictionary = vector<string>();
   Node* head;
    
    void reconstruct() {
        dictionary.insert(dictionary.end(), words.begin(), words.end());
        words.clear();
        
        if (this->head != NULL)
            delete this->head;
        
        /* Remove duplicates */
        sort(dictionary.begin(), dictionary.end());
        dictionary.erase(unique(dictionary.begin(), dictionary.end()), dictionary.end());
        this->head = new Node(dictionary, 0, dictionary.size() - 1, 0, false);
        
        /* creates the succint data structure */
        //rsdic::RSDicBuilder rsdb;
        //rsdb.PushBack(1);
        //succintTree(this->head, rsdb);
        //rsdic::RSDic rsd;
        //rsdb.Build(rsd);
        //cout << rsd.num() << endl;
    }
    
    /* Creation of the succinct data structure */
//     void succintTree(Node* node, rsdic::RSDicBuilder& rsdb) {
//         if (node != NULL) {
//             if (node->leftnode != NULL)
//                 rsdb.PushBack(1);
//             if (node->eqnode != NULL)
//                 rsdb.PushBack(1);
//             if (node->rightnode != NULL)
//                 rsdb.PushBack(1);
//         }
// 
//         rsdb.PushBack(0);
//         
//         if (node->leftnode != nullptr)
//             succintTree(node->leftnode, rsdb);
//         if (node->eqnode != nullptr)
//             succintTree(node->eqnode, rsdb);
//         if (node->rightnode != nullptr)
//             succintTree(node->rightnode, rsdb);
//     }
public:
    /* 
     *  Trie contructor
     */
    Trie() {
        this->head = NULL;
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