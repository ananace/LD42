#pragma once

#include <SFML/Graphics/Color.hpp>

namespace Util
{

sf::Color hsv2rgb(float hue, float saturation, float value, float alpha = 1.f);

}
