//
//  trie_node.cpp
//  Top-k-prefix
//
//  Created by Paolo Cifariello on 12/11/15.
//  Copyright © 2015 Paolo Cifariello. All rights reserved.
//

#include <stdio.h>

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct myComp {
    int starting_index;
    
    myComp(int starting_index) {
        this->starting_index = starting_index;
    }
    
    inline int operator() (const string& a, const string& b) const {
        int comparison = a.compare(this->starting_index, string::npos, b, this->starting_index);
        return comparison < 0;
    };
};

class Node {
private:
    const static int FANOUT = 1;
    char labels[FANOUT];
    unique_ptr<Node> children[2 * FANOUT + 1];
    int left;
    int right;
    
public:
    Node(vector<string> &strings, int sx, int dx, int starting_index, bool to_sort) {
        if (starting_index > 6) {
            return;
        }
        
        if (to_sort) {
            /* Sort the string by starting at starting_index */
            sort(strings.begin() + sx, strings.begin() + dx + 1, myComp(starting_index));
        }
        
        /* Find half string at its character at starting_index in order to choose node label */
        int half = (sx + dx)/2;
        char label = strings.at(half)[starting_index];
        this->labels[0] = label;
        
        int left = half - 1;
        int right = half + 1;
        
        while (left >= sx && strings.at(left)[starting_index] == label) {
            left--;
        }
        
        while (right <= dx && strings.at(right)[starting_index] == label) {
            right++;
        }

        this->left = sx;
        this->right = dx;
        
        int realsx = left + 1;
        
        while (realsx <= right - 1 && strings.at(realsx).length() < starting_index + 1) {
            realsx++;
        }
        
        if (realsx > right - 1) {
            this->children[1] = nullptr;
        } else {
            this->children[1] = unique_ptr<Node>(new Node(strings, realsx, right - 1, starting_index + 1, true));
        }
        if (left < sx) {
            this->children[0] = nullptr;
        } else {
            this->children[0] = unique_ptr<Node>(new Node(strings, sx,  left, starting_index, false));
        }
        
        if (right > dx) {
            this->children[2] = nullptr;
        } else {
            this->children[2] = unique_ptr<Node>(new Node(strings, right,  dx, starting_index, false));
        }
    }
    
    pair<int, int>* lookup(string p, int starting_index) {
        if (starting_index >= p.length())
            return new pair<int, int>(this->left, this->right);

        char matchChar = p.at(starting_index);
        unique_ptr<Node> r;
        
        if (matchChar == this->labels[0]) {
            if (children[1] == nullptr)
                return NULL;

            return this->children[1]->lookup(p, starting_index + 1);
        } else if (matchChar < this->labels[0]) {
            if (children[0] == nullptr)
                return NULL;

            return this->children[0]->lookup(p, starting_index);
        } else {
            if (children[2] == nullptr)
                return NULL;

            return this->children[2]->lookup(p, starting_index);
        }
    }
};