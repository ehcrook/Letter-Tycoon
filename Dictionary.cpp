//
//  Dictionary.cpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/19/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#include <fstream>
#include <vector>

#include "Dictionary.h"
#include "Card.h"
#include "Score.h"

using namespace std;

void Dictionary::load(string filename) {
    
    ifstream file(filename.c_str());
    string str;
    while(file >> str)
    dictionary.insert(str);
    
}

bool Dictionary::check(string word) {
    
    if(word.size() > 10) return false;
    if(word.size() < 3) return false;
    
    set<string>::iterator itr = dictionary.find(word);
    
    if(itr != dictionary.end()) return true;

    return false;

}

Score Dictionary::score(string word, vector<Patent> patents) {
    
    vector<Patent> used;
    int multiplier = 1;
    
    vector<Patent>::iterator itr = patents.begin();
    for (;itr!=patents.end();itr++) {
        if (itr->checkSpecialUsage(word)) {
            multiplier *= 2;
            used.push_back(*itr);
        }
    }
    
    // all words with Q in score double
    bool usedQ = false;
    if(word.find('q',0) < word.size())
    {
        multiplier *= 2;
        usedQ = true;
    }
    
    int cash;
    int stocks;
    
    switch (word.size()) {
        case 1:
        case 2:
            throw -1;
        case 3: cash = 1; stocks = 0; break;
        case 4: cash = 2; stocks = 0; break;
        case 5: cash = 3; stocks = 0; break;
        case 6: cash = 4; stocks = 1; break;
        case 7: cash = 6; stocks = 1; break;
        default:
            cash = 6; stocks = (int)word.size() - 6; break;
    }

    cash *= multiplier;
    stocks *= multiplier;
    
    return Score(cash, stocks, used, usedQ);
    
}


