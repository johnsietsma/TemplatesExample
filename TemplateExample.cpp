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

template<typename T>
vec3 calculate_color(T& object, float deltaTime)
{
    static const vec3 colorIncrement{ 0.1f, 0.1f, 0.1f };
    vec3 c = object.color + colorIncrement * deltaTime;
    if (c.x > 255) c = { 0,0,0 }; // Wrap the color around
    return c;
}


template<typename T>
void update_particles(T* particles, size_t particleCount, float deltaTime)
{
    for (size_t i = 0; i < particleCount; i++) {
        particles[i].position = calculate_position(particles[i], deltaTime);
    }
}

template<>
void update_particles<ParticleColored>(ParticleColored* particles, size_t particleCount, float deltaTime)
{
    for (size_t i = 0; i < particleCount; i++) {
        particles[i].position = calculate_position(particles[i], deltaTime);
        particles[i].color = calculate_color(particles[i], deltaTime);
    }
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

    constexpr const vec3 origin{ 0,0,0 };
    constexpr const vec3 right{ 1,0,0 };
    constexpr const vec3 green{ 1,0,0 };

    // Create and fill a Particle buffer
    Particle* pParticles = make_buffer<Particle,ParticleCount>(origin, right);
    // Update particles
    update_particles(pParticles, ParticleCount, TimeStep);

    // Create and fill a ParticleColored buffer
    ParticleColored* pParticlesColored = make_buffer<ParticleColored, ParticleCount>(origin, right, green);
    // Update colored particles
    update_particles(pParticlesColored, ParticleCount, TimeStep);

    // Cleanup
    delete pParticles;
    delete pParticlesColored;

    return 0;
}

