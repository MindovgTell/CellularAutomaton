#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "CellularAutomaton.hpp"


class DrawAutomaton
{
private:
    int height;
    int width;
    sf::VideoMode videoMode;
    sf::RenderWindow* window;

    sf::Event event;

    CellularAutomaton ca;

    std::vector<std::vector<sf::RectangleShape> > grid;
    void init_grid();
    void init_window();
public:
     
    DrawAutomaton(CellularAutomaton& c, int height, int width);
    ~DrawAutomaton();

    sf::RectangleShape set_shape(int);

    void pollEvent();
    const bool running() const;

    void random_grid();

    void update_grid();
    void update();
    void render();
    void renderGrid(sf::RenderTarget* target);

};
