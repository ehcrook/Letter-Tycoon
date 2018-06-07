//
//  Player.cpp
//  Letter Tycoon C++
//
//  Created by Stuart Crook on 5/18/18.
//  Copyright © 2018 Stuart Crook. All rights reserved.
//

#include "Player.h"

using namespace std;

string Player::output_patents()
{
    string o;
    
    if(patents.size() == 0)
        return "none";

    for(unsigned int i = 0; i < patents.size(); i++) {
        o.push_back(patents[i]);
        o.push_back(' ');
    }
    o.append("($" + to_string(patent_total) + ")");
    
    return o;
}

