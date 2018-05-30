//
//  Patents.cpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/20/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <string>

#include "Card.h"
#include "Player.h"
#include "Patents.h"

using namespace std;

void Patents::load(string filename) {

    ifstream file(filename);
    char letter = '0';
    int price = 0;
    int freq = 0;
    while(file >> letter >> price >> freq)
    {
        Card card(letter, price);
        patents[card] = nobody;
    }
    
}

void Patents::output(iostream out) {
    
    map<Card, Player*>::iterator itr = patents.begin();
    for(; itr != patents.end(); itr++) {
        out << itr->first.letter << " is owned by " << (itr->second)->getName() << endl;
    }
    
}

Player Patents::getPatentHolder(char c) {
    
    map<Card, Player*>::iterator itr = patents.begin();
    for(; itr != patents.end(); itr++) {
        if(itr->first.letter == c) return *itr->second;
    }
    
    Player nobody("nobody");
    return nobody;

}

bool Patents::isPatentHolder(Player p, char c) {
    
    Player holder = getPatentHolder(c);
    return p.getName()==holder.getName();
    
}

vector<Card> Patents::getAvailable() {
    
    map<Card, Player*>::iterator itr = patents.begin();
    vector<Card> available;
    for(; itr != patents.end(); itr++) {
#ifdef _DEBUG
        cout << itr->first.letter << " is owned by " << (itr->second)->getName() << endl;
#endif
        if(itr->second==nobody) available.push_back(itr->first);
    }

    return available;

}

void Patents::buyPatent(Player& player, Card patent) {
    
    cout << "Player wants to buy " << patent.letter << endl;
    
    map<Card, Player*>::iterator itr = patents.begin();
    for(; itr != patents.end(); itr++) {
        if(itr->first.letter == patent.letter) {
            if (itr->second==nobody) {
                patents[itr->first] = &player;
                player.remove_money(itr->first.price);
                player.add_patents(itr->first);
                return;
            }
        }
    }
    
    throw patent.letter;
    
}

vector<Card> Patents::getBuyable(string word, int money) {
    
    vector<Card> buyable;
    for (int i = 0; i<word.size(); i++) {
        char letter = word[i];
        Player owner = getPatentHolder(letter);
        Card card = getCard(letter);
        if(owner.getName()==nobody->getName() && money >= card.price) buyable.push_back(card);
    }
    
    return buyable;
    
}

Card Patents::getCard(char c) {

    map<Card, Player*>::iterator itr = patents.begin();
    for(; itr != patents.end(); itr++) {
        if(itr->first.letter == c) return itr->first;
    }
    
    throw "No Card exists for letter";
}

