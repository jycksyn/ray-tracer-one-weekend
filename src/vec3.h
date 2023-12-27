#ifndef RAY_TRACER_ONE_WEEKEND_VECH
#define RAY_TRACER_ONE_WEEKEND_VECH

#include<vector>
#include <cmath>
#include <cstdlib>
#include <iostream>

class vec3 {
  public:
    vec3 () = default;
    vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
    
    [[nodiscard]] inline float x() const { return e[0]; }
    [[nodiscard]] inline float y() const { return e[1]; }
    [[nodiscard]]  inline float z() const { return e[2]; }

    [[nodiscard]] inline float r() const { return e[0]; }
    [[nodiscard]] inline float g() const { return e[1]; }
    [[nodiscard]] inline float b() const { return e[2]; }
    
    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return {-e[0], -e[1], -e[2]}; }
    inline float operator[](int i) const { return e[i]; }
    
    inline vec3& operator+=(const vec3 &v2);
    inline vec3& operator-=(const vec3 &v2);
    inline vec3& operator*=(const vec3 &v2);
    inline vec3& operator/=(const vec3 &v2);
    inline vec3& operator*=(float t);
    inline vec3& operator/=(float k);

    [[nodiscard]] inline float length() const {
      return std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }

    [[nodiscard]] inline float squared_length() const {
      return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    
    inline void make_unit_vector() {
      float k = 1.0f / this->length();
      e[0] *= k; e[1] *= k; e[2] *=k;
    }
    
    float e[3] {};
};

inline std::istream& operator>>(std::istream &is, vec3 &t) {
  is >> t.e[0] >> t.e[1] >> t.e[2];
  return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &t) {
  os << t.e[0] << " " << t.e[1] << " " << t.e[2];
  return os;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
  return {v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]};
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
  return {v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]};
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
  return {v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]};
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]};
}

inline vec3 operator*(float t, const vec3 &v1) {
    return {t * v1.e[0], t * v1.e[1], t * v1.e[2]};
}

inline vec3 operator*(const vec3 &v1, float t) {
    return {t * v1.e[0], t * v1.e[1], t * v1.e[2]};
}

inline vec3 operator/(const vec3 &v1, float t) {
    return {v1.e[0] / t, v1.e[1] / t, v1.e[2] / t};
}

inline float dot(const vec3 &v1, const vec3 &v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return {
            v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
            -v1.e[0] * v2.e[2] + v1.e[2] * v2.e[0],
            v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]
            };
}

inline vec3& vec3::operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const vec3 &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline vec3& vec3::operator/=(const vec3 &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline vec3& vec3::operator-=(const vec3 &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline vec3& vec3::operator/=(const float k) {
    float t = 1.0f/k;

    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

vec3 random_in_unit_sphere() {
    vec3 random(
            static_cast<float>(drand48()),
            static_cast<float>(drand48()),
            static_cast<float>(drand48())
            );
    random *= 2;
    random += vec3(-1, -1, -1);
    random.make_unit_vector();
    random *= static_cast<float>(drand48());
    return random;
}

vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2*dot(v, n)*n;
}

bool refract(const vec3 &v, const vec3 &n, float index, vec3 &refracted) {
    vec3 u = unit_vector(v);
    float c = dot(u, n);
    float discriminant = 1 - index*index*(1 - c*c);
    if (discriminant > 0) {
        refracted = index*(u - c*n) - sqrt(discriminant) * n;
        return true;
    }
    return false;
}

#endif

