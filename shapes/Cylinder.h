#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"
#include <algorithm>
#include <vector>
#include <string>
#include <QImage>
#include <QGLWidget>

namespace CS123 { namespace GL {
class VAO;
}}

class Cylinder : public Shape
{
public:
    Cylinder();
    Cylinder(int param1, int param2);
    ~Cylinder();

    void setParams(int param1, int param2, float param3);

protected:
    std::vector<GLfloat> getFaceVertexData(int param1, int param2);

    glm::vec2 getCylinderTexture(const glm::vec4& point, int w, int h, float repeatU, float repeatV);

    void loadTextureImage();

    int m_param1;
    int m_param2;

    float m_repeatU = 2;
    float m_repeatV = 2;
};

#endif // CYLINDER_H
