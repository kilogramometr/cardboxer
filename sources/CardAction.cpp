#include "../headers/CardAction.hpp"

CardAction::CardAction(bool offensive, int health, int maxHealth, int guard)
{
    this->offensive = offensive;
    // this->defensive = defensive;
    this->healthMod = health;
    this->maxHealthMod = maxHealth;
    this->guardMod = guard;
}

// std::pair<bool, bool> getType();
bool CardAction::isOffensive() { return this->offensive; }
bool CardAction::isDefensive() { return !this->offensive; }

int CardAction::getHealthMod() { return this->healthMod; }
int CardAction::getMaxHealthMod() { return this->maxHealthMod; }
int CardAction::getGuardMod() { return this->guardMod; }

void CardAction::setHealthMod(int health) { this->healthMod = health; }
void CardAction::setMaxHealthMod(int health) { this->maxHealthMod = health; }
void CardAction::setGuardMod(int guard) { this->guardMod = guard; }

