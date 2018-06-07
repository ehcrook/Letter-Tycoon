#ifndef _Card_h_
#define _Card_h_

class Card
{

public:
    Card() {
        Card('0',0);
    }
    
    Card(char l, int p)
    {
        letter = l; price = p;
        special = isSpecial(l);
    }
    
    bool operator<(const Card& a) const
    {
        return letter < a.letter;
    }
    
    bool operator==(const Card& a) const
    {
        return letter == a.letter;
    }
    
    static bool isVowel(char letter)
    {
        switch (letter) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return true;
            default:
                return false;
        }
    }
    
    static bool isSpecial(char letter)
    {
        switch (letter) {
            case 'b':
            case 'j':
            case 'k':
            case 'q':
            case 'v':
            case 'x':
            case 'z':
                return true;
            default:
                return false;
        }
    }

    char getLetter() const { return letter; }
    int getPrice() const { return price; }
    bool isSpecial() const { return special; }
    
protected:
    char letter;
    int price;
    bool special;
    
};
#endif
