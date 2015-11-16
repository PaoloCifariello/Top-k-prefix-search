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
    char label;
    int left;
    int right;
public:
    unique_ptr<Node> leftnode;
    unique_ptr<Node> eqnode;
    unique_ptr<Node> rightnode;
    
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
        this->label = label;
        
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
            this->eqnode = nullptr;
        } else {
            this->eqnode = unique_ptr<Node>(new Node(strings, realsx, right - 1, starting_index + 1, true));
        }
        if (left < sx) {
            this->leftnode = nullptr;
        } else {
            this->leftnode = unique_ptr<Node>(new Node(strings, sx,  left, starting_index, false));
        }
        
        if (right > dx) {
            this->rightnode = nullptr;
        } else {
            this->rightnode = unique_ptr<Node>(new Node(strings, right,  dx, starting_index, false));
        }
    }
    
    pair<int, int>* lookup(string p, int starting_index) {
        if (starting_index >= p.length())
            return new pair<int, int>(this->left, this->right);

        char matchChar = p.at(starting_index);
        unique_ptr<Node> r;
        
        if (matchChar == this->label) {
            if (this->eqnode == nullptr)
                return NULL;

            return this->eqnode->lookup(p, starting_index + 1);
        } else if (matchChar < this->label) {
            if (this->leftnode == nullptr)
                return NULL;

            return this->leftnode->lookup(p, starting_index);
        } else {
            if (this->rightnode == nullptr)
                return NULL;

            return this->rightnode->lookup(p, starting_index);
        }
    }
};