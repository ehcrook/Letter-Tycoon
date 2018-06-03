//
//  Computer.hpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/28/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Computer_h
#define Computer_h

#include <vector>

#include "Patent.h"
#include "Hand.h"
#include "Strategy.h"
#include "Dictionary.h"

class Computer : public Strategy {
public:
    Computer(Dictionary &d) : Strategy(d) {}
//    string getName() { return Strategy::getName(); }
    string play(Hand hand, Hand shared, vector<Patent> patents);
    string discard(Hand hand);
    char replace(Hand hand);
    Patent buyPatent(vector<Patent> patents);
private:
    string tryWords(string letters, int length, int attempts);

};

#endif /* Computer_h */
