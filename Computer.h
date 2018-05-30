//
//  Computer.hpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/28/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Computer_h
#define Computer_h

#include "Card.h"
#include "Hand.h"
#include "Strategy.h"
#include "Dictionary.h"

class Computer : public Strategy {
public:
    Computer(Dictionary &d) : Strategy(d) {}
//    string getName() { return Strategy::getName(); }
    string play(Hand hand, Hand shared);
    string discard(Hand hand);
    Card buyPatent(vector<Card> patents);    
private:
    string tryWords(string letters, int length, int attempts);

};

#endif /* Computer_h */
