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

string Computer::play(Hand hand, Hand shared, vector<Patent> patents) {

    string letters = hand.getLetters() + shared.getLetters();
    
    int bestScore = 0;
    string bestWord = "D";
    for(int length=10; length != 2; length--) {
        string word = tryWords(letters, length, 10000, patents);
        if (word!="D") {
            Score score = dictionary.score(word, patents)[0];
            if (score.getValue() > bestScore) {
                bestScore = score.getValue();
                bestWord = word;
                cout << bestWord << "," << bestScore << endl;
            }
        }

    }
    
    return bestWord;
}

string Computer::tryWords(string letters, int length, int attempts, vector<Patent> patents) {
    
    int i = 0;
    bool valid = false;
    int bestScore = 0;
    string bestWord = "";
    while (i<attempts) {
        random_shuffle(letters.begin(), letters.end());
        string word = letters.substr(0,length);
        if (dictionary.check(word)) {
            Score score = dictionary.score(word, patents)[0];
            if (score.getValue() > bestScore) {
                bestScore = score.getValue();
                bestWord = word;
                valid = true;
                cout << bestWord << "," << bestScore << endl;
            }
        }
        i++;
    }
    
    if (valid) return bestWord;
    
    return "D";
    
}

string Computer::discard(Hand hand) {
    hand.shuffle();
    return hand.getLetters().substr(0,1);
}

char Computer::replace(Hand hand) {
    hand.shuffle();
    return hand.getLetters()[0];
}

Patent Computer::buyPatent(vector<Patent> patents) {
    return patents[0];
}

