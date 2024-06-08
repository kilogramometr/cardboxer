#include "../headers/Game.hpp"
#include "../headers/utils.hpp"

Game::Game(std::list<Card *> *library)
{
    this->library = library;
    this->player = new Player;
    this->appendChild(this->player);

    this->enemy = new Enemy;
    this->appendChild(this->enemy);

    this->playerTurn = true;

    this->randomisePlayerDeck(library);

    this->returnButton = new Button({300, 0}, {100, 50}, {5, -5}, 38, sf::Color::Red, "Return", 3);
    this->restartButton = new Button({400, 0}, {100, 50}, {5, -5}, 38, sf::Color::Black, "Restart", 4);
    
    this->playerDeck = new Button({657, 400}, {71.5, 100}, {25, -10}, 50, sf::Color::Green, "0", 3);
    this->playerDiscard = new Button({728.5, 400}, {71.5, 100}, {25, -10}, 50, sf::Color::Blue, "0", 1);
    
    for (int i = 0; i < 3; i++) { this->player->draw(); }
    this->lastMoved = this->player->hand.end();
    this->updateCards();

    this->showCards();

    this->appendChild(this->returnButton);
    this->appendChild(this->restartButton);
    this->appendChild(this->playerDeck);
    this->appendChild(this->playerDiscard);
    
}

void Game::onDraw(sf::RenderTarget& target, sf::Transform& transform) {}

void Game::onUpdate(sf::Vector2f mousePos)
{
    this->playerDeck->setText(std::to_string(this->player->getDeckSize()));
    this->playerDiscard->setText(std::to_string(this->player->getDiscardSize()));
    if (!playerTurn)
    {
        sf::Time t = timer.getElapsedTime();
        if (t.asMilliseconds() > 2500)
            this->turn();
    }
    
    if (this->player->handEmpty())
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
    
    if (hold && hover)
    {
        auto change = mousePos - this->lastPos;
        this->removeChild(&this->hoverCard);
        (*it)->move(change);
        this->moved = true;
        this->lastMoved = it;
    }
    else if (hold && !hover && this->moved)
    {
        auto change = mousePos - this->lastPos;
        this->removeChild(&this->hoverCard);
        (*this->lastMoved)->move(change);
        this->moved = true;
    }
    else if (hover)
    {
        if ( this->lastMoved != this->player->hand.end() && 455 - (*this->lastMoved)->getPosition().y > 100)
        {
            std::cerr<<"Card Playerd: "<<(*this->lastMoved)->getName()<<"\n";
            this->hideCards();
            this->player->discard(*this->lastMoved);
            this->showCards();
        }
        else 
        { this->appendChild(&this->hoverCard); }
        this->updateCards();
        this->hoverCard = **it;
        this->hoverCard.setScale({1, 1});
        this->hoverCard.setPosition({275, 100});
        this->moved = false;
        this->lastMoved = this->player->hand.end();
    }
    else 
    {
        if ( this->lastMoved != this->player->hand.end() && 455 - (*this->lastMoved)->getPosition().y > 100)
        {
            std::cerr<<"Card Playerd: "<<(*this->lastMoved)->getName()<<"\n";
            this->hideCards();
            this->player->discard(*this->lastMoved);
            this->showCards();
        }
        this->removeChild(&this->hoverCard); 
        this->moved = false;
        this->lastMoved = this->player->hand.end();
    }
    
    this->lastPos = mousePos;    
}

void Game::setEnemy(Enemy enemy) { this->enemy = &enemy; }
void Game::killEnemy() { delete this->player; };
void Game::killPlayer() { delete this->enemy; };

void Game::randomisePlayerDeck(std::list<Card *> *library)
{
    this->player->clearDeck();
    for (int i = 0; i < 3; i++)
    {
        int size = library->size();
        int pos = randomUniform(0, size-1);
        auto it = library->begin();
        std::advance(it, pos);
        this->player->addToDeck(*it);
        std::cerr<<(*it)->getTextureRect().width<<"\n";
    }
}

void Game::resolveCard(Card *card, Boxer *source, bool offensive)
{
    this->lastPlayed = *card;
    CardAction *action = (offensive) ?
        card->getOffensiveAction() : card->getDefensiveAction();
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

    target->damage(action->getHealthMod(), action->isBypass());
    target->setMaxHealth(action->getMaxHealthMod() + target->getMaxHealth());
    target->setGuard(action->getGuardMod() + target->getGuard());

    if (source == this->enemy)
        { return; }
    else 
    {
        this->removeChild(card);
        if (action->isBurn()) this->player->burnCard(card);
        else this->player->discard(card);
    }
}

void Game::turn()
{
    std::cerr<<this->playerTurn<<"\n";
    //std::cout<<"Game screen update"<<std::endl;
    if (!playerTurn)
    {
        std::cerr<<"Happy times\n";
        // Card *c = new Card(this->enemy->playCard());
        // bool offensive = (c->getOffensiveAction() != nullptr);
        // this->resolveCard(c, this->enemy, offensive);
    }
    else 
    {
        this->timer.restart();
        std::cerr<<"Restart timer\n";
    }
    this->playerTurn = !this->playerTurn;
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
                this->turn();
                this->playerTurn = false;
                return 100;

            case 3:
                return 3;

            case 4:
                this->hideCards();
                this->player = new Player();
                this->enemy = new Enemy();
                this->randomisePlayerDeck(this->library);
                for (int i = 0; i < 3; i++) { this->player->draw(); }
                this->lastMoved = this->player->hand.end();
                this->updateCards();
                this->showCards();
                return 100;

            default:
                break;
            }
        }
    }
    return 100;
}
