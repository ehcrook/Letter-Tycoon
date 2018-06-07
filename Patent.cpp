//
//  Patent.cpp
//  Letter-Tycoon
//
//  Created by Stuart Crook on 6/2/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#include "Patent.h"

#include <string>

using namespace std;

bool Patent::checkSpecialUsage(string word) {

    if (!special) return false;
    
    // special abilities
    switch(letter) {
        case 'b':
            return isVowel(word[0]) && isVowel(word[word.size()-1]);
        case 'j':
        {
            int count = 0;
            for(unsigned int i = 0; i < word.size(); i++)
                if(Card::isVowel(word[i])) count++;
            return count >= word.size()/2;
        }
        case 'k':
        {
            int count = 0;
            for(unsigned int i = 0; i < word.size(); i++)
                if(Card::isVowel(word[i])) count++;
            return (count == 1);
        }
    }
    
    return false;
    
}
