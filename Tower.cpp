#include "Tower.h"
#include "cache.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <list>
#include "myValue.h"
using namespace std;
using namespace sf;

Tower::Tower(list<position> path) 
{
    objects = std::make_unique<sf::Sprite[]>(path.size());
    newPos.x=path.front().y*t;
    newPos.y=path.front().x*t;
    path.pop_front();
    newPos.mark=path.size();  
    texture["anim1"].loadFromImage(Cache::instance().get_image("anim1"));
    texture["anim2"].loadFromImage(Cache::instance().get_image("anim2"));
    texture["anim3"].loadFromImage(Cache::instance().get_image("anim3")); 
}


void Tower::display(list<position>  towers,RenderWindow & window,double & tt2) 
{
    static map<string,Texture>::iterator  it=texture.begin();
    if(tt2>tempTower)
    {
        if(it==texture.end())
            it=texture.begin();
        
        for(int i=0;i<towerCount;i++)
        {    
            objects[i].setPosition(towers.front().y*t,towers.front().x*t);
            towers.pop_front();        
            objects[i].setTexture(it->second);
        }
        it++;                 
        tt2=0;
    }
    for(int i=0;i<towerCount;i++)
        window.draw(objects[i]); 
};


