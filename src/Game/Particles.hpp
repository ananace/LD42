#pragma once

#include <ParticleManager.hpp>

namespace Particles
{

typedef Core::ParticleManager::Particle Particle;

// 1x1 white pixel that lives 5s, for debugging
Particle Debug(const sf::Vector2f& pos) {
    sf::Transform transform;
    transform.translate(pos);
    return { 5, 0, 0, sf::Color::White, sf::Color::Red, transform, { }, { 0, 0, 1, 1 } };
};

}
