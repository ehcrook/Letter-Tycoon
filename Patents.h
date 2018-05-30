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
#include "Card.h"

class Patents {
public:
    Patents() {
        patents = map<Card, Player*>();
        nobody = new Player("nobody");
    };
    void load(string filename);
    vector<Card> getAvailable();
    Card getCard(char c);
    void buyPatent(Player& player, Card patent);
    Player getPatentHolder(char c);
    bool isPatentHolder(Player player, char c);
    vector<Card> getBuyable(string word, int money);
    void output(iostream out);
private:
    map<Card, Player*> patents;
    Player *nobody;
};

#endif /* Patents_h */
