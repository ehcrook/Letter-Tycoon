
#include <stdio.h>

#include <set>
#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Card.h"
#include "Cards.h"
#include "Player.h"
#include "Patents.h"
#include "Hand.h"
#include "Strategy.h"
#include "Human.h"
#include "Cheater.h"
#include "Computer.h"

#define DEBUG_
using namespace std;

static void update_score(Player& player, Patents patents, const string word) {
    
    int q = 1;
    if(word.find('q',0) < word.size())
    {
        q = 2;
        cout << "You used the q and received x2 score!" << endl;
    }
    
    // special abilities
    int b = 1;
    Card B('b', 2);
    if(patents.isPatentHolder(player,'b'))
    {
        if(Card::isVowel(word[0]) && Card::isVowel(word[word.size()-1]))
        {
            b = 2;
            cout << "You used your b ability and received x2 score!" << endl;
        }
    }
    
    int j = 1;
    Card J('j', 2);
    if(patents.isPatentHolder(player,'j'))
    {
        int count = 0;
        for(unsigned int i = 0; i < word.size(); i++)
        if(Card::isVowel(word[i])) count++;
        if(count >= word.size()/2)
        {
            j = 2;
            cout << "You used your j ability and received x2 score!" << endl;
        }
    }
    
    int k = 1;
    Card K('k',2);
    if(patents.isPatentHolder(player,'k'))
    {
        int count = 0;
        for(unsigned int i = 0; i < word.size(); i++)
        if(Card::isVowel(word[i])) count++;
        if(count == 1)
        {
            k = 2;
            cout << "You used your k ability and received x2 score!" << endl;
        }
    }

    int multiplier = b*j*k*q;
    if(word.size() < 7) player.add_money(multiplier*((int)word.size()-2));
    if(word.size() >= 6) player.add_stocks(multiplier);
    if(word.size() >= 7) player.add_money(multiplier*6);
    if(word.size() > 7) player.add_stocks(multiplier*((int)word.size()-7));

}

static void turn(Player& player, Strategy& strategy, Cards& cards, Dictionary& dictionary, Patents& patents)
{

    cout << player.getName() << "'s turn!" << endl;
    cout << "money: $" << player.get_money() << ", stocks:" << player.get_stocks()
    << ", patents:" << player.get_patent_total() << endl;
    
    Hand shared = cards.getSharedDeck();
    cout << "In the middle: [" << shared.output() << "]" << endl;
    
    cout << "In your hand: [" << cards.getHand(player).output() << "]" << endl;

    string str = "S";
    string discards = "";
    
    while(str == "S")
    {

        cout << "Play a word! Say 'S' to rearrange your hand. Say 'D' to swap out cards and end your turn." << endl;
        str = strategy.play(cards.getHand(player), shared);
        
        cout << "Player enters [" << str << "]" << endl;
        if(str == "D")
        {
            cout << "Which letters would you like to discard?" << endl;
            discards = strategy.discard(cards.getHand(player));
            cards.discard(player, discards);
        }
        else if(str == "S")
        {
            Hand hand = cards.getHand(player);
            hand.shuffle();
            cout << "In your hand: [" << hand.output() << "]" << endl;
        }
        else
        {
            if (!dictionary.check(str)) {
                cout << "Your word is not valid. Lose one coin. Your turn is over." << endl;
                player.remove_money(1);
                return;
            }
            else {
                cout << player.getName() << " played '" << str << "'" << endl;
            }
            
            try
            {
                cards.checkWord(player, str);
            }
            catch(char c)
            {
                cout << "You do not have enough of the letter " << c << " to play this word. Lose one coin. Your turn is over." << endl;
                player.remove_money(1);
                return;
            }
            
            if (dictionary.check(str)) {
                // play the word
                cards.play(player, str);
            }
            else {
                cout << "Your word is not valid. Lose one coin. Your turn is over." << endl;
                player.remove_money(1);
                return;
            }
            
            if (cards.getHand(player).getSize()>0) {
                cout << "Discard any of these letters [" << cards.getHand(player).output() << "]? Enter without spaces. Type P to pass." << endl;
                discards = strategy.discard(cards.getHand(player));
                cout << "Player discards [" << discards << "]" << endl;

                if(discards == "P") break;
                
                try {
                    cards.discard(player, discards);
                }
                catch (char c) {
                    cout << "You do not have the letter " << c << " in your hand." << endl;
                }
            }
        }
        
    }
		
    cards.endTurn(player);
    
    if (str == "D") return;
        
    update_score(player, patents, str);
    
    cout << "You now have $" << player.get_money() << " and " << player.get_stocks() << " stocks" << endl;
    cout << "In your hand: [" << cards.getHand(player).output() << "]" << endl;

    // pay for use of letters owned by other people
    for(int i=0; i < str.size(); i++)
    {
        char letter = str[i];
        Player owner = patents.getPatentHolder(letter);
        if (!(player==owner||owner.getName()=="nobody")) {
            owner.add_money(1);
            cout << "You used the letter " << letter << " so " << owner.getName() << " earned $1" << endl;
        }
    }

    // see if player wants to buy any patents
    vector<Card> buyable = patents.getBuyable(str, player.get_money());
    if(buyable.size() > 0)
    {
        for(unsigned int i = 0; i < buyable.size(); i++)
        cout << buyable[i].letter << "($" << buyable[i].price << ") ";
        
        cout << endl << "Enter a letter to buy. Enter P to continue without buying." << endl;
        Card patent = strategy.buyPatent(buyable);
        
        if(patent.letter != 'P')
        {   

            // checking that they entered a valid letter
            Card c(patent.letter, 0);
            bool valid_purchase = false;
            for(unsigned int i = 0; i < buyable.size(); i++)
                if(buyable[i] == c) valid_purchase = true;

            if(!valid_purchase)
                cout << "That letter wasn't an option! You forfeit your chance to buy." << endl;
            else
            {

                try {
                    patents.buyPatent(player, patent);
                    cout << "Purchased!" << endl;
                    cout << "You now have $" << player.get_money() << " and " << player.get_stocks() << " stocks" << endl;
                }
                catch (char c) {
                    cout << c << " is not available for purchase." << endl;
                }
            }
        }
    }
    else
        cout << "You cannot purchase any patents at this time." << endl;
}

static vector<Player> setupPlayers(Dictionary &dictionary, map<Player, Strategy *> &strategies) {
    
    set<Player> players;
    
    // set up the players
    int playerCount = 0;
    do {
        string p;
        cout << "Enter number of players to play this game (2 to 6)." << endl;
        cin >> p;
        if (p=="") {
            playerCount = 2;
        }
        else {
            try {
                playerCount = stoi(p);
            } catch (...) {
                cout << "Invalid entry (" << p << "). Please try again" << endl;
            }
        }
    } while (playerCount < 2 || playerCount > 6);
    
    bool ok;
    for (int i=0; i<playerCount; i++) {
        
        string str;
        Player* player;
        Strategy* strategy;

        do {
            
            cout << "Enter player (#" << (i+1) << ")'s name. Use '!' for a computer player. > ";
            cin >> str;
            
            if (str[0] == '!') {
                string name = str.substr(1);
                player = new Player(name + " (computer)");
                strategy = new Computer(dictionary);
            }
            else if (str[0] == '@') {
                string name = str.substr(1);
                player = new Player(name + " (cheater)");
                strategy = new Cheater(dictionary);
            }
            else {
                player = new Player(str);
                strategy = new Human(dictionary);
            }
            
            pair<set<Player>::iterator,bool> itr = players.insert(*player);
            ok = itr.second;
            if (!ok) {
                cout << "Player with the same name exist already. Please provide a different name." << endl;
            }
        }
        while (!ok);
        
        strategies[*player] = strategy;
        
    }
    
    return vector<Player>(players.begin(),players.end());
}

int main()
{
    // set stuff up
	  Dictionary dictionary;
    dictionary.load("dictionary.txt");
    cout << "Dictionary Loaded with " << dictionary.getSize() << " Words." << endl;

    Cards cards;
    cards.load("cards.txt");
    cout << "Deck Loaded with " << cards.getDeckSize() << " Cards." << endl;
    
    Patents patents;
    patents.load("cards.txt");
    cout << "Patents Loaded with " << patents.getAvailable().size() << " Patents." << endl;

    vector<Player> players;
    map<Player, Strategy *> strategies;
    
    players = setupPlayers(dictionary, strategies);
    
    cards.setup(players);
    
    random_shuffle(players.begin(), players.end());

    // play
    bool finished = false;
    
	while(!finished)
	{
		cout << endl << endl << endl;
		cout << "Deck has " << cards.getDeckSize() << " cards remaining" << endl;

        {
            cout << "Patents remaining: ";
            vector<Card> available = patents.getAvailable();
            
            vector<Card>::iterator itr = available.begin();
            for(; itr != available.end(); itr++)
                cout << itr->letter << " ";
            cout << endl;
        }
        
        {
            vector<Player>::iterator itr = players.begin();
            for (; itr!=players.end(); itr++) {
                cout << itr->getName() << " owns: " << itr->output_patents() << endl;
            }
            cout << endl << endl << endl;
        }

        {
            vector<Player>::iterator itr = players.begin();
            for (; itr!=players.end(); itr++) {
                Strategy* strategy = strategies[*itr];
                turn(*itr, *strategy, cards, dictionary, patents);
                cout << endl << endl;
            }
        }
        
        {
            finished = false;
            vector<Player>::iterator itr = players.begin();
            for (; itr!=players.end(); itr++) {
                if (itr->get_patent_total()>=45) finished = true;
            }
        }

 	}

    int topscore = 0;
    Player winner("winner");
    
    cout << endl << endl << endl;
	cout << "Game is over!" << endl;
    
    {
        vector<Player>::iterator itr = players.begin();
        for (; itr!=players.end(); itr++) {
            cout << itr->getName() << endl;
            cout << "\t$" << itr->get_money() << " " << itr->get_stocks()
            << " stocks " << itr->get_patent_total() << " in patents" << endl
            << "\tFor a total score of " << itr->score() << endl;
            
            if (itr->score() > topscore) {
                topscore = itr->score();
                winner = *itr;
            }
        }
        cout << endl << endl << endl;
    }

    // have not handled ties
    cout << winner.getName() << " wins!" << endl;


	return 0;
}
