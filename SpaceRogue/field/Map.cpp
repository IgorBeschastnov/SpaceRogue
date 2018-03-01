#include "Map.h"



Map::Map(int difficulty) :
    mapCreator(new DunGen::Map(MAP_WIDTH,MAP_HEIGHT)),
    difficulty(difficulty), levelNumber(0)
{
    generateLevel();
}


Map::~Map()
{
}

void Map::setDifficulty(int difficulty)
{
    this->difficulty = difficulty;
}

void Map::setPlayer(Player *player)
{
    //add plyaer to list
    this->player = player;
    // add to player coordinates of generation
    player->setPosition(playerStartPosition);
}

Player *Map::getPlayer()
{
    return player;
}

void Map::generateLevel()
{
    //create level
    level = mapCreator->generateLevel(100,3,10);
    rooms = mapCreator->getRooms();
    // select random room for init of player
    placePlayer();
    // select random rooms and create enemies (depends on difficulty, cannot be in one room with player??)

    // select random rooms and create items (depends on difficulty)
    levelNumber++;
    emit nextLevel(levelNumber);
}

int Map::getWidth()
{
    return MAP_WIDTH;
}

int Map::getHeight()
{
    return MAP_HEIGHT;
}

int **Map::getLevel()
{
    return level;
}

void Map::movePlayer(int key)
{
    QString message;
    if (key == 16777236)
    {
//        key = "Right";
        if (level[(int)player->getPosition().x+1][(int)player->getPosition().y] != 1)
        {
            player->setPosition(Vector2f(player->getPosition().x+1, player->getPosition().y));
        }else {message="Sorry, you cannot move through walls";}
    }
    else if (key == 16777234)
    {
//        key = "Left";
        if (level[(int)player->getPosition().x-1][(int)player->getPosition().y] != 1)
        {
            player->setPosition(Vector2f(player->getPosition().x-1, player->getPosition().y));
        }else {message="Sorry, you cannot move through walls";}

    }
    else if (key == 16777235)
    {
//        key = "Up";
        if (level[(int)player->getPosition().x][(int)player->getPosition().y-1] != 1)
        {
            player->setPosition(Vector2f(player->getPosition().x, player->getPosition().y-1));
        }else {message="Sorry, you cannot move through walls";}\
    }
    else if (key == 16777237)
    {
//        key = "Down";
        if (level[(int)player->getPosition().x][(int)player->getPosition().y+1] != 1)
        {
            player->setPosition(Vector2f(player->getPosition().x, player->getPosition().y+1));
        }else {message="Sorry, you cannot move through walls";}

    }
    if (!message.isEmpty())
    {
        emit newEvent(message);
    }
}

Vector2f Map::getPlayerStartPosition()
{
    return playerStartPosition;
}

void Map::placePlayer()
{
    playerStartPosition = Vector2f(rooms.front()->center()[0], rooms.front()->center()[1]);
}
