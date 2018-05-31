//
//  Dictionary.cpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/19/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#include <fstream>

#include "Dictionary.h"

using namespace std;

void Dictionary::load(string filename) {
    
    ifstream file(filename.c_str());
    string str;
    while(file >> str)
    dictionary.insert(str);
    
}

bool Dictionary::check(string word) {
    
    if(word.size() > 10) return false;
    if(word.size() < 3) return false;
    
    set<string>::iterator itr = dictionary.find(word);
    
    if(itr != dictionary.end()) return true;
    
//    if(word[word.size()-1] == 's')
//    {
//        string sub = word.substr(0,word.size()-1);
//        itr = dictionary.find(sub);
//        if(itr != dictionary.end()) return true;        
//    }
        
    return false;

}
