#ifndef NAMEGENERATOR_H
#define NAMEGENERATOR_H

#include <string>
#include <vector>

namespace NameGenerator
{
    static const std::vector<std::string> firstName{
        "Guy",
        "Charles",
        "Alfred",
        "Billy",
        "Roy"};

    std::string GenerateName()
    {
        std::string name{};
        int random{rand()%static_cast<int>(firstName.size())};
        name = firstName[random];
        return name;
    }
}

#endif