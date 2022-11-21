#pragma once

#include <SFML/Graphics.hpp>

#define W 800
#define H 800

#define PI 3.14159265

using namespace sf;
using namespace std;

inline float len(Vector2f p) {
	return sqrt(p.x*p.x + p.y*p.y);
}
