#include "LissajousCurve.h"

int main()
{
    RenderWindow window(VideoMode(W, H), "Physical Simulation", Style::Close | Style::Titlebar);
    window.setFramerateLimit(60);

    Clock dtc;
    float t = 0;
    //

    LissajousCurve lc(W, H);
    lc.add_window(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();


        lc.generate(2, 3, 200);
        lc.draw();
        
        window.display();
    }

    return 0;
}
