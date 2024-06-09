#include "../headers/Shield.hpp"

Shield::Shield(bool dir)
{
    this->points = 0;

    this->setSprite(dir);
    this->setText();
}

void Shield::setSprite(bool dir)
{
    if(!this->texture.loadFromFile("./res/textures/shield.png"))
        std::cout<<"Failed to load shield texture"<<std::endl;
    
    this->setTexture(this->texture);
    this->setScale(sf::Vector2f(0.75, 0.75));
    if (dir == 0) this->setPosition(sf::Vector2f(45, 480));
    else this->setPosition(sf::Vector2f(755-this->getGlobalBounds().width, 5));
}

void Shield::setText()
{
    this->font.loadFromFile("./res/fonts/pixellettersfull.ttf");
    
    this->text.setFont(this->font);
    this->text.setCharacterSize(55);
    if(this->points < 10) this->text.setPosition(sf::Vector2f(this->getPosition().x + 52, this->getPosition().y+15));
    else this->text.setPosition(sf::Vector2f(this->getPosition().x+40, this->getPosition().y+15));

    std::stringstream ss;
    ss << this->points;
    this->text.setString(ss.str());
}

void Shield::setPoints(int points)
{
    this->points = points;
    this->text.setString(std::to_string(points));
    if(this->points < 10) this->text.setPosition(sf::Vector2f(this->getPosition().x + 52, this->getPosition().y+15));
    else this->text.setPosition(sf::Vector2f(this->getPosition().x+40, this->getPosition().y+15));

    std::stringstream ss;
    ss << this->points;
    this->text.setString(ss.str());
}

void Shield::onDraw(sf::RenderTarget &target, sf::Transform& transform)
{
    target.draw(*this, transform);
    target.draw(this->text);
}
