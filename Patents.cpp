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

#include "Patent.h"
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
        Patent patent(card);
        patents[patent] = nobody;
    }
    
}

void Patents::output(iostream out) {
    
    map<Patent, Player*>::iterator itr = patents.begin();
    for(; itr != patents.end(); itr++) {
        out << (itr->first).getLetter() << " is owned by " << (itr->second)->getName() << endl;
    }
    
}

Player Patents::getPatentHolder(char c) {
    
    map<Patent, Player*>::iterator itr = patents.begin();
    for(; itr != patents.end(); itr++) {
        if(itr->first.getLetter() == c) return *itr->second;
    }
    
    Player nobody("nobody");
    return nobody;

}

bool Patents::isPatentHolder(Player& p, char c) {
    
    Player holder = getPatentHolder(c);
    return p.getName()==holder.getName();
    
}

vector<Patent> Patents::getAvailable() {
    
    map<Patent, Player*>::iterator itr = patents.begin();
    vector<Patent> available;
    for(; itr != patents.end(); itr++) {
#ifdef _DEBUG
        cout << itr->first.letter << " is owned by " << (itr->second)->getName() << endl;
#endif
        if(itr->second==nobody) available.push_back(itr->first);
    }

    return available;

}

void Patents::buyPatent(Player& player, Patent& patent) {
    
    cout << "Player wants to buy " << patent.getLetter() << endl;
    
    map<Patent, Player*>::iterator itr = patents.begin();
    for(; itr != patents.end(); itr++) {
        if((itr->first==patent)) {
            if (itr->second==nobody) {
                patents[itr->first] = &player;
                player.remove_money(itr->first.getPrice());
                player.add_patents(itr->first);
                return;
            }
        }
    }
    
    throw patent.getLetter();
    
}

vector<Patent> Patents::getPatents(Player& player) {
    
    vector<Patent> playerPatents;
    map<Patent, Player*>::iterator itr = patents.begin();
    for(; itr != patents.end(); itr++) {
        if ((itr->second)->getName()==player.getName()) playerPatents.push_back(itr->first);
    }
    return playerPatents;
}

vector<Patent> Patents::getBuyable(string word, int money) {
    
    vector<Patent> buyable;
    for (int i = 0; i<word.size(); i++) {
        char letter = word[i];
        Player owner = getPatentHolder(letter);
        Patent patent = getPatent(letter);
        if(owner.getName()==nobody->getName() && money >= patent.getPrice()) buyable.push_back(patent);
    }
    
    return buyable;
    
}

Patent Patents::getPatent(char c) {

    map<Patent, Player*>::iterator itr = patents.begin();
    for(; itr != patents.end(); itr++) {
        if(itr->first.getLetter() == c) return itr->first;
    }
    
    throw "No Patent exists for letter";
}

