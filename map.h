#pragma once 
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <list>
#include "position.h"

class gameMap
{
    private:
        char map[20][20];
        std::map<std::string,sf::Texture> texture;
        sf::Sprite drawableMap[20][20];
        void checkCell(int x, int y,int a, int b,position &  enemy);
        void checkArray(position  & enemy);
        void PathBack(position &enemy,std::list<position> &path);
        void reversePath(int a ,int b,position & enemy,std::list<position> & path);   
        void setBorders(int &b1,int &b2,int&b3,int &b4,int);
        void bubbleSort(std::vector<position>& reserve);
        void checkForOne(int p1,int p2,std::vector<std::list<position> > enemyPath);
        void checkPerimetr(std::vector<std::list<position> > & enemyPath,int b1,int b2,int b3,int b4); 

    public:
        std::list<position> enemyPath1,enemyPath2,enemyPath3,towers;
        void display(sf::RenderWindow &);
        void shortPath();
        void sort(int radius); 
        void downloadMap(std::string path);        
        void uploadMap(std::string path);   
        gameMap(std::string s);
};