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
#include "Patent.h"

using namespace std;

string Cheater::play(Hand hand, Hand shared, vector<Patent> patents) {
    
    string word;
    int i = rand() % 10;
    
    if (i==1) {
        word = hand.getLetters() + shared.getLetters();
        modifyDictionary(word);
    } else {
        word = Computer::play(hand, shared, patents);
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

Patent Cheater::buyPatent(vector<Patent> patents) {
    int i = rand() % 10;
    if (i==0) return Patent(Card('a',0));
    else if (i==1) return Patent(Card('e',0));
    else if (i==2) return Patent(Card('i',0));
    else if (i==3) return Patent(Card('o',0));
    else if (i==4) return Patent(Card('s',0));
    else if (i==5) return Patent(Card('t',0));
    return Computer::buyPatent(patents);
}

