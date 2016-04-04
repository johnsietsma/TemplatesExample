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


// Make and fill a buffer using the defaultObject.
template<typename T, int TCount, typename... TArgs>
T* make_buffer(TArgs... args)
{
    T* pBuffer = new T[TCount];
    std::fill_n(pBuffer, TCount, T{args...});
    return pBuffer;
}


int main()
{
    constexpr const size_t ParticleCount = 100; // How many particles we'll have
    constexpr const float TimeStep = 1/30.f;    // How much time passes for each update

    // Create and fill a Particle buffer
    Particle* pParticles = make_buffer<Particle,ParticleCount>(/*position*/vec3{ 0,0,0 }, /*velocity*/vec3{ 1,0,0 });

    // Create and fill a ParticleColored buffer
    ParticleColored* pParticlesColored = make_buffer<ParticleColored, ParticleCount>(/*position*/vec3{ 0,0,0 }, /*velocity*/vec3{ 1,0,0 }, /*color*/vec3{ 0,1,0 });

    // Update the position of all the particles.
    for (size_t particleIndex = 0; particleIndex < ParticleCount; particleIndex++)
    {
        pParticles[particleIndex].position += calculate_position(pParticles[particleIndex], TimeStep);
        pParticlesColored[particleIndex].position += calculate_position(pParticlesColored[particleIndex], TimeStep);
    }

    // Cleanup
    delete pParticles;
    delete pParticlesColored;

    return 0;
}

