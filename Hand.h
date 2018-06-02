//
//  Hand.hpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/26/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Hand_h
#define Hand_h

//#include <stdio.h>

#include <vector>
#include <iostream>
#include <algorithm>
//#include <map>

#include "Card.h"

using namespace std;

class Hand
{
public:
    
    Hand() {}
    
    Hand(vector<Card> cards) {
        hand.insert(hand.end(),cards.begin(),cards.end());
    }
    
    string output();
    
    int getSize() {
        return (int)hand.size();
    }
    
    string getLetters();
    
//    vector<Card> getCards() {
//        vector<Card> cards(hand);
//        return cards;
//    }

    void shuffle() {
        random_shuffle(hand.begin(), hand.end());
    }
    
    void add(Hand cards) {
        hand.insert(hand.end(),cards.hand.begin(),cards.hand.end());
    }
    
    void add(Card card) {
        hand.push_back(card);
    }
    
//    void remove(vector<Card> cards) {
//        vector<Card>::iterator card = cards.begin();
//        for(;card!=cards.end();card++)
//            hand.erase(card);
//    }
    
    void remove(Card card) {
        vector<Card>::iterator itr = find(hand.begin(),hand.end(),card);
        //cout << itr->letter << " found." << endl;
        hand.erase(itr);
    }

    Card getCard(char letter);
            
protected:
    vector<Card> hand;
    
};

#endif

