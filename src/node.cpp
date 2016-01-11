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

#include "node.h"

struct myComp {
    int starting_index;
    
    myComp(int starting_index) {
        this->starting_index = starting_index;
    }
    
    inline int operator() (const string& a, const string& b) const {
        int comparison = a.compare(this->starting_index, string::npos, b, this->starting_index, string::npos);
        return comparison < 0;
    };
};

class Node {
private:
    char label;
    int left;
    int right;
public:
    Node* leftnode;
    Node* eqnode;
    Node* rightnode;
    
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
            this->eqnode = NULL;
        } else {
            this->eqnode = new Node(strings, realsx, right - 1, starting_index + 1, true);
        }
        if (left < sx) {
            this->leftnode = NULL;
        } else {
            this->leftnode = new Node(strings, sx,  left, starting_index, false);
        }
        
        if (right > dx) {
            this->rightnode = NULL;
        } else {
            this->rightnode = new Node(strings, right,  dx, starting_index, false);
        }
    }
    
    pair<int, int>* lookup(string p, int starting_index) {
        if (starting_index >= p.length())
            return new pair<int, int>(this->left, this->right);

        char matchChar = p.at(starting_index);
        Node* r;
        
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