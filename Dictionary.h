//
//  Dictionary.h
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/19/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Dictionary_h
#define Dictionary_h

#include <set>
#include <string>
#include <vector>

#include "Patent.h"
#include "Score.h"

using namespace std;

class Dictionary
{
public:
    Dictionary(){}
    void load(string file);
    bool check(string word);
    Score score(string word, vector<Patent> patents);
    int getSize() { return (int)dictionary.size(); }
    
private:
    set<string> dictionary;
};

#endif /* Dictionary_h */
