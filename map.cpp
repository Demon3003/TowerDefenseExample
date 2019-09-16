#include "map.h"
#include <SFML/Graphics.hpp>
#include "myValue.h"
#include <string>
#include <list>
#include "cache.h"
#include <fstream>
#include "position.h"
using namespace sf;
using namespace std;
#define GET_IMG Cache::instance().get_image 
std::list<position> enemy1; position base;

    void gameMap::downloadMap(string path)
    {
        int i,k;
        ifstream input(path,ios::binary);
        for(i=0;i<border;i++)
        {
            for(k=0;k<border;k++)
            {
                input.read(reinterpret_cast<char*>(&map[i][k]),sizeof(map[i][k]));
            }
        }
        input.close();            
    };

    void gameMap::uploadMap(string path) 
    {
        int i,k;
        ofstream output(path,ios::binary);
        for(i=0;i<border;i++)
        {
            for(k=0;k<border;k++)
            {
                output.write(reinterpret_cast<char*>(&map[i][k]),sizeof(map[i][k]));
            }
        }
        output.close();            
    };

        
    int reserved[20][20];
    void gameMap::checkCell(int x, int y,int a, int b,position & enemy)
    {
        const short mapSize=20;
        if(x+a>=0 && x+a<mapSize && y+b>=0 && y+b<mapSize)
        {	
            if (reserved[x+a][y+b]==enemy.mark)
            {			
                reserved[x][y]=enemy.mark+1;

                if(map[x][y] == 'b')
                {
                    enemy.x=x;
                    enemy.y=y;
                }	
            }
        }

    };

    void  gameMap::checkArray(position  & enemy)
	{
		int k,f;
		const short mapSize=20;
		for (k=0; k<mapSize; k++)    
		{
			for(f=0;f<mapSize;f++)
			{				
				if (((map[k][f] == 'r') || (map[k][f] == 'b')) && (reserved[k][f] == -1))
				{
					checkCell(k,f,0,1,enemy);
					checkCell(k,f,1,0,enemy);
					checkCell(k,f,-1,0,enemy);
					checkCell(k,f,0,-1,enemy);	
				}
			}				
		}
	};

    void  gameMap::reversePath(int a ,int b,position & enemy,list<position> & path)
	{
		int x,y;
		x=enemy.x;
		y=enemy.y;
		const short mapSize=20;
		if(x+a>=0 && x+a<mapSize && y+b>=0 && y+b<mapSize)
		{
			if (reserved[x+a][y+b]==enemy.mark-1)
			{			
				position newPos ;
				newPos.x=x+a;
				newPos.y=y+b;
				path.push_front(newPos);
				enemy.mark--;
				enemy.x=x+a;
				enemy.y=y+b;
			
			}
		}
		
	};

    void gameMap::PathBack(position &enemy,list<position> &path)
    {
        while(enemy.mark!=0)
        {
            reversePath(0,1,enemy,path);
            if(enemy.mark==0)
                break;
            reversePath(1,0,enemy,path);
            if(enemy.mark==0)
                break;
            reversePath(-1,0,enemy,path);
            if(enemy.mark==0)
                break;
            reversePath(0,-1,enemy,path);
            if(enemy.mark==0)
                break;
        }
    }

    void gameMap::shortPath()
    {
        const short mapSize=20;
        vector<list<position> > enemyPath;
        for(list<position>::iterator it=enemy1.begin();it!=enemy1.end();it++)
        {  
            position enemy=*it;    
            int f,k;
            for (f = 0; f < mapSize; f++)
            {
                for (k = 0; k < mapSize; k++)
                    reserved[f][k] = -1;
            }
            reserved[enemy.x][enemy.y] = 0;
            
            while((enemy.x != base.x) || (enemy.y != base.y))
            {
                checkArray(enemy);
                enemy.mark++;		
            }	

            list<position> path;
            path.push_front(enemy);

            PathBack(enemy,path);
            enemyPath.push_back(path);
        }
        enemyPath1=enemyPath[0];
        enemyPath2=enemyPath[1];
        enemyPath3=enemyPath[2];
    };


    void gameMap::setBorders(int &b1,int &b2,int&b3,int &b4,int radius)
    {
        b1=towers.front().x - radius;
        b2=towers.front().x + radius;
        b3=towers.front().y - radius;
        b4=towers.front().y + radius ;

        if(b1<0)
            b1=0;
        if(b2>19)
            b2=19;
        if(b3<0)
            b3=0;
        if(b4>19)
            b4=19; 
    };

    void gameMap::sort(int radius)
    {
        int i,sz,b1,b2,b3,b4;
        const short enemCount=3;
        const int cell=20;
        vector<list<position> > enemyPath (enemCount);
        sz=towers.size();
        
        for(i=0;i<sz;i++)
        {
            setBorders(b1,b2,b3,b4,radius);
            checkPerimetr(enemyPath, b1,b2,b3,b4);
            position newPos =towers.front();
            towers.pop_front();
            towers.push_back(newPos);
        }

        vector<position> reserve(sz);
        for(i=0;i<sz;i++)
        {
            reserve[i]=towers.front();
            towers.pop_front();
        }

        bubbleSort(reserve);
    };


    void gameMap::bubbleSort(vector<position> & reserve)
    {
        int p1,p2,size;
        size=reserve.size();
        for(p2=0;p2<size;p2++)
        {
            for(p1=0;p1<size-p2-1;p1++)
            {
                if(reserve[p1].mark<reserve[p1+1].mark)
                {
                    position newPosition =reserve[p1+1];
                    reserve[p1+1]=reserve[p1];
                    reserve[p1]=newPosition;        

                }   
            }
        }
        for(int i=0;i<reserve.size();i++)
            towers.push_back(reserve[i]);
        towers.resize(towerCount);
    };

  
    void gameMap::checkPerimetr(vector<list<position> > & enemyPath,int b1,int b2,int b3,int b4)
    {
        int p1,p2;
        for(p1=b1;p1<=b2;p1++)
        {
            for(p2=b3;p2<=b4;p2++)
            {
                enemyPath.push_back(enemyPath1);
                enemyPath.push_back(enemyPath2);
                enemyPath.push_back(enemyPath3);
                    
                if(map[p1][p2]=='r')
                {
                    checkForOne(p1,p2,enemyPath);             
                }
                enemyPath.clear();        
            }
        }
    };




    void gameMap::checkForOne(int p1,int p2,vector<list<position> > enemyPath)
    {
        int size1,size2;
        for(size1=0;size1<enemyPath.size();size1++)
        {
            size2=enemyPath[size1].size();
            while(size2>0)
            {
                if((p1==enemyPath[size1].front().x) && (p2==enemyPath[size1].front().y))
                {
                    towers.front().mark++;
                }
                enemyPath[size1].pop_front();
                size2--;

            }
        }    
    }

    gameMap::gameMap(string s)
    {
        texture["base"].loadFromImage(GET_IMG("base")); texture["road"].loadFromImage(GET_IMG("road"));
        texture["enemyBase"].loadFromImage(GET_IMG("enemyBase")); texture["tower"].loadFromImage(GET_IMG("tower"));
        downloadMap(s);
        int i,k,a=0,b=0;
        position newPosition;
        for(i=0;i<border;i++)
        {
            for(k=0;k<border;k++)
            {
                if(map[i][k]==' ')
                    drawableMap[i][k].setTexture(texture[""]);

                if(map[i][k]=='b')
                {
                    drawableMap[i][k].setTexture(texture["base"]);
                    base.x=i;
                    base.y=k;
                }

                if(map[i][k]=='r')
                    drawableMap[i][k].setTexture(texture["road"]);
                   
                if(map[i][k]=='t')
                {
                    drawableMap[i][k].setTexture(texture["tower"]);
                    newPosition.x=i;
                    newPosition.y=k;
                    towers.push_back(newPosition);        
                }  

                if(map[i][k]=='e')
                {
                    drawableMap[i][k].setTexture(texture["enemyBase"]);
                    newPosition.x=i;
                    newPosition.y=k;
                    enemy1.push_back(newPosition);
                }
                drawableMap[i][k].setPosition(a,b);
                a=a+t;
            }
            b=b+t;
            a=0;
        }
    }

    void gameMap::display(RenderWindow & window)
    {
        for(int i=0;i<border;i++)
        {
            for(int k1=0;k1<border;k1++)
            {
              window.draw(drawableMap[i][k1]);
            }
        }
    }