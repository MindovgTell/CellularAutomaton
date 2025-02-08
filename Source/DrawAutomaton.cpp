#include "DrawAutomaton.hpp"

void DrawAutomaton::init_window()
{
    this->videoMode.width = this->width*5;
    this->videoMode.height = this->height*5;
    this->window = new sf::RenderWindow(this->videoMode, "Cellular Automaton", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

DrawAutomaton::DrawAutomaton(CellularAutomaton& c, int height, int width): ca(c)  
{
    this->height = height;
    this->width = width;
    this->init_window();
    this->init_grid();
}

DrawAutomaton::~DrawAutomaton()
{
    delete this->window;
}

const bool DrawAutomaton::running() const 
{
    return this->window->isOpen(); 
}

void DrawAutomaton::pollEvent()
{
    while(this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if(this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            else if(this->event.key.code == sf::Keyboard::N)
            {
                random_grid();
                std::cout << ca.get_function_number() << '\n';
            }
            else if(this->event.key.code == sf::Keyboard::S)
            {
                this->ca.random_state();
                update_grid();
            }
            else if(this->event.key.code == sf::Keyboard::R)
            {
                this->ca.random_function();
                this->ca.reinit_wolfram_code();
                update_grid();
            }
            else if(this->event.key.code == sf::Keyboard::C)
            {
                this->ca.corn_state(1);
                update_grid();
            }
            break;
        default:
            break;
        }
    }
}

sf::RectangleShape DrawAutomaton::set_shape(int i)
{
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(5.f,5.f));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    std::string str = this->ca.get_state();
        if(str[i] == '0')
            shape.setFillColor(sf::Color::Blue);
        else if(str[i] == '1')
            shape.setFillColor(sf::Color::Green);
        else if(str[i] == '2')
            shape.setFillColor(sf::Color::Red);
    return shape;
}

void DrawAutomaton::init_grid()
{
    for(int i = 0; i != this->height; ++i)
    {
        std::vector<sf::RectangleShape> vec;
        for(int j = 0; j != this->width; ++j)
        {
            sf::RectangleShape shape = set_shape(j);
            shape.setPosition(sf::Vector2f(5.f * j, 5.f * i));
            vec.push_back(shape);
        }
        this->grid.push_back(vec);
        this->ca(); 
    }
}

void DrawAutomaton::update_grid()
{   
    std::vector<std::vector<sf::RectangleShape> > new_grid;
    for(int i = 0; i != this->height; ++i)
    {
        std::vector<sf::RectangleShape> vec;
        for(int j = 0; j != this->width; ++j)
        {
            sf::RectangleShape shape = set_shape(j);
            shape.setPosition(sf::Vector2f(5.f * j, 5.f * i));
            vec.push_back(shape);
        }
        new_grid.push_back(vec);
        this->ca(); 
    }
    this->grid = new_grid;

}

void DrawAutomaton::random_grid()
{
    this->ca.random_function();
    this->ca.random_state();
    this->ca.reinit_wolfram_code();
    this->update_grid();
}

void DrawAutomaton::renderGrid(sf::RenderTarget* target)
{
    for(int i = 0; i != this->height; ++i)
    {
        for(int j = 0; j != this->width; ++j)
        {
            // sf::RectangleShape shape = set_shape(j);
            // shape.setPosition(sf::Vector2f(5.f * j, 5.f * i));
            // target->draw(shape);
            target->draw(this->grid[i][j]);
        }
    }
}

void DrawAutomaton::render()
{
    this->window->clear(sf::Color::Black);
    this->renderGrid(this->window);
    this->window->display();
}

void DrawAutomaton::update()
{
    this->pollEvent();
}