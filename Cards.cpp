//
//  Cards.cpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/26/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#include "Cards.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"

#include <fstream>
#include <map>
#include <vector>

//#ifdef DEBUG_
#include <iostream>
//#endif

void Cards::load(string filename) {
    ifstream file;
    char letter;
    int price;
    int freq;
    
    file.open(filename);
    
    while(file.good()) {
        file >> letter >> price >> freq;
        Card card(letter, price);
        for(int i = 0; i < freq; i++)
            deck.add(card);
    }
    
    deck.shuffle();
    
}

void Cards::setup(vector<Player> players) {
    
    shared.add(deck.draw(3));
    
    vector<Player>::iterator itr = players.begin();
    
    for(; itr!=players.end(); itr++) {
        Hand *hand = new Hand(deck.draw(7));
        hands.insert(pair<Player, Hand*>(*itr,hand));
        cout << "Starting hand for " << itr->getName() << " is [" << hand->output() << "]" << endl;
    }
    
}

void Cards::endTurn(Player player){
    
    {
        int count = shared.getSize();
        shared.add(deck.draw(3-count));
    }
    
    {
        Hand* hand = hands[player];
        int count = hand->getSize();
        hand->add(deck.draw(7-count));
    }
    
    cout << deck.output() << endl;
    
}

void Cards::checkWord(Player player, string word)
{
    Hand hand = *hands[player];

    // make sure all letters are in the deck
    map<char, int> all;
    
    {
        string letters = hand.getLetters();
        for(unsigned int i = 0; i < letters.size(); i++)
            all[letters[i]]++;
    }
    
    {
        string letters = shared.getLetters();
        for(unsigned int i = 0; i < letters.size(); i++)
            all[letters[i]]++;
    }

    map<char, int> used;
    for(unsigned int i = 0; i < word.size(); i++)
        used[word[i]]++;
    
    map<char, int>::iterator itr;
    map<char, int>::iterator itr2 = used.begin();
    for(; itr2 != used.end(); itr2++)
    {
        itr = all.find(itr2->first);
        if(itr == all.end() || itr->second < itr2->second)
            throw itr->first;
    }
    
}

//string Cards::outputSharedDeck() {
//    return shared.output();
//}

void Cards::play(Player player, string word)
{
    Hand *hand = hands[player];

    // remove all letters
    for(unsigned int i = 0; i < word.size(); i++)
    {
        try {
            Card card = hand->getCard(word[i]);
            //cout << "Removing " << word[i] << " from players hand." << endl;
            hand->remove(card);
            deck.discard(card);
        }
        catch (char l) {
            Card card = shared.getCard(word[i]);
            //cout << "Removing " << word[i] << " from shared deck." << endl;
            shared.remove(card);
            deck.discard(card);
        }
    }
    
    //cout << "Shared Deck is " << shared.output() << endl;
}

void Cards::discard(Player player, string word)
{
    
    Hand *hand = hands[player];
    
    for(unsigned int i = 0; i < word.size(); i++)
    {
        Card card = hand->getCard(word[i]);
        hand->remove(card);
        deck.discard(card);
    }

}

void Cards::replace(Player player, char letter)
{
    Hand *hand = hands[player];
    Card card = hand->getCard(letter);
    hand->remove(card);
    deck.discard(card);
    
}

Hand Cards::getHand(Player player) {
    
    map<Player, Hand*>::iterator itr = hands.begin();
    for(; itr != hands.end(); itr++) {

        if(itr->first.getName() == player.getName()) {
//            cout << itr->second->getLetters() << endl;
            Hand hand = *itr->second;
            return hand;
        }
        
    }
    throw player.getName() + " not found";
}






