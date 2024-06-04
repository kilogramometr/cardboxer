#pragma once
#include <utility> // std::pair
#include <string>

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

public:
    CardAction(bool offensive, bool burn, bool bypass, std::string chain, int health, int maxHealth, int guard);

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

    std::string getChain();
    // std::pair<bool, bool> getType();
};