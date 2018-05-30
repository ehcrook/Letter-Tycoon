//
//  Strategy.cpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/19/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

#include "Strategy.h"
#include "Human.h"
#include "Card.h"
#include "Hand.h"

using namespace std;

string Human::play(Hand hand, Hand shared) {
    string word;
    cin >> word;
    return word;
}

string Human::discard(Hand hand) {
    string discards;
    cin >> discards;
    return discards;
}

Card Human::buyPatent(vector<Card> patents) {
    string discards;
    
    cin >> discards;

    vector<Card>::iterator itr = patents.begin();
    for(; itr!=patents.end(); itr++) {
        if (itr->letter==discards[0]) return *itr;
    }
    
    return Card('P',0);
}


