#pragma once
#include <SFML/Graphics.hpp>
#include "myValue.h"
#include <vector>
#include "position.h"
#include <string>
#include <list>
using namespace std;
using namespace sf;

class Tower
{
  protected:
    position newPos;
    map<string,Texture> texture;
    unique_ptr<Sprite[]> objects;
  public:
    Tower(list<position>);
    void display(list<position>  ,RenderWindow & ,double & );
};
