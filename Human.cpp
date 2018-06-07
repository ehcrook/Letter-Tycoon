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
#include "Patent.h"
#include "Hand.h"

using namespace std;

string Human::play(Hand hand, Hand shared, vector<Patent> patents) {
    string word;
    cin >> word;
    return word;
}

string Human::discard(Hand hand) {
    string discards;
    cin >> discards;
    return discards;
}

char Human::replace(Hand hand) {
    string discards;
    cin >> discards;
    return discards[0];
}

Patent Human::buyPatent(vector<Patent> patents) {
    string discards;
    
    cin >> discards;

    vector<Patent>::iterator itr = patents.begin();
    for(; itr!=patents.end(); itr++) {
        if (itr->getLetter()==discards[0]) return *itr;
    }
    
    return Patent(Card('P',0));
}


