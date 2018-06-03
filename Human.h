//
//  Human.h
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/28/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Human_h
#define Human_h

#include "Patent.h"
#include "Hand.h"
#include "Strategy.h"
#include "Dictionary.h"

//#include <vector>

class Human : public Strategy {
public:
    Human(Dictionary &d) : Strategy(d) {}
//    string getName() { return Strategy::getName(); }
    string play(Hand hand, Hand shared, vector<Patent> patents);
    string discard(Hand hand);
    char replace(Hand hand);
    Patent buyPatent(vector<Patent> patents);
    static const Patent PASS;
};

#endif /* Human_h */
