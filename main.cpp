#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1000, 600), "Tennis!");

    RectangleShape line(Vector2f(2, 600));
    line.setFillColor(Color::White);
    line.setPosition(500, 0);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(line);
        
        window.display();
    }

    return 0;
}S