//
//  Dictionary.cpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/19/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#include <fstream>
#include <vector>
#include <algorithm>

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

vector<Score> Dictionary::score(string word, vector<Patent> patents) {
    
    vector<Score> scores;
    string letters = word;
    int pos = (int) word.find(",");
    
    // player is playing two words
    if (pos != string::npos) {
        
        string w1 = word.substr(0,pos);
        vector<Patent> used1 = getWordScore(w1, patents).getPatentsUsed();
        sort(used1.begin(),used1.end());
        
        string w2 = word.substr(pos+1);
        vector<Patent> used2 = getWordScore(w2, patents).getPatentsUsed();
        sort(used2.begin(),used2.end());

        // get intersecting set of used patents
        vector<Patent> both;
        set_intersection(used1.begin(), used1.end(), used2.begin(), used2.end(), both.begin());
        
        // get scores without the shared patents
        vector<Patent> p1;
        set_difference(used1.begin(), used1.end(), both.begin(), both.end(), p1.begin());
        Score s1 = getWordScore(w1, p1);

        vector<Patent> p2;
        set_difference(used2.begin(), used2.end(), both.begin(), both.end(), p2.begin());
        Score s2 = getWordScore(w2, p2);

        if (s1.getScore() > s2.getScore()) {
            s1 = getWordScore(w1, patents);
            s2 = getWordScore(w2, p2);
        }
        else {
            s1 = getWordScore(w1, p1);
            s2 = getWordScore(w2, patents);
        }
        
        scores.push_back(s1);
        scores.push_back(s2);
        
    }
    else {
        scores.push_back(getWordScore(word, patents));
    }

    return scores;
    
}

Score Dictionary::getWordScore(string word, vector<Patent> patents) {
    
    vector<Patent> used;
    
    vector<Patent>::iterator itr = patents.begin();
    for (;itr!=patents.end();itr++) {
        if (itr->checkSpecialUsage(word)) {
            used.push_back(*itr);
        }
    }
    
    // all words with Q in score double
    bool usedQ = false;
    if(word.find('q',0) < word.size()) {
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
    
    return Score(cash, stocks, used, usedQ);
    
}

