#include "ParticleManager.hpp"
#include "Math.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>

using namespace Core::Math;
using Core::ParticleManager;

ParticleManager::ParticleManager()
    : m_maxParticles(0)
    , m_curParticle(0)
{ }

void ParticleManager::setParticleCount(unsigned int particles)
{
    if (m_maxParticles > particles)
        m_curParticle = 0;
    m_maxParticles = particles;

    m_particles.resize(m_maxParticles);
    m_lifetimes.resize(m_maxParticles, 0);
}
void ParticleManager::clearParticles()
{
    m_curParticle = 0;
    for (unsigned int i = 0; i < m_maxParticles; ++i)
        m_lifetimes[i] = 0;
}

void ParticleManager::emitParticle(const Particle& definition)
{
    unsigned int iters = 0;
    while (m_lifetimes[m_curParticle] > 0)
    {
        if (++iters >= m_maxParticles)
            return;
        if (++m_curParticle >= m_maxParticles)
            m_curParticle = 0;
    }

    m_particles[m_curParticle] = definition;
    m_lifetimes[m_curParticle] = definition.Lifetime;
}

void ParticleManager::update(float dt)
{
    sf::Vector2f frictionStore;
    for (unsigned int i = 0; i < m_maxParticles; ++i)
    {
        if (m_lifetimes[i] <= 0)
            continue;

        auto& particle = m_particles[i];

        frictionStore = particle.Velocity * (particle.Friction * -1);
        particle.Velocity += frictionStore * dt;

        particle.Transform
            .translate(particle.Velocity)
            .rotate(particle.RotationVelocity);

        particle.Lifetime -= dt;
    }
}

void ParticleManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &m_texture;

    sf::RenderStates stateCopy = states;
    sf::Vertex vertices[4] = {
        { { -0.5f, -0.5f }, sf::Color::White, { 0, 0 } },
        { { -0.5f,  0.5f }, sf::Color::White, { 0, 1 } },
        { {  0.5f,  0.5f }, sf::Color::White, { 1, 1 } },
        { {  0.5f, -0.5f }, sf::Color::White, { 1, 0 } },
    };

    for (unsigned int i = 0; i < m_maxParticles; ++i)
    {
        if (m_lifetimes[i] <= 0)
            continue;

        auto& particle = m_particles[i];
        vertices[0].texCoords = { particle.UV.left, particle.UV.top };
        vertices[1].texCoords = { particle.UV.left, particle.UV.top + particle.UV.height };
        vertices[2].texCoords = { particle.UV.left + particle.UV.width, particle.UV.top + particle.UV.height };
        vertices[3].texCoords = { particle.UV.left + particle.UV.width, particle.UV.top };

        float delta = m_lifetimes[i] / particle.Lifetime;
        sf::Color color = Core::Math::Lerp(particle.StartColor, particle.EndColor, delta);

        // Quick fade-out over the last quarter second
        if (m_lifetimes[i] <= 0.25f)
            color.a *= m_lifetimes[i] * 4.f;

        vertices[0].color = color;
        vertices[1].color = color;
        vertices[2].color = color;
        vertices[3].color = color;

        sf::Transform baseScale;
        baseScale.scale(particle.UV.width, particle.UV.height);
        stateCopy.transform = states.transform * baseScale * particle.Transform;
        target.draw(vertices, 4, sf::TriangleStrip, stateCopy);
    }
}

