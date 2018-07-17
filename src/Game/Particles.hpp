#pragma once

#include <Math.hpp>
#include <ParticleManager.hpp>
#include "Util.hpp"

#include <random>

namespace Particles
{

typedef Core::ParticleManager::Particle Particle;

std::random_device g_random;

// 1x1 white pixel that lives 5s, for debugging
Particle Debug(const sf::Vector2f& pos) {
    sf::Transform transform;
    transform.translate(pos);
    return { 5, 0, 0, sf::Color::White, sf::Color::Red, transform, { }, { 0, 0, 1, 1 } };
}

Particle FireworkBurst(const sf::Vector2f& pos, float hue) {
    using Core::Math::Pi;

    std::uniform_real_distribution<float> value(0.75f, 1.f);
    std::uniform_real_distribution<float> force(120.f, 1024.f);
    std::uniform_real_distribution<float> angle(0.f, 2.f * Pi<float>());
    std::uniform_real_distribution<float> rotation(0.f, 2.f * Pi<float>());

    sf::Color startColor = Util::hsv2rgb(hue, 1.f, value(g_random)),
              endColor(75, 75, 75, 75);

    sf::Transform transform;
    transform.translate(pos);

    float ang = angle(g_random);
    float speed = force(g_random);
    sf::Vector2f velocity(cos(ang) * speed, sin(ang) * speed);

    return {
        1.5f,  // Lifetime, seconds
        0.25f, // Friction, % per second
        (Pi<float>() - rotation(g_random)), // Rotation velocity, radians per second
        startColor, // Starting colour
        endColor,   // Ending colour
        transform,  // Starting transform
        velocity,   // Starting velocity, pixels per second
        { 0, 0, 4, 4 } // Particle spritesheet rectangle
    };
}

}
