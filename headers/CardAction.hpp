#pragma once
#include <utility> // std::pair

class CardAction 
{
    // bool defensive;
    bool offensive;
    int healthMod;
    int maxHealthMod;
    int guardMod;

public:
    CardAction(bool offensive, int health, int maxHealth, int guard);

    int getHealthMod();
    void setHealthMod(int health);

    int getMaxHealthMod();
    void setMaxHealthMod(int health);

    int getGuardMod();
    void setGuardMod(int guard);

    bool isOffensive();
    bool isDefensive();
    // std::pair<bool, bool> getType();
};