//
//  main.cpp
//  Top-k-prefix
//
//  Created by Paolo Cifariello on 12/11/15.
//  Copyright © 2015 Paolo Cifariello. All rights reserved.
//

#include "trie.cpp"
#include <sstream>

void runTest1() {
    Trie t = Trie();
    
    int runs = 20000;
    int query = 10000;
    

    for (int i = 0; i < runs; i++) {
        std::stringstream randStr;
        
        for (int j = std::rand() * (1.0 / (RAND_MAX + 1.0)) * 10; j != 0; j--) {
            int pos = std::rand() * (1.0 / (RAND_MAX + 1.0)) * 26;
            randStr << (char) ('a' + pos);
        }
        
        if (randStr.str().length() > 0) {
            if (i == runs -1) {
                t.addWord(randStr.str(), true);
            } else {
                t.addWord(randStr.str(), false);
            }
            
        }
        
    }
    
    for (int i = 0; i < query; i++) {
        std::stringstream randStr;
        for (int j = std::rand() * (1.0 / (RAND_MAX + 1.0)) * 10; j != 0; j--) {
            int pos = std::rand() * (1.0 / (RAND_MAX + 1.0)) * 26;
            randStr << (char) ('a' + pos);
        }

        string nextString = randStr.str();
        if (nextString.length() > 3) {
            float time = clock();
            auto res = t.lookup(nextString);
            time = clock() - time;
            
            if (res.hasNext()) {
                std::cout << "Looking for " << nextString << std::endl;
                
                cout << "Query result (in " << (time*1000)/CLOCKS_PER_SEC << " milliseconds):" << endl;
                while (res.hasNext()) {
                    cout << res.next() << ", ";
                }
                cout << endl;
            }
        }
    }
    
}

int main(int argc, char *argv[]) {
    Trie trie = Trie();

    runTest1();

    return 0;
}

