#ifndef TIME_H
#define TIME_H

#include <SFML/Graphics.hpp>
class Time
{
    public:
    Time();

    static sf::Clock timer;
    static double deltaTime;
    private:
};

#endif