#pragma once 
#include <map>
#include <cmath>
#include <cfloat>

namespace coord {//tolua_export

class Vector3 {//tolua_export

public:
    Vector3();
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    void set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
    virtual ~Vector3();

    Vector3 operator -() const { Vector3 v; v.set(-x, -y, -z); return v; }

    /// Add a vector to this vector.
    void operator += (const Vector3& v){
        x += v.x; y += v.y; z += v.z;
    }

    /// Subtract a vector from this vector.
    void operator -= (const Vector3& v){
        x -= v.x; y -= v.y; z -= v.z;
    }

    void operator *= (float s){
        x *= s; y *= s; z *= s;
    }

    float length() const{
        return sqrt(x * x + y * y + z * z);
    }

    float length_squared() const{
        return x * x + y * y + z * z;
    }

    float normalize(){
        float length = this->length();
        if (length < FLT_EPSILON){
            return 0.0f;
        }
        float inv_length = 1.0f / length;
        x *= inv_length;
        y *= inv_length;
        return length;
    }
public:
    float x;//tolua_export
    float y;//tolua_export
    float z;//tolua_export

};//tolua_export

}//tolua_export
