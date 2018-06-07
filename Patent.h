//
//  Patent.hpp
//  Letter-Tycoon
//
//  Created by Stuart Crook on 6/2/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Patent_h
#define Patent_h

#include <string>
#include "Card.h"

using namespace std;

class Patent : public Card
{
public:
    Patent(Card c) : Card(c.getLetter(), c.getPrice()) {}
    bool checkSpecialUsage(string word);
};

#endif /* Patent_h */
