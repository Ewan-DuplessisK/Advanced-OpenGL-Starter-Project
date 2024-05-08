#pragma once
#include "Matrix4.h"
#include "Vector3.h"

class Object3D
{
protected:
    Vector3 m_position;
    Matrix4 m_rotation;
    Vector3 m_scale;
public:
    Object3D() = default;
    ~Object3D() = default;
    virtual void Generate()=0;
    virtual void Draw() = 0;
    Vector3 GetPosition(){return m_position;}
    void SetPosition(Vector3 position){m_position = position;}
    void Move(Vector3 translation){m_position += translation;}
    Matrix4 GetRotation(){return m_rotation;}
};
