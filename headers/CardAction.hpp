#pragma once
#include <utility> // std::pair
#include <string>
#include "utils.hpp"

class CardAction 
{
    // bool defensive;
    bool offensive;
    bool burn;
    bool bypass;
    std::string chain;
    int healthMod;
    int maxHealthMod;
    int guardMod;
    Animation animation;
    bool heal;


public:
    CardAction(bool offensive, bool burn, bool bypass, bool heal, std::string chain, int health, int maxHealth, int guard, int animation);
    CardAction(CardAction &copy);
    int getHealthMod();
    void setHealthMod(int health);

    int getMaxHealthMod();
    void setMaxHealthMod(int health);

    int getGuardMod();
    void setGuardMod(int guard);

    bool isOffensive();
    bool isDefensive();
    bool isBypass();
    bool isBurn();
    bool isHeal();

    std::string getChain();
    Animation getAnimation();
    // std::pair<bool, bool> getType();
};