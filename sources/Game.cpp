#include "../headers/Game.hpp"
#include "../headers/utils.hpp"

Game::Game(std::list<Card *> *library, std::list<Enemy *> *enemies)
{

    this->library = library;
    this->enemies = enemies;
    this->player = new Player;
    this->appendChild(this->player);

    this->randomEnemy();
    this->appendChild(this->enemy);

    this->playerTurn = true;
    this->moved = false;
    this->choose = false;

    this->randomisePlayerDeck(library);

    this->returnButton = new Button({300, 0}, {100, 50}, {5, -4}, 38, sf::Color::Red, "Return", 3);
    this->restartButton = new Button({400, 0}, {100, 50}, {5, -4}, 38, sf::Color::Black, "Restart", 4);
    
    this->playerDeck = new Button({657, 400}, {71.5, 100}, {25, -10}, 50, sf::Color::Green, "0", 0);
    this->playerDiscard = new Button({728.5, 400}, {71.5, 100}, {25, -10}, 50, sf::Color::Blue, "0", 0);
    this->drawButton = new Button({657, 500}, {143, 100}, {25, -10}, 50, sf::Color::Green, "Draw", 2);

    this->offensiveButton = new Button({212.5, 262.5}, {125, 75}, {5, 6}, 38, sf::Color::Red, "Offensive", 5);
    this->defensiveButton = new Button({462.5, 262.5}, {125, 75}, {5, 6}, 38, sf::Color::Blue, "Defensive", 6);
    
    for (int i = 0; i < 3; i++) { this->player->draw(); }
    this->lastMoved = this->player->hand.end();
    this->updateCards();

    this->showCards();

    this->appendChild(this->returnButton);
    this->appendChild(this->restartButton);
    this->appendChild(this->playerDeck);
    this->appendChild(this->playerDiscard);
    this->appendChild(this->drawButton);
    
}

void Game::onDraw(sf::RenderTarget& target, sf::Transform& transform) {}

void Game::onUpdate(sf::Vector2f mousePos)
{
    if (!this->enemyDead && this->enemy->getHealth() <= 0)
        { this->killEnemy(); this->enemyDead = true; }
    if (!this->playerDead && this->player->getHealth() <= 0)
        { this->killPlayer(); this->playerDead = true; }

    if (this->chain)
    {
        sf::Time t = timer.getElapsedTime();
        if (t.asMilliseconds() > 750)
        {
            this->chain = false;
            this->updateLastPlayed(*this->nextPlay);
            this->hideCards();
            this->player->discard(this->nextPlay);
            this->showCards();
            this->resolveCard(this->nextPlay, this->player, true);
            this->nextPlay = nullptr;
            this->choose = false;
            this->playerTurn = false;
            this->timer.restart();
        }
    }

    // update deck text
    this->playerDeck->setText(std::to_string(this->player->getDeckSize()));
    this->playerDiscard->setText(std::to_string(this->player->getDiscardSize()));
    //resolve enemy turn
    if (!playerTurn)
    {
        sf::Time t = timer.getElapsedTime();
        if (t.asMilliseconds() > 1500)
            this->turn();
    }
    //draw cards if hand empty
    if (this->player->handEmpty() && this->playerTurn)
    {
        this->hideCards();
        for (int i = 0; i < 3; i++)
        {
            if (this->player->getDeckSize() == 0) this->player->reshuffle();
            this->player->draw();
        }
        this->updateCards();
        this->showCards();
    }


    //resolve hover and drag&drop
    bool hover = false;
    bool hold = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    auto it = this->player->hand.begin();
    for (; it != this->player->hand.end(); ++it)
    {
        if ((*it)->getGlobalBounds().contains(mousePos))
        {
            hover = true;
            break;
        }

    }
    if (hold && hover && !this->choose && this->playerTurn)
    {
        auto change = mousePos - this->lastPos;
        this->removeChild(&this->hoverCard);
        (*it)->move(change);
        this->moved = true;
        this->lastMoved = it;
    }
    else if (hold && !hover && this->moved && !this->choose && this->playerTurn)
    {
        auto change = mousePos - this->lastPos;
        this->removeChild(&this->hoverCard);
        (*this->lastMoved)->move(change);
        this->moved = true;
    }
    else if (hover)
    {
        if ( this->lastMoved != this->player->hand.end() && 455 - (*this->lastMoved)->getPosition().y > 100 && this->playerTurn)
        {
            std::cerr<<"Card Playerd: "<<(*this->lastMoved)->getName()<<"\n";
            this->updateLastPlayed(**this->lastMoved);
            this->showButtons();
            this->hideCards();
            this->player->discard(*this->lastMoved);
            this->showCards();
            this->choose = true;
        }
        else 
        { this->appendChild(&this->hoverCard); }
        this->updateCards();
        this->hoverCard = **it;
        this->updateHoverCard();
        this->moved = false;
        this->lastMoved = this->player->hand.end();
    }
    else if (this->lastPlayed.getGlobalBounds().contains(mousePos))
    {
        this->updateCards();
        this->hoverCard = this->lastPlayed;
        this->updateHoverCard();
        this->moved = false;
        this->lastMoved = this->player->hand.end();
        this->appendChild(&this->hoverCard);
    }
    else 
    {
        if ( this->lastMoved != this->player->hand.end() && 455 - (*this->lastMoved)->getPosition().y > 100 && this->playerTurn)
        {
            std::cerr<<"Card Playerd: "<<(*this->lastMoved)->getName()<<"\n";
            this->updateLastPlayed(**this->lastMoved);
            this->showButtons();
            this->hideCards();
            this->player->discard(*this->lastMoved);
            this->showCards();
            this->choose = true;
        }
        this->removeChild(&this->hoverCard); 
        this->moved = false;
        this->lastMoved = this->player->hand.end();
    }
    
    this->lastPos = mousePos;    
}

void Game::setEnemy(Enemy enemy) { this->enemy = &enemy; }

void Game::killEnemy() 
{ 
    this->enemy->dead(&animationEnd);
};

void Game::killPlayer() 
{
    this->player->dead(&animationEnd); 
};

void Game::randomisePlayerDeck(std::list<Card *> *library)
{
    this->player->clearDeck();
    std::list<Card *> checklist;
    for (int i = 0; i < 3; i++)
    {
        int size = library->size();
        int pos = randomUniform(0, size-1);
        auto it = library->begin();
        std::advance(it, pos);
        if ((*it)->isObtainable())
        {
            bool add = true;
            for (auto jt = checklist.begin(); jt != checklist.end(); ++jt)
            {   
                if ((*jt)->getName() == (*it)->getName()) 
                { add = false; break; }
            }  
            if (add)
            {
                this->player->addToDeck(*it);
                checklist.push_back(*it);
            }
            else --i;
        }
        else --i;
    }
}

void Game::resolveCard(Card *card, Boxer *source, bool offensive)
{
    std::cerr<<offensive<<"\n";
    CardAction *action = (offensive) ?
        card->getOffensiveAction() : card->getDefensiveAction();
    
    std::cerr<<"Target"<<"\n";
    Boxer *target;
    if (source == this->player) 
    {
        if (offensive) target = this->enemy;
        else target = this->player;
    }
    else 
    {
        if (offensive) target = this->player;
        else target = this->enemy;
    }
    std::cerr<<"resolve"<<"\n";

    std::cerr<<target->getHealth()<<" "<<action->getHealthMod()<<" health\n";
    std::cerr<<target->getMaxHealth()<<" "<<action->getMaxHealthMod()<<" maxhealth\n";
    std::cerr<<target->getGuard()<<" "<<action->getGuardMod()<<" guard\n";

    target->damage(action->getHealthMod(), action->isBypass());
    target->setMaxHealth(action->getMaxHealthMod() + target->getMaxHealth());
    target->setGuard(action->getGuardMod() + target->getGuard());

    std::cerr<<target->getHealth()<<" health\n";
    std::cerr<<target->getMaxHealth()<<" maxhealth\n";
    std::cerr<<target->getGuard()<<" guard\n";
    


    std::cerr<<action->getAnimation()<<"\n";
    switch(action->getAnimation())
    {
    case Animation::attack1:
        source->attack1();
        break;
    case Animation::attack2:
        source->attack2();
        break;
    case Animation::attack3:
        source->attack3();
        break;
    case Animation::block:
        source->block();
        break;
    default:
        break;
    }

    if (action->getChain() != "")
    {
        auto it = std::find_if(this->player->hand.begin(), this->player->hand.end(), [action](Card *card){ return *card == action->getChain(); });
        if (it != this->player->hand.end()) 
        {
            this->nextPlay = *it;
            this->chain = true;
        }
    }
    
    if (source == this->enemy)
        { return; }
    else if (action->isBurn()) this->player->burnCard(card);

}

void Game::turn()
{
    std::cerr<<this->playerTurn<<"\n";
    //std::cout<<"Game screen update"<<std::endl;
    if (!playerTurn)
    {
        std::cerr<<"Happy times\n";

        Card *c = this->enemy->playCard();
        std::cerr<<"Card: "<<c->getName();
        bool offensive = (c->getOffensiveAction() != nullptr);
        this->updateLastPlayed(*c);
        std::cerr<<"updated\n";
        this->resolveCard(c, this->enemy, offensive);
    }
    this->playerTurn = !this->playerTurn;
}

int Game::onButtonClick(sf::Vector2f mousePosition)
{
    for (auto i = this->children.begin(); i != this->children.end(); ++i)
    {
        int code = (*i)->buttonClick(mousePosition);
        if (code != 0)
        {
            switch (code)
            {
            case 1:
                return 100;

            case 2:
                if (this->player->getDeckSize() == 0 && this->player->getDiscardSize() == 0)
                    return 100;
                this->hideCards();
                if (this->player->getDeckSize() == 0)
                    this->player->reshuffle();
                if (this->player->getDeckSize() > 0)
                    this->player->draw();
                this->updateCards();
                this->showCards();
                this->playerTurn = false;
                this->timer.restart();
                return 100;

            case 3:
                return 3;

            case 4:
                this->moved = false;
                this->choose = false;
                this->playerTurn = true;
                this->hideCards();
                this->hideButtons();
                this->removeChild(&this->lastPlayed);
                this->removeChild(this->player);
                this->removeChild(this->enemy);
                this->player = new Player();
                this->randomEnemy();
                this->randomisePlayerDeck(this->library);
                for (int i = 0; i < 3; i++) { this->player->draw(); }
                this->lastMoved = this->player->hand.end();
                this->updateCards();
                this->showCards();
                this->appendChild(this->player);
                this->appendChild(this->enemy);
                return 100;
            
            case 5:
                this->resolveCard(&this->lastPlayed, this->player, true);
                this->hideButtons();
                this->choose = false;
                this->playerTurn = false;
                this->timer.restart();
                return 100;

            case 6:
                this->resolveCard(&this->lastPlayed, this->player, false);
                this->hideButtons();
                this->choose = false;
                this->playerTurn = false;
                this->timer.restart();
                return 100;

            default:
                break;
            }
        }
    }
    return 100;
}

void Game::updateLastPlayed(Card card)
{
    this->removeChild(&this->lastPlayed);
    this->lastPlayed = card;
    this->lastPlayed.setScale({0.4, 0.4});
    this->lastPlayed.setPosition({0, 0});
    this->appendChild(&this->lastPlayed);
}

void Game::showButtons()
{
    if (this->lastPlayed.getOffensiveAction() != nullptr)
        this->appendChild(this->offensiveButton);
    if (this->lastPlayed.getDefensiveAction() != nullptr)
        this->appendChild(this->defensiveButton);
}

void Game::hideButtons()
{
    this->removeChild(this->offensiveButton);
    this->removeChild(this->defensiveButton);
}

void Game::updateHoverCard()
{
    this->hoverCard.setScale({1, 1});
    this->hoverCard.setPosition({275, 100});
}

void Game::hideCards()
{
    for (auto it = this->player->hand.begin(); it != this->player->hand.end(); ++it)
        this->removeChild(*it);
}

void Game::showCards()
{
    for (auto it = this->player->hand.begin(); it != this->player->hand.end(); ++it)
        this->appendChild(*it);
}

void Game::updateCards()
{
    float x = (800-3*(250/2))/2;
    float w = (250/2);
    for (auto it = this->player->hand.begin(); it != this->player->hand.end(); ++it)
    {
        (*it)->setScale({0.4, 0.4});
        (*it)->setPosition({x, 455});
        x += w;
    }
}

void Game::randomEnemy()
{
    int size = this->enemies->size();
    auto it = this->enemies->begin();
    int random = randomUniform(0, size-1);
    std::advance(it, random);
    this->enemy = new Enemy(*it);
}