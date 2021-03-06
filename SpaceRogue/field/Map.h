#ifndef MAP_H
#define MAP_H

#include <memory>
#include <random>
#include <list>
#include <QObject>
#include <QThread>
#include <QList>

#include "DungeonGeneration.hpp"
#include "FoV.hpp"
#include "../player/Player.h"
#include "../player/MovePlanner.h"
#include "../enemies/Enemy.h"


//#include "../enemies/Enemy.h"

//! �����, ������� �������� ����� ���������. � ����� field ��� �� ����� ���� ��������� ������ ��� ��������� ����� � ����..
// ��� � ��� ����� ����������? ����������� �������/�������?
static const int MAP_WIDTH = 40;
static const int MAP_HEIGHT = 33;

/**
 * @brief The Map class
 * Size of level is constant
 */
class Map : public QThread
{
    Q_OBJECT

public:
    Map(int difficulty);
    ~Map();

    //!
    virtual void run() override;

    //! ����� ���������. ������ �� ���������� �������� � ���������.
    //! ����� ������� �� �������� ����, ����� ����� ������ ������������������?
    void setDifficulty(int difficulty);

    //! Method sets main player
    void setPlayer(Player* player);

    //! Method returns player
    Player* getPlayer();

    //! Method generates level with MapCreator and then places different objects
    void generateLevel();

    //! Method returns width of the map
    int getWidth();

    //! Method returns height of the map
    int getHeight();

    //! Methods returns list with alive objects
    std::list<Alive*> &getAlive();

    //! Method returns level
    int **getLevel();
    int **getVision();
    DunGen::Room *getNearestRoom(QList<DunGen::Room *> rooms, Vector2f pos);
    int getDistance(Vector2f first, Vector2f second);

    //! Method if player controlled ouside program
    void movePlayer(int key); // reformat this

    //! Method moves player to his aim
    void movePlayer();

    //! Method analyse map and set aim to player
    void findPlayerAim();

    //! Method move creature to newPosition, if it is possible
    void moveCreature(Alive* creature, Vector2f newPosition);

    //! Method moves enemies
    void moveEnemies();

    //! Method returns player's spawn position
    Vector2f getPlayerStartPosition();

    //! Method returns position of stairs
    Vector2f getStairsPosition();

    //! Method returns the current number of level
    int getLevelNumber();

    //! Method checks if player moves toward enemy
    bool isSomebodyHere(Vector2f pos);

    //! Method checks if player near enemy
    bool isPlayerNear(Alive *creature);

    //! Method moves enemies and player
    void makeTurn();

signals:
    //!
    void newEvent(const QString &text);
    //! Signal is emitted when we move to next level
    void newLevel();
    //!
    void newTurn(int turn);
    //!
    void gameOver();
    //!
    void updateWindow();

private:
    //!
    void placePlayer();
    //!
    void placeStairs();
    //!
    void placeEnemies();
    //!
    void placeItems();
    //! Method adds a bit of traps in random places in rooms
    void placeTraps();

    FOV* fov;
    DunGen::Map *mapCreator;
    //! data structure that contains map (4 width, 3 height)
    int **level;
    int **vision;
    //! Vector with rooms placed on level
    std::vector<DunGen::Room*> rooms;
    //!
    QList<DunGen::Room*> visited;
    QList<DunGen::Room*> unvisited;
    DunGen::Room* playerAim;
    //! List with all objects
    //std::list<std::shared_ptr<Object>> objects;
    //! List with alive objects
    std::list<Alive*> alive;
    //! Position where player is spawned
    sf::Vector2f playerStartPosition;
    //! Position of stairs to next level
    sf::Vector2f stairsPosition;
    //! Vector of traps
    std::vector<Vector2f> traps;
    //!
    int turn;
    int difficulty;
    int levelNumber;
    Player* player;
    MovePlanner *movePlanner;
    std::random_device rd;
    std::mt19937 mt;
};

#endif // MAP_H
