#include "cache.h"
#include "myValue.h"
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;

Image Cache::get_image(std::string s)
{
    return myCache[s];
}

void Cache::load(std::string s,std::string fNmae)
{
    myCache[s].loadFromFile(fNmae);

}
