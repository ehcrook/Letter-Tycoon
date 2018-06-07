//
//  Strategy.hpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/19/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Strategy_h
#define Strategy_h

#include "Patent.h"
#include "Hand.h"
#include "Dictionary.h"

using namespace std;

class Strategy {
public:
    Strategy(Dictionary &d) {
        dictionary = d;
    }
    string getName() { return name; }
    virtual string play(Hand hand, Hand shared, vector<Patent> patents) = 0;
    virtual string discard(Hand hand) = 0;
    virtual char replace(Hand hand) = 0;
    virtual Patent buyPatent(vector<Patent> patents) = 0;
    static const Patent PASS;
protected:
    string name;
    Dictionary dictionary;
};

#endif /* Strategy_h */

