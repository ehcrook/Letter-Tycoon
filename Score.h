//
//  Score.hpp
//  Letter-Tycoon
//
//  Created by Stuart Crook on 6/2/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Score_h
#define Score_h

#include <math.h>
#include <vector>

#include "Patent.h"

using namespace std;

class Score {
public:
    Score(int c, int s, vector<Patent> p, bool usedQ) {
        cash = c;
        stocks = s;
        patents = p;
        q = usedQ;
        bonus = pow(2,(int)p.size() + (usedQ ? 1 : 0));
    }
    int getCash() {
        return cash;
    }
    int getStocks() {
        return stocks;
    }
    int getBonus() {
        return bonus;
    }
    vector<Patent> getPatentsUsed() {
        return patents;
    }
    int getValue() {
        return cash + stocks;
    }
    bool usedQ() {
        return q;
    }
    int getScore() {
        return getBonus() * getValue();
    }
private:
    int cash;
    int stocks;
    int bonus;
    bool q;
    vector<Patent> patents;
    
};

#endif /* Score_h */
