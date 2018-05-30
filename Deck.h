#ifndef _Deck_h_
#define _Deck_h_

#include <vector>
//#include <map>

#include "Card.h"
#include "Hand.h"

using namespace std;

// a deck is a Hand that supports draws and a discard pile
class Deck : public Hand
{
public:

    Deck() {}
    
    string output();
    
    int getDeckSize() { return (int)hand.size(); }
    vector<Card> draw(int num);
    
    void discard(Card card) {
        //remove(card);
        discards.add(card);
    }

    void shuffle();

private:
    Hand discards;

};

#endif
