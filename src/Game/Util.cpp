#include "Util.hpp"

#include <cmath>

sf::Color Util::hsv2rgb(float hue, float saturation, float value, float alpha)
{
    if (saturation <= 0.f)
        return sf::Color::Black;

    if (hue >= 360.f)
        hue = 0.f;
    hue /= 60.f;

    auto iHue = int(hue);
    float hueRemain = hue - iHue;

    float p = value * (1.f - saturation),
          q = value * (1.f - (saturation * hueRemain)),
          t = value * (1.f - (saturation * (1.f - hueRemain)));

    switch (iHue)
    {
    case 0:  return sf::Color(value, t, p, sf::Uint8(alpha * 255));
    case 1:  return sf::Color(q, value, p, sf::Uint8(alpha * 255));
    case 2:  return sf::Color(p, value, t, sf::Uint8(alpha * 255));
    case 3:  return sf::Color(p, q, value, sf::Uint8(alpha * 255));
    case 4:  return sf::Color(t, p, value, sf::Uint8(alpha * 255));
    default: return sf::Color(value, p, q, sf::Uint8(alpha * 255));
    };
}
