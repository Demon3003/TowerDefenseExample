#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include "myValue.h"
#include "cache.h"
#include <list>
#include <memory>
using namespace std;
using namespace sf;

Enemy::Enemy(list<position> & enemyPath)  : Tower(enemyPath)
{
    texture["enemy"].loadFromImage(Cache::instance().get_image("enemy"));
    texture["steps"].loadFromImage(Cache::instance().get_image("steps"));
    warrior.setTexture(texture["enemy"]);
    warrior.setPosition(enemyPath.front().y*t,enemyPath.front().x*t);
    enemyPath.pop_front(); 
};


void  Enemy::drawEnemy(list<position> & enemyPath,RenderWindow & window,double & tt) 
{  
    int k,h;
    k=enemyPath.size();
        
    for(int i=0;i<k;i++)
    {
       if(tt>temp)
        {
            newPos.x=enemyPath.front().y*t-newPos.x;
            newPos.y=enemyPath.front().x*t-newPos.y;
            warrior.move(newPos.x,newPos.y);
            window.draw(warrior);
            h=newPos.mark-enemyPath.size();
            objects[h].setTexture(texture["steps"]);   
            objects[h].setPosition(enemyPath.front().y*t,enemyPath.front().x*t);

            for(int u=0;u<h+1;u++)
                window.draw(objects[u]);  
          
            h++;
            if(h==newPos.mark)
            {
                h=0;
            }
            newPos.x=enemyPath.front().y*t;
            newPos.y=enemyPath.front().x*t;
            enemyPath.pop_front();  
            tt=0;
        }

    };    
}
void Enemy::checkToDraw(list<position> enemyPath,RenderWindow & window)
{
    if(enemyPath.size()!=0)
    {
        for(int u=0;u<newPos.mark-enemyPath.size()+1;u++)
        window.draw(objects[u]);  
    }

};
/*DrawEnemy::DrawEnemy(list<position> & enemyPath)    
{
    enemyImg.loadFromFile("img/enemy.png",IntRect(0,0,t,t)); steps.loadFromFile("img/steps.png",IntRect(0,0,t,t));
    circle1.setTexture(enemyImg);
    circle1.setPosition(enemyPath.front().y*t,enemyPath.front().x*t);
    newX1=enemyPath.front().y*t;
    newY1=enemyPath.front().x*t;
    enemyPath.pop_front();
    pathSize=enemyPath.size();
    
    circle11= make_unique<Sprite[]>(enemyPath.size());
   
};
void DrawEnemy::display(list<position> & enemyPath,RenderWindow & window,double & tt)
{  
    int k,h;
  k=enemyPath.size();
        
    for(int i=0;i<k;i++)
    {
       if(tt>temp)
        {
            newX1=enemyPath.front().y*t-newX1;
            newY1=enemyPath.front().x*t-newY1;
            circle1.move(newX1,newY1);
            window.draw(circle1);
            h=pathSize-enemyPath.size();
            circle11[h].setTexture(steps);   
            circle11[h].setPosition(enemyPath.front().y*t,enemyPath.front().x*t);

            for(int u=0;u<h+1;u++)
                window.draw(circle11[u]);  
          
            h++;
            if(h==pathSize)
            {
                h=0;
            }
            newX1=enemyPath.front().y*t;
            newY1=enemyPath.front().x*t;
            enemyPath.pop_front();  
            tt=0;
        }

    };    
}
void DrawEnemy::checkToDraw(list<position> enemyPath,RenderWindow & window)
{
    if(enemyPath.size()!=0)
    {
        for(int u=0;u<pathSize-enemyPath.size()+1;u++)
        window.draw(circle11[u]);  
    }

};
*/