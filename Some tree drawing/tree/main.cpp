#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "windows.h"

using namespace std; 
using namespace sf;

int main()
{
    srand(0);

    const int W=1000, H=850;
    const int ln = 5;
    unsigned long long len_of_tree = 0;
    vector<Vector2i> crr_pts = { Vector2i(W/2, 0) };

    RenderWindow window(VideoMode(W, H), "Magic Tree");
    RenderTexture texture;
    texture.create(W, H);

    while (window.isOpen())
    {
        vector<Vector2i> new_pts;
        
        if (crr_pts[0].y <= H) {
            for (int i=0; i<crr_pts.size(); i++) {
                int r = rand() % 3;
                Vector2i c = crr_pts[i];
            
                Vector2i le = c + Vector2i(-ln, ln),
                         ri = c + Vector2i(ln, ln);

                if (new_pts.size() != 0 and new_pts[new_pts.size()-1] == le) le = ri;

                if (r == 0) {
                    if (le == ri) le = ri = c;
                    else {
                        ri = le;
                        new_pts.push_back(le);
                    }
                }
                else if (r == 1) {
                    le = ri;
                    new_pts.push_back(ri);
                }
                else if (r == 2) {
                    if (le != ri) new_pts.push_back(le); 
                    new_pts.push_back(ri);
                }

                Vertex arms[] = { Vertex(Vector2f(le)), Vertex(Vector2f(c)), Vertex(Vector2f(ri)) }; 
                texture.draw(arms, 3, LinesStrip);
            }
            crr_pts = new_pts;

            len_of_tree++;
            std::cout << len_of_tree << '\n';
        }

        //

        Event e;
        while (window.pollEvent(e))
            if (e.type == Event::Closed) window.close();

        window.clear();

        sf::Sprite sprite(texture.getTexture());
        window.draw(sprite);

        window.display();

        //Sleep(200);
    }

    return 0;
}