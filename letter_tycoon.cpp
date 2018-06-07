
#include <stdio.h>

#include <set>
#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Card.h"
#include "Cards.h"
#include "Player.h"
#include "Patent.h"
#include "Patents.h"
#include "Score.h"
#include "Hand.h"
#include "Strategy.h"
#include "Human.h"
#include "Cheater.h"
#include "Computer.h"
#include "EmilyComputer.h"

#define DEBUG_
using namespace std;

static bool playWord(string word, Player& player, Strategy& strategy, Cards& cards, Dictionary& dictionary, Patents& patents) {

    cout << player.getName() << " played '" << word << "'" << endl;

    string letters = word;
    int pos = (int) word.find(",");
    
    // player is playing two words
    if (pos != string::npos) {
        if (patents.isPatentHolder(player, 'v')) {
            string w1 = word.substr(0,pos);
            string w2 = word.substr(pos+1);
            cout << "Playing two words " << w1 << "," << w2 << endl;
            if (!dictionary.check(w1) || !dictionary.check(w2)) {
                cout << "Your words are not valid. Lose one coin. Your turn is over." << endl;
                player.remove_money(1);
                return false;
            }
            letters = w1 + w2;
        }
        else {
            cout << "You do not have the V Patent. Lose one coin. Your turn is over." << endl;
            player.remove_money(1);
            return false;
        }
    }
    else {
        if (!dictionary.check(word)) {
            cout << "Your word is not valid. Lose one coin. Your turn is over." << endl;
            player.remove_money(1);
            return false;
        }
    }
    
    try
    {
        cards.checkLetters(player, letters);
    }
    catch(const char c)
    {
        cout << "You do not have enough of the letter " << c << " to play this word. Lose one coin. Your turn is over." << endl;
        player.remove_money(1);
        return false;
    }
    
    cards.play(player, letters);

    string discards;
    if (cards.getHand(player).getSize()>0) {
        cout << "Discard any of these letters [" << cards.getHand(player).output() << "]? Enter without spaces. Type P to pass." << endl;
        discards = strategy.discard(cards.getHand(player));
        cout << "Player discards [" << discards << "]" << endl;
        
        if(discards == "P") return true;
        
        try {
            cards.discard(player, discards);
        }
        catch (char c) {
            cout << "You do not have the letter " << c << " in your hand." << endl;
        }
    }
    
    return true;
    
}

static void turn(Player& player, Strategy& strategy, Cards& cards, Dictionary& dictionary, Patents& patents)
{

    cout << player.getName() << "'s turn!" << endl;
    cout << "money: $" << player.get_money() << ", stocks:" << player.get_stocks()
    << ", patents:" << player.get_patent_total() << endl;
    
    Hand shared = cards.getSharedDeck();
    cout << "In the middle: [" << shared.output() << "]" << endl;
    
    cout << "In your hand: [" << cards.getHand(player).output() << "]" << endl;

    bool played = false;
    bool replaced = false;
    string str = "S";
    string discards = "";
    
    while(!played)
    {

        cout << "Enter 'S' to rearrange your hand." << endl;
        cout << "Enter 'D' to swap out cards and end your turn." << endl;
        
        if (patents.isPatentHolder(player, 'b'))
            cout << "You have the B Patent.  Earn double if your word begins and ends in vowels." << endl;

        if (patents.isPatentHolder(player, 'j'))
            cout << "You have the J Patent.  Earn double if vowels are at least half of your word." << endl;

        if (patents.isPatentHolder(player, 'k'))
            cout << "You have the K Patent.  Earn double if your word has only one vowel." << endl;

        if (patents.isPatentHolder(player, 'v'))
            cout << "You have the V Patent.  You may build two words." << endl;
        
        if (patents.isPatentHolder(player, 'x'))
            cout << "You have the X Patent.  You may use one letter card twice." << endl;

        if (patents.isPatentHolder(player, 'z'))
            cout << "You have the Z Patent.  You may add an 'S' to the end of your word." << endl;

        // player with q may discard 1 card at beginning of their turn
        if (!replaced && patents.isPatentHolder(player, 'q'))
            cout << "Enter 'Q' to replace one card from your hand." << endl;

        cout << "Play a Word! " << endl;
        
        str = strategy.play(cards.getHand(player), shared, patents.getPatents(player));
        
        cout << "Player enters [" << str << "]" << endl;
        switch (str[0]) {
            case 'D':
            {
                cout << "Which letters would you like to discard?" << endl;
                discards = strategy.discard(cards.getHand(player));
                cards.discard(player, discards);
                played = true;
                break;
            }
            case 'S':
            {
                Hand hand = cards.getHand(player);
                hand.shuffle();
                cout << "In your hand: [" << hand.output() << "]" << endl;
                break;
            }
            case 'Q':
            {
                if (!replaced) {
                    cout << "Which letter would you like to discard? " << endl;
                    discards = strategy.discard(cards.getHand(player));
                    cards.replace(player, discards[0]);
                    replaced = true;
                }
                break;
            }
            default:
                // if word played is invalid then exit
                if (!playWord(str, player, strategy, cards, dictionary, patents)) return;
                played = true;
        }
        
    }
		
    cards.endTurn(player);
    
    if (str == "D") return;
    
    // update scores
    vector<Score> scores = dictionary.score(str, patents.getPatents(player));
    
    if (scores.size()==2) {
        cout << "You used your V-Patent ability to play two words." << endl;
    }
    vector<Score>::iterator s = scores.begin();
    for (;s!=scores.end();s++) {
        Score score = *s;
        vector<Patent> used = score.getPatentsUsed();
        vector<Patent>::iterator itr = used.begin();
        for (;itr!=used.end();itr++) {
            cout << "You used your " << itr->getLetter() << "-Patent ability and received x2 score!" << endl;
        }
        if (score.usedQ()) {
            cout << "Your word contains Q. You have received x2 score!" << endl;
        }
        cout << "Your word scored $" << score.getCash()*score.getBonus() << " and " << score.getStocks()*score.getBonus() << " stocks." << endl;
        player.add_money(score.getCash()*score.getBonus());
        player.add_stocks(score.getStocks()*score.getBonus());
    }
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
    vector<Patent> buyable = patents.getBuyable(str, player.get_money());
    if(buyable.size() > 0)
    {
        for(unsigned int i = 0; i < buyable.size(); i++)
        cout << buyable[i].getLetter() << "($" << buyable[i].getPrice() << ") ";
        
        cout << endl << "Enter a letter to buy. Enter P to continue without buying." << endl;
        Patent patent = strategy.buyPatent(buyable);
        
        if(patent.getLetter() != 'P')
        {   

            // checking that they entered a valid letter
            bool valid_purchase = false;
            for(unsigned int i = 0; i < buyable.size(); i++)
                if(buyable[i].getLetter()==patent.getLetter()) valid_purchase = true;

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
            else if (str[0] == '?') {
                string name = str.substr(1);
                player = new Player(name + " (average computer)");
                strategy = new EmilyComputer(dictionary);
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
    if (dictionary.getSize()==0) {
        cout << "Could not load Dictionary." << endl;
        return -1;
    }
    cout << "Dictionary Loaded with " << dictionary.getSize() << " Words." << endl;

    Cards cards;
    cards.load("cards.txt");
    if (cards.getDeckSize()==0) {
        cout << "Could not load Deck." << endl;
        return -1;
    }
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
            vector<Patent> available = patents.getAvailable();
            
            vector<Patent>::iterator itr = available.begin();
            for(; itr != available.end(); itr++)
                cout << itr->getLetter() << " ";
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
