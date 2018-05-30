//
//  Deck.cpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/19/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

//#include <iostream>
//#include <map>
#include <vector>
#include <string>

#include "Deck.h"

using namespace std;

string Deck::output() {
    string o;
    o.append("Deck=" + to_string(hand.size()));
    o.append("; Discards=" + to_string(discards.getSize()));
    return o;
}

vector<Card> Deck::draw(int num) {
    
    vector<Card> drawn;
    int count = num;
    
    // if not enough cards, add what remains and adjust num accordingly
    // and then reuse the discard pile
    if(num > hand.size())
    {
        count -= (int) hand.size();
        drawn.insert(drawn.end(),hand.begin(), hand.end());
        hand.clear();
        shuffle();
    }

    // regular old drawing of the card
    for(int i = 0; i < count; i++)
    {
        drawn.push_back(hand.back());
        hand.pop_back();
    }
    
    // if drew the last of the deck
    if(hand.size() == 0) shuffle();
    
    return drawn;
    
}

void Deck::shuffle()
{
    // adds discard pile back into the remaining deck
    add(discards);
    discards = Hand();

    Hand::shuffle();

    // taking care of the last card
    /*
     * why is this necessary
     */
//    Card back = in_deck.back();
//    unsigned int index = rand()%deck.getSize();
//    deck.back() = deck[index];
//    deck[index] = back;
}

