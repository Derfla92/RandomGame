#include "Camera.h"
#include "Game.h"
#include <iostream>

Camera::Camera()
    : viewport{sf::FloatRect(0, 0, 1920, 1080)}
{
}

void Camera::CameraMovement()
{
    //Camera Movement
    if (sf::Mouse::getPosition(Game::Window).x > 0 && sf::Mouse::getPosition(Game::Window).x < 20)
    {
        viewport.setCenter(viewport.getCenter() + sf::Vector2<float>{-1 * panSpeed * static_cast<float>(Game::time.deltaTime), 0} );
    }
    else if (sf::Mouse::getPosition(Game::Window).x > static_cast<int>(Game::Window.getSize().x) - 20 && sf::Mouse::getPosition(Game::Window).x < static_cast<int>(Game::Window.getSize().x))
    {
        viewport.setCenter(viewport.getCenter() + sf::Vector2<float>{1 * panSpeed * static_cast<float>(Game::time.deltaTime), 0});
    }
    if (sf::Mouse::getPosition(Game::Window).y > 0 && sf::Mouse::getPosition(Game::Window).y < 20)
    {
        viewport.setCenter(viewport.getCenter() + sf::Vector2<float>{0, -1 * panSpeed * static_cast<float>(Game::time.deltaTime)});
    }
    else if (sf::Mouse::getPosition(Game::Window).y > static_cast<int>(Game::Window.getSize().y) - 20 && sf::Mouse::getPosition(Game::Window).y < static_cast<int>(Game::Window.getSize().y))
    {
        viewport.setCenter(viewport.getCenter() + sf::Vector2<float>{0, 1 * panSpeed * static_cast<float>(Game::time.deltaTime)});
    }
}

void Camera::CameraZoom(int mouseWheelDelta)
{
    if (mouseWheelDelta > 0)
    {
        viewport.setSize(viewport.getSize().x * 0.99f, viewport.getSize().y * 0.99f);
    }
    else
    {
        viewport.setSize(viewport.getSize().x * 1.01f, viewport.getSize().y * 1.01f);
    }
    std::cout << viewport.getSize().x << ", " << viewport.getSize().y << std::endl;
}