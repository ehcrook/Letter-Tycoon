//
//  Cards.hpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/26/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Cards_h
#define Cards_h

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Hand.h"

#include <string>
#include <set>
#include <map>

using namespace std;

class Cards
{
public:
    Cards() {}
    void load(string filename);
    void setup(vector<Player> players);
    int getDeckSize() {
        return deck.getSize();
    }
    Hand getSharedDeck() { return shared; }
    void checkWord(Player player, string word);
    void discard(Player player, string letters);
    void play(Player player, string word);
    void endTurn(Player player);
    Hand getHand(Player player);
//    Hand operator[] (const Player& player) const { return hands[player]; }
private:
    Deck deck;
    Hand shared;
    map<Player, Hand*> hands;

};

#endif /* Cards_h */
