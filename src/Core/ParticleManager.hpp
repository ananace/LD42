#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

namespace Core
{

class ParticleManager : public sf::Drawable
{
public:
    struct Particle
    {
        float Lifetime, Friction, RotationVelocity;
        sf::Color StartColor, EndColor;
        sf::Transform Transform;
        sf::Vector2f Velocity;
        sf::FloatRect UV;
    };

    ParticleManager();
    ParticleManager(const ParticleManager& copy) = default;
    ParticleManager(ParticleManager&& move) = default;
    ~ParticleManager() = default;

    ParticleManager& operator=(const ParticleManager& copyAssign) = default;
    ParticleManager& operator=(ParticleManager&& moveAssign) = default;

    void setTexture(const sf::Texture& texture);
    void setParticleCount(unsigned int particles);
    void clearParticles();

    void emitParticle(const Particle& definition);
    void update(float dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    // Used as a ring buffer for particle creation
    unsigned int m_maxParticles,
                 m_curParticle;

    sf::Texture m_texture;

    std::vector<float> m_lifetimes;
    std::vector<Particle> m_particles;
};

}
