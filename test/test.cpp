//
//  test.cpp
//  Top-k-prefix-search
//
//  Created by Paolo Cifariello on 16/11/15.
//  Copyright © 2015 Paolo Cifariello. All rights reserved.
//


//#include <string>
//#include <iostream>
#include <sstream>

#include "../src/trie.cpp"

void runTest() {
    Trie t = Trie();
    
    int runs = 12;
    
    long start = clock();
    for (int i = 0; i < runs; i++) {
        std::stringstream randStr;
        
        for (int j = std::rand() * (1.0 / (RAND_MAX + 1.0)) * 6; j != 0; j--) {
            int pos = std::rand() * (1.0 / (RAND_MAX + 1.0)) * 26;
            randStr << (char) ('a' + pos);
        }
        std::string a = randStr.str();
        std::cout << a;
    }
    
    for (int i = 0; i < runs; i++) {
        std::stringstream randStr;
        for (int j = std::rand() * (1.0 / (RAND_MAX + 1.0)) * 6; j != 0; j--) {
            int pos = std::rand() * (1.0 / (RAND_MAX + 1.0)) * 26;
            randStr << (char) ('a' + pos);
        }
    }
  
}