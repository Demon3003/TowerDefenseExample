#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"
#include "map.h"
#include <list>
#include <memory>
using namespace sf;
using namespace std;

class Enemy : public Tower
{
  public:
    Sprite warrior;
    void checkToDraw(std::list<position> enemyPath,RenderWindow & window);
    void drawEnemy(std::list<position> & enemyPath,RenderWindow & window,double &); 
    Enemy(std::list<position> & enemyPath);
};

