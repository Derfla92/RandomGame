#ifndef GUI_H
#define GUI_H

#include<string>

class GUI
{
    public:
    GUI();

    void Update();

    private:

    void Button();
    void Image();
    void Text(const std::string&);

};

#endif