/* Emily's computer player */

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>

#include "EmilyComputer.h"
#include "Card.h"
#include "Hand.h"

using namespace std;


string EmilyComputer::play(Hand hand, Hand shared, vector<Patent> patents) {
	set<string> playable;

    string letters = hand.getLetters() + shared.getLetters();
    
    for(int length=10; length != 2; length--) {
    	int n = 1000;
    	if(length == 3) n = 100;
        tryWords(playable, letters, length, n);
    }
    
    if(playable.size() == 0) return "D";

    set<string>::iterator itr = playable.begin();

    int best = rand()%10;
    int num = rand()%playable.size();

    for(int i = 0; i < num; i++)
    {
        if(best && (*itr).size() > 4) return *itr;
    	itr++;
    }

    return *itr;
}

void EmilyComputer::tryWords(set<string>& playable, string letters, int length, int attempts) {
    
    int i = 0;
    string word;
    while (i<attempts) {
        random_shuffle(letters.begin(), letters.end());
        word = letters.substr(0,length);
      	if(dictionary.check(word))
      		playable.insert(word);
        i++;
    }
}

string EmilyComputer::discard(Hand hand) {
    hand.shuffle();
    return hand.getLetters().substr(0,1);
}

char EmilyComputer::replace(Hand hand) {
    hand.shuffle();
    return hand.getLetters()[0];
}

Patent EmilyComputer::buyPatent(vector<Patent> patents) {
    return patents[0];
}
