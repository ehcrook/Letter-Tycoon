/* Emily's computer player */

#ifndef _EMILYCOMPUTER_H_
#define _EMILYCOMPUTER_H_

#include "Patent.h"
#include "Hand.h"
#include "Strategy.h"
#include "Dictionary.h"
using namespace std;

class EmilyComputer: public Strategy
{
public:
    EmilyComputer(Dictionary &d) : Strategy(d) {}
    string play(Hand hand, Hand shared, vector<Patent> patents);
    string discard(Hand hand);
    char replace(Hand hand);
    Patent buyPatent(vector<Patent> patents);
private:
    void tryWords(set<string>& playable, string letters, int length, int attempts);

};


#endif
