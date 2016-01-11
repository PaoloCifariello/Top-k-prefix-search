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

#include "iterator.h"

class Iterator
{
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
