#pragma once
#include <iostream>
#include <string>
#include "hp.hpp"
#include "statsblock.hpp"
using namespace std;

class Monster : public hp, public StatBlock {
private:
    string name;
    string description;
    int xpReward;
    int goldReward; 
    
public:
 


};

  

   