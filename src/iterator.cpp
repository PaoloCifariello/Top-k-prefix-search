//
//  iterator.cpp
//  Top-k-prefix
//
//  Created by Paolo Cifariello on 16/11/15.
//  Copyright © 2015 Paolo Cifariello. All rights reserved.
//

#include <vector>
#include <string>

using namespace std;

class Iterator {
private:
    vector<string> data;
    int l;
    int r;
    
public:
    Iterator(vector<string> data, pair<int, int>* indexes) {
        this->data = data;
        if (indexes == nullptr) {
            this->l = data.size();
            this->r = data.size();
        } else {
            this->l = indexes->first;
            this->r = indexes->second;
        }
    }
    
    bool hasNext() {
        return l <= r && l < data.size();
    }
    
    string next() {
        return this->data.at(l++);
    }
};