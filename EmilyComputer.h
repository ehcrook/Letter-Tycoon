/* Emily's computer player */

#ifndef _EMILYCOMPUTER_H_
#define _EMILYCOMPUTER_H_

#include "Card.h"
#include "Hand.h"
#include "Strategy.h"
#include "Dictionary.h"
using namespace std;

class EmilyComputer: public Strategy
{
public:
    EmilyComputer(Dictionary &d) : Strategy(d) {}
    string play(Hand hand, Hand shared);
    string discard(Hand hand);
    Card buyPatent(vector<Card> patents);    
private:
    void tryWords(set<string>& playable, string letters, int length, int attempts);

};


#endif