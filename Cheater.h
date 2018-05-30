//
//  Cheater.hpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/29/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Cheater_h
#define Cheater_h

#include "Card.h"
#include "Hand.h"
#include "Computer.h"
#include "Dictionary.h"

//#include <vector>

class Cheater : public Computer {
public:
    Cheater(Dictionary &d) : Computer(d) {}
    string play(Hand hand, Hand shared);
    Card buyPatent(vector<Card> patents);
private:
    void modifyDictionary(string word);
};

#endif /* Cheater_h */
