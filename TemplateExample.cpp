#pragma warning(disable:4996) // Unsafe fill_n
#include <algorithm>
#pragma warning(default:4996)

// A simple Vector 3. For demo purposes only!
struct vec3
{
    float x, y, z;

    vec3 operator *(float val) const {
        return{ x*val, y*val, z*val };
    }

    vec3 operator +(const vec3& val) const {
        return{ x + val.x, y + val.y, z + val.z };
    }

    vec3 operator +=(const vec3& val) {
        vec3 newVal = *this + val;
        *this = val;
        return newVal;
    }
};

// A simple Particle.
struct Particle
{
    vec3 position;
    vec3 velocity;
};

struct ParticleColored
{
    vec3 position;
    vec3 velocity;
    vec3 color;
};


// Calculates the new position of a physics object at a given time step.
template<typename T>
vec3 calculate_position(const T& physicsObject, float timeStep)
{
    return physicsObject.velocity * timeStep;
}


int main()
{
    constexpr const size_t ParticleCount = 100; // How many particles we'll have
    constexpr const float TimeStep = 1/30.f;    // How much time passes for each update

    // Create and fill a Particle buffer
    Particle* pParticles = new Particle[ParticleCount];
    constexpr const Particle DefaultParticle { /*position*/{ 0,0,0 }, /*velocity*/{ 1,0,0 } };
    std::fill_n(pParticles, ParticleCount, DefaultParticle);

    // Create and fill a ParticleColored buffer
    ParticleColored* pParticlesColoured = new ParticleColored[ParticleCount];
    constexpr const ParticleColored DefaultParticleColored{ /*position*/{ 0,0,0 }, /*velocity*/{ 1,0,0 }, /*color*/{0,1,0} };
    std::fill_n(pParticlesColoured, ParticleCount, DefaultParticleColored);

    // Update the position of all the particles.
    for (size_t particleIndex = 0; particleIndex < ParticleCount; particleIndex++)
    {
        pParticles[particleIndex].position += calculate_position(pParticles[particleIndex], TimeStep);
        pParticlesColoured[particleIndex].position += calculate_position(pParticlesColoured[particleIndex], TimeStep);
    }

    delete pParticles;
    delete pParticlesColoured;

    return 0;
}

