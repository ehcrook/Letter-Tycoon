//
//  Cheater.cpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/29/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Cheater.h"

#include "Card.h"
#include "Hand.h"

using namespace std;

string Cheater::play(Hand hand, Hand shared) {
    
    string word;
    int i = rand() % 10;
    
    if (i==1) {
        word = hand.getLetters() + shared.getLetters();
        modifyDictionary(word);
    } else {
        word = Computer::play(hand, shared);
    }
    return word;
}

void Cheater::modifyDictionary(string word) {
    
    string DICTONARY = "cheatersdictionary.txt";
    
    ofstream f(DICTONARY);
    f << word;
    f.close();
    
    dictionary.load(DICTONARY);
    cout << "Cheater's Dictionary Size is " << dictionary.getSize() << endl;
    
}

Card Cheater::buyPatent(vector<Card> patents) {
    int i = rand() % 10;
    if (i==0) return Card('a',0);
    else if (i==1) return Card('e',0);
    else if (i==2) return Card('i',0);
    else if (i==3) return Card('o',0);
    else if (i==4) return Card('s',0);
    else if (i==5) return Card('t',0);
    return Computer::buyPatent(patents);
}

