#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

class Cache
{
    public:
        void load(string s,string f);
        sf::Image get_image(string s);
        
        Cache(const Cache&)=delete;
        Cache & operator=(const Cache&)=delete;
        static Cache &instance()
        {
            static Cache m_cache;
            return m_cache;
        }
    private:
        unordered_map<string,sf::Image> myCache;
        Cache()=default;
};