#ifndef _Player_h_
#define _Player_h_

#include "Patent.h"
#include "Hand.h"

//#include <set>
//#include <map>
#include <vector>
#include <string>

using namespace std;

class Player
{
    
public:

    Player(string n) {
        money = 0;
        stocks = 0;
        patent_total = 0;
        name = n;
    }
    
    string getName() const { return name; }
    
//    Hand getHand() { return hand; }
    
    //string output_hand();
    
    string output_patents();
    
    void add_money(int m) { money = money+m; }
    
    void remove_money(int m) { money = max(money-m,0); }
    
    int get_money() const { return money; }
    
    void add_stocks(int n) { stocks = stocks+n; }
    
    int get_stocks() const { return stocks; }
    
    void add_patents(Patent c) {
        patent_total = patent_total+c.getPrice();
        patents.push_back(c.getLetter());
    }
    
    int get_patent_total() const { return patent_total; }
    
    int score() const { return patent_total + stocks + money; }
    
    bool operator<(const Player& a) const
    {
        return name < a.name;
    }
    
    bool operator==(const Player& a) const
    {
        return name == a.name;
    }

private:
//    Hand hand;
    vector<char> patents;
    int money;
    int stocks;
    int patent_total;
    string name;
};

#endif
