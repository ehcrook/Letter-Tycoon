#ifndef _Card_h_
#define _Card_h_

class Card
{

public:
    Card() {
        Card('0',0);
    };
    
    Card(char l, int p)
    {
        letter = l; price = p;
    };
    
    bool operator<(const Card& a) const
    {
        return letter < a.letter;
    };
    
    bool operator==(const Card& a) const
    {
        return letter == a.letter;
    };
    
    static bool isVowel(char letter)
    {
        if(letter == 'a') return true;
        if(letter == 'e') return true;
        if(letter == 'i') return true;
        if(letter == 'o') return true;
        if(letter == 'u') return true;
        return false;
    }
    
    char letter;
    int price;
};
#endif
