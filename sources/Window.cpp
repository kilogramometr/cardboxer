#include "../headers/Window.hpp"
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include "../headers/utils.hpp"

Window::Window(sf::Vector2f resolution, std::string title)
    : sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), title)
{
    // set resolution
    this->resolution = resolution;

    if(!this->backgroundTexture.loadFromFile("../res/textures/background.png"))
        std::cout<<"Unable to load background texture"<<std::endl;
    this->backGround.setTexture(this->backgroundTexture);
    
    if (!this->loadLibrary()) throw 0;
    if (!this->loadEnemies()) throw 1;
    
    // create scene and view
    this->menu = new Menu();
    this->game = new Game(&library, &enemies);
    this->cardLibrary = new CardLibrary(&this->library);
    this->setCurrentScene(this->menu);

    //Set max framerate
    this->setVerticalSyncEnabled(false);
    this->setFramerateLimit(60);
    this->setTitle("Cardboxer");

    //Mouse hold
    this->mouseHold = false;
}

void Window::loop()
{
    sf::Event event;
    while(this->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                this->close();
                break;
            case sf::Event::MouseButtonReleased:
                this->checkClicks();
                break;
            default:
                break;
        }
    }

    this->updateMousePosition();
    this->Scene->update(this->mousePosition);
    this->drawScene();
    this->display();
}

void Window::drawScene()
{
    this->draw(this->backGround);
    sf::Transform transform;
    this->Scene->draw(*this, transform);
}

void Window::setCurrentScene(Node *node)
{
    this->Scene = node;
}

void Window::updateMousePosition()
{
    sf::Vector2i mousePositionWindow = sf::Mouse::getPosition(*this);
    this->mousePosition = this->mapPixelToCoords(mousePositionWindow);
}

void Window::checkClicks()
{
    this->updateMousePosition();
    switch(this->Scene->buttonClick(this->mousePosition))
    {
        case 1: // switch to game scene
            this->setCurrentScene(this->game);
            break;
        case 2: // shutdown
            this->close();
            break;
        case 3: // switch to menu scene
            this->setCurrentScene(this->menu);
            break;
        case 4: // switch to card library scene
            this->setCurrentScene(this->cardLibrary);
            break;
        case 100: // click handled by internal scene function
        default:
            break;
    }
}

void Window::checkMouseHold()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->mouseHold = true;
    else
        this->mouseHold = false;
}


/*
 * INIT
 */

bool Window::loadLibrary()
/* load global library of cards for use during game */
{
    std::ifstream file("./cards/load_list.json", std::ifstream::binary);
    Json::Value list;
    int failures = 0;
    if(file.is_open())
    {   
        try { file >> list; }
        catch(Json::RuntimeError e) 
        {
            e.what();
            log(e.what());
            return false; 
        }
        file.close();
    }
    else 
    {
        std::cerr<<"\nLibraryLoader: Panic! Unable to open load list for cards! Can't procede!\n";
        log("\nLibraryLoader: Panic! Unable to open load list for cards! Can't procede!\n");
        return false;
    }
    
    std::map<std::string, bool> loadedCards;
    
    for (auto f : list)
    {
        std::string path = "./cards/"+f.asString();
        file.open(path, std::ifstream::binary);
        Json::Value card;
        if(file.is_open())
        {
            file >> card;
            file.close();

            if (card["name"].isNull())
            {
                std::cerr<<"LibraryLoader: error #1; file "<<f.asString()<<" - attribute \"name\" is NULL (expected string).\n";
                log("LibraryLoader: error #1; file "+f.asString()+" - attribute \"name\" is NULL (expected string).\n");
                continue;
            }
            else
            {
                auto it = loadedCards.find(card["name"].asString());
                if (it == loadedCards.end()) 
                    loadedCards[card["name"].asString()] = true; 
                else 
                {
                    std::cerr<<"LibraryLoader: error #2; Card \""<<card["name"].asString()<<"\" - card of this name has already been loaded. Skipping...\n";
                    log("LibraryLoader: error #2; Card \""+card["name"].asString()+"\" - card of this name has already been loaded. Skipping...\n");
                    continue;
                }
            }

            try { this->library.emplace_back(new Card(card)); }
            catch (int e)
            {
                // std::cerr<<"\nError\n";
                failures++;
                switch(e)
                {
                case 11:
                    std::cerr<<"LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"health\" in \"defensiveAction\" is NULL (expected int).\n";
                    log("LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"health\" in \"defensiveAction\" is NULL (expected int).\n");
                    break;
                case 12:
                    std::cerr<<"LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"maxHealth\" in \"defensiveAction\" is NULL (expected int).\n";
                    log("LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"maxHealth\" in \"defensiveAction\" is NULL (expected int).\n");
                    break;
                case 13:
                    std::cerr<<"LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"guard\" in \"defensiveAction\" is NULL (expected int).\n";
                    log("LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"guard\" in \"defensiveAction\" is NULL (expected int).\n");
                    break;
                case 21:
                    std::cerr<<"LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"health\" in \"offensiveAction\" is NULL (expected int).\n";
                    log("LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"health\" in \"offensiveAction\" is NULL (expected int).\n");
                    break;
                case 22:
                    std::cerr<<"LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"maxHealth\" in \"offensiveAction\" is NULL (expected int).\n";
                    log("LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"maxHealth\" in \"offensiveAction\" is NULL (expected int).\n");
                    break;
                case 23:
                    std::cerr<<"LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"guard\" in \"offensiveAction\" is NULL (expected int).\n";
                    log("LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attribute \"guard\" in \"offensiveAction\" is NULL (expected int).\n");
                    break;
                case 30:
                    std::cerr<<"LibarryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attrivute \"texture\" is NULL (expected file and rectangle)\n";
                    log("LibarryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - attrivute \"texture\" is NULL (expected file and rectangle)\n");
                    break;
                case 31:
                    std::cerr<<"LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - can't open texture file \""+ card["texture"]["file"].asString() +"\" .\n";
                    log("LibraryLoader: error #"+std::to_string(e)+"; Card \""+ card["name"].asString() +"\" - can't open texture file \""+ card["texture"]["file"].asString() +"\" .\n");
                    break;
                default:
                    std::cerr<<"LibraryLoader: unidentified error #"<<e<<"\n";
                    log("LibraryLoader: unidentified error #"+std::to_string(e)+"\n");
                    break;
                }
            }
        }
        else 
        { 
            std::cerr<<"LibraryLoader: Can't open card file: \""<<f.asString()<<"\". Skipping...\n"; 
            log ("LibraryLoader: Can't open card file: \""+f.asString()+"\". Skipping...\n");
            failures++; 
            }
    }
    std::cerr<<"LibraryLoader: Loaded "<<this->library.size()<<" cards, failed to load "<<failures<<".\n";
    log("LibraryLoader: Loaded "+std::to_string(this->library.size()) + " cards, failed to load "+std::to_string(failures)+".\n");
    // TODO: Load cards from jsons as json objects into this->library (list of cards)
    return true;
}

bool Window::loadEnemies()
{
    std::ifstream file("./enemies/load_list.json", std::ifstream::binary);
    Json::Value list;
    int failures = 0;
    if(file.is_open())
    {   
        try { file >> list; }
        catch(Json::RuntimeError e) 
        {
            e.what();
            return false; 
        }
        file.close();
    }
    else 
    {
        std::cerr<<"\nEnemyLoader: Panic! Unable to open load list for enemies! Can't procede!\n";
        log("\nEnemyLoader: Panic! Unable to open load list for enemies! Can't procede!\n");
        return false;
    }

    for (auto f : list)
    {
        std::string path = "./enemies/"+f.asString();
        file.open(path, std::ifstream::binary);
        Json::Value enemy;
        if(file.is_open())
        {
            file >> enemy;
            file.close();

            if (enemy["name"].isNull())
            {
                std::cerr<<"EnemyLoader: error #1; file "<<f.asString()<<" - attribute \"name\" is NULL (expected string). Skipping...\n";
                log("EnemyLoader: error #1; file "+f.asString()+" - attribute \"name\" is NULL (expected string). Skipping...\n");
            }

            try { this->enemies.emplace_back(new Enemy(enemy, library)); }
            catch (int e)
            {
                failures++;
                switch(e)
                {
                case 10:
                    std::cerr<<"EnemyLoader: error #"+std::to_string(e)+"; Card from file \""+ f.asString() +"\" - attribute \"name\" NULL (expected string).\n";
                    log("EnemyLoader: error #"+std::to_string(e)+"; Card from file \""+ f.asString() +"\" - attribute \"name\" NULL (expected string).\n");
                    break;
                case 20:
                    std::cerr<<"EnemyLoader: error #"+std::to_string(e)+"; Card \""+ enemy["name"].asString() +"\" - attribute \"hp\" is NULL (expected int).\n";
                    log("EnemyLoader: error #"+std::to_string(e)+"; Card \""+ enemy["name"].asString() +"\" - attribute \"hp\" is NULL (expected int).\n");
                    break;
                case 30:
                    std::cerr<<"EnemyLoader: error #"+std::to_string(e)+"; Card \""+ enemy["name"].asString() +"\" - attribute \"texture\" is NULL (expected object).\n";
                    log("EnemyLoader: error #"+std::to_string(e)+"; Card \""+ enemy["name"].asString() +"\" - attribute \"texture\" is NULL (expected object).\n");
                    break;
                case 31:
                    std::cerr<<"EnemyLoader: error #"+std::to_string(e)+"; Card \""+ enemy["name"].asString() +"\" - can't open texture file \""+ enemy["texture"]["file"].asString() +"\" .\n";
                    log("EnemyLoader: error #"+std::to_string(e)+"; Card \""+ enemy["name"].asString() +"\" - can't open texture file \""+ enemy["texture"]["file"].asString() +"\" .\n");
                    break;
                case 40:
                    std::cerr<<"EnemyLoader: error #"+std::to_string(e)+"; Card \""+ enemy["name"].asString() +"\" - attribute \"actions\" is NULL (expected array).\n";
                    log("EnemyLoader: error #"+std::to_string(e)+"; Card \""+ enemy["name"].asString() +"\" - attribute \"actions\" is NULL (expected array).\n");
                    break;
                
                default:
                    std::cerr<<"EnemyLoader: unidentified error #"<<e<<"\n";
                    log("EnemyLoader: unidentified error #"+std::to_string(e)+"\n");
                    break;
                }
            }
        }
        else 
        { 
            std::cerr<<"EnemyLoader: Can't open enemy file: \""<<f.asString()<<"\". Skipping...\n"; 
            log("EnemyLoader: Can't open enemy file: \""+f.asString()+"\". Skipping...\n");
            failures++; }
    }
    std::cerr<<"EnemyLoader: Loaded "<<this->enemies.size()<<" enemies, failed to load "<<failures<<".\n";
    log("EnemyLoader: Loaded "+std::to_string(this->enemies.size())+" enemies, failed to load "+std::to_string(failures)+".\n");
    return true;

}