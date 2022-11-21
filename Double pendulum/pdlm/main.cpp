#include <SFML/Graphics.hpp>

#define PI 3.14159265

using namespace std; 
using namespace sf;

CircleShape add_circle(float r) {
    CircleShape c(r);
    c.setFillColor(Color::Black);
    c.setOutlineThickness(1);
    c.setOutlineColor(Color::White);
    return c;
}

int main()
{
    const int W=600, H=600;
    Vector2f ctr_brc{W/2, H/2};

    const float g = 0.6;
    float a1_v = 0, a2_v = 0;

    const float r1 = 150, r2 = 100;
    const float m1 = 30, m2 = 15;
    float a1 = PI, a2 = PI; 

    RenderWindow window(VideoMode(W, H), "Double Pendulum");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    CircleShape ctr_point(3); ctr_point.setFillColor(Color::White);
    ctr_point.setPosition(ctr_brc - Vector2f(3, 3));

    CircleShape bob1 = add_circle(m1);
    CircleShape bob2 = add_circle(m2);

    while (window.isOpen())
    {
        float n1 = -g * (2*m1 + m2) * sin(a1),
              n2 = -m2*g*sin(a1 - 2*a2),
              n3 = -2*sin(a1-a2)*m2,
              n4 = a2_v*a2_v*r2 + a1_v*a1_v*r1*cos(a1-a2),
              den = r1 * (2*m1 + m2 - m2*cos(2*a1 - 2*a2)),
             
              a1_a = (n1 + n2 + n3*n4) / den;

        n1 = 2*sin(a1-a2);
        n2 = a1_v*a1_v*r1*(m1+m2);
        n3 = g*(m1+m2)*cos(a1);
        n4 = a2_v*a2_v*r2*m2*cos(a1-a2);
        den = r2*(2*m1 + m2 - m2*cos(2*a1 - 2*a2));
        float a2_a = n1 * (n2+n3+n4) / den;

        a1_v += a1_a;
        a2_v += a2_a;

        a1 += a1_v;
        a2 += a2_v;

        bob1.setPosition(ctr_brc + Vector2f(sin(a1), cos(a1))*r1 - Vector2f(m1, m1));
        bob2.setPosition(bob1.getPosition() + Vector2f(m1, m1) + Vector2f(sin(a2), cos(a2))*r2 - Vector2f(m2, m2));
        
        Vertex arms[] = {Vertex(ctr_brc), Vertex(bob1.getPosition() + Vector2f(m1, m1)), Vertex(bob2.getPosition() + Vector2f(m2, m2))}; 

        Event e;
        while (window.pollEvent(e))
            if (e.type == Event::Closed) window.close();

        window.clear();
        window.draw(arms, 3, LinesStrip);
        window.draw(ctr_point);
        window.draw(bob1); window.draw(bob2);
        window.display();
    }

    return 0;
}