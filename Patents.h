//
//  Patents.h
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/20/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#ifndef Patents_h
#define Patents_h

#include <map>

#include "Player.h"
#include "Patent.h"

class Patents {
public:
    Patents() {
        patents = map<Patent, Player*>();
        nobody = new Player("nobody");
    };
    void load(string filename);
    vector<Patent> getAvailable();
    Patent getPatent(char c);
    void buyPatent(Player& player, Patent& patent);
    Player getPatentHolder(char c);
    bool isPatentHolder(Player& player, char c);
    vector<Patent> getPatents(Player& player);
    vector<Patent> getBuyable(string word, int money);
    void output(iostream out);
private:
    map<Patent, Player*> patents;
    Player *nobody;
};

#endif /* Patents_h */
