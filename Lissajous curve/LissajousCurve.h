#pragma once

#include "h.h"

class LissajousCurve
{
public:
	RenderTexture rt;

	LissajousCurve(float w, float h) {
		this->w = w;
		this->h = h;
		rt.create(w, h);
		center = Vector2f(W/2, H/2);
	}

	void add_window(RenderWindow &w) {
		window = &w;
	}

	void draw() {
		Sprite sprite(rt.getTexture());
        (*window).draw(sprite);
	}

	void generate(float a, float b, float scale, float r=5, float k=1000) {
		rt.clear();
		
		for (float t=0; t <= 2; t += PI/k) {
			Vector2f p = Vector2f(sin(a*t*PI), cos(b*t*PI));

			CircleShape c(r); c.setFillColor(Color::Green);
			c.setPosition( p * scale + center );

			rt.draw(c);
		}
		//rt.display();
	}

private:
	float w, h;

	Vector2f center;

	RenderWindow *window;
};
