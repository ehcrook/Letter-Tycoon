//
//  Strategy.hpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/19/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Strategy_h
#define Strategy_h

#include "Card.h"
#include "Hand.h"
#include "Dictionary.h"

using namespace std;

class Strategy {
public:
    Strategy(Dictionary &d) {
        dictionary = d;
    }
    string getName() { return name; }
    virtual string play(Hand hand, Hand shared) = 0;
    virtual string discard(Hand hand) = 0;
    virtual Card buyPatent(vector<Card> patents) = 0;
    static const Card PASS;
protected:
    string name;
    Dictionary dictionary;
};

#endif /* Strategy_h */

