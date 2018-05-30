//
//  Hand.cpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/26/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#include "Hand.h"

#include <string>

string Hand::output()
{
    string o;
    for(unsigned int i = 0; i < hand.size(); i++) {
        o.push_back(hand[i].letter);
        if(i < hand.size()-1) o.push_back(' ');
    }
    //o.pop_back();
    return o;
}

Card Hand::getCard(char letter) {
    for(unsigned int i = 0; i < hand.size(); i++) {
        if (hand[i].letter==letter)
            return hand[i];
    }
    throw letter;
}

string Hand::getLetters() {
    string o;
    for(unsigned int i = 0; i < hand.size(); i++)
        o.push_back(hand[i].letter);
    return o;
}
