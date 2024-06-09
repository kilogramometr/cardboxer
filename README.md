# Cardboxer
Cardboxer is a simple university project utilising SFML and JsonCpp libraries.

The player is controlling action of their character with cards they may drag and drop. The Goal is to defeat the enemies, who will try to defeat the player. Each defeated enemy results in one of three rewards - full heal, increased maxium health cap or a new card.

Should you want to add new cards to your version of the game, simply go to cards folder within the game folder. Cards are stored in .json format. To create a new card copy an existing one and modify it. For hints on possible options in a card see template.json and other cards. To change the card background edit res/textures/card.png, but under no circumstance change it's dimensions. Enemies are stored and can be modified like the cards. Currently adding new sprites is impossible.
