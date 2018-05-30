//
//  Computer.cpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/28/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

#include "Computer.h"
#include "Card.h"
#include "Hand.h"

using namespace std;

string Computer::play(Hand hand, Hand shared) {

    string letters = hand.getLetters() + shared.getLetters();
    
    for(int length=8; length != 2; length--) {
        string word = tryWords(letters, length, 1000);
        if (word!="D") return word;
    }
    
    return "D";
}

string Computer::tryWords(string letters, int length, int attempts) {
    
    int i = 0;
    bool valid = false;
    string word;
    while (i<attempts && !valid) {
        random_shuffle(letters.begin(), letters.end());
        word = letters.substr(0,length);
        //        cout << i << " " << word << " " << valid << endl;
        valid = dictionary.check(word);
        i++;
    }
    
    if (valid) return word;
    
    return "D";
    
}

string Computer::discard(Hand hand) {
    hand.shuffle();
    return hand.getLetters().substr(0,1);
}

Card Computer::buyPatent(vector<Card> patents) {
    return patents[0];
}

