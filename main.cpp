#include "map.h"
#include "myValue.h"
#include "position.h"
#include "Enemy.h"
#include "Tower.h"
#include "cache.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

using namespace std;
using namespace sf;
#define GET_IMG Cache::instance().get_texture

int main()
{
    Cache::instance().load("anim1","img/anim1.png");
    Cache::instance().load("anim2","img/anim2.png");
    Cache::instance().load("anim3","img/anim3.png");
    Cache::instance().load("base","img/base.png");
    Cache::instance().load("enemy","img/enemy.png");
    Cache::instance().load("enemyBase","img/enemyBase.png");
    Cache::instance().load("road","img/road.png");
    Cache::instance().load("steps","img/steps.png");
    Cache::instance().load("tower","img/tower.png");
    gameMap myMap("MyM.txt");
    myMap.shortPath();
    myMap.sort(2);
    Enemy enemy1(myMap.enemyPath1);
    Enemy enemy2(myMap.enemyPath2);
    Enemy enemy3(myMap.enemyPath3);
    Tower towers(myMap.towers);
    RenderWindow window(VideoMode(1000, 1000), "SFML works!");
    double timer1=0.0,timer2=-5000.0,timer3=-1000.0,tt2=0.0;
    int h1=0,h2=0,h3=0,k1,k2,k3,i;
    Clock clock;

    while (window.isOpen())
    {
        double time=clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time=time/100;
        timer1+=time; timer2+=time; timer3+=time;
        tt2+=time;
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        myMap.display(window);
           
        enemy1.drawEnemy(myMap.enemyPath1,window,timer1);
        enemy2.drawEnemy( myMap.enemyPath2,window,timer2);   
        enemy3.drawEnemy(myMap.enemyPath3,window,timer3);
                
        enemy1.checkToDraw(myMap.enemyPath1,window);
        enemy2.checkToDraw(myMap.enemyPath2,window);
        enemy3.checkToDraw(myMap.enemyPath3,window);
       
        if(myMap.enemyPath1.size()!=0 || myMap.enemyPath2.size()!=0 || myMap.enemyPath3.size()!=0)
        {
            window.draw(enemy1.warrior);
            window.draw(enemy2.warrior);
            window.draw(enemy3.warrior);
            towers.display(myMap.towers,window,tt2);
        }   
       
        window.display();
    }

    return 0;
}
