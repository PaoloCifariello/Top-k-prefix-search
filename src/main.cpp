//
//  main.cpp
//  Top-k-prefix
//
//  Created by Paolo Cifariello on 12/11/15.
//  Copyright © 2015 Paolo Cifariello. All rights reserved.
//

#include "trie.cpp"

std::vector<string> words {
    "antani",
    "anti",
    "anta",
    "ciao",
    "ciccia",
    "cane",
    "shock",
    "base",
    "cast",
    "book",
    "bed",
    "bar"

};

std::vector<string> query {
    "ci",
    "cic",
    "ant",
    "anta",
    "bi",
    "ba",
    "b"
};

int main(int argc, char *argv[]) {
    Trie trie = Trie();
    
    for(std::size_t i = 0; i != words.size(); ++i) {
        std::cout << "Inserting " << words.at(i) << std::endl;
        trie.addWord(words.at(i));
    }
    
    for(std::size_t i = 0; i != query.size(); ++i) {
        std::cout << "Looking for " << query.at(i) << std::endl;
        auto res = trie.lookup(query.at(i));

        cout << "Found: ";
        while (res.hasNext()) {
            cout << res.next() << ", ";
        }
        
        cout << endl;
    }

    return 0;
}