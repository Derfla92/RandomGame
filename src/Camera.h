#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>


class Camera
{
    public:
    Camera();
    void CameraMovement();
    void CameraZoom(int);
    sf::View viewport;
    private:
    int panSpeed{100};
    int zoom{1};
    
};


#endif