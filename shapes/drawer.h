#ifndef DRAWER_H
#define DRAWER_H

#include "GL/glew.h"
#ifdef __APPLE__
#include <glu.h>
#else
#include "GL/glu.h"
#endif

#include <vector>
#include <glm.hpp>
#include <memory>
#include "shapes/Shape.h"
#include "shapes/Cylinder.h"
#include "gl/openglshape.h"
#include "L_System/turtle.h"

class Drawer {
public:
    Drawer();
    ~Drawer();

    void draw(const std::vector<SegmentData>& data);

protected:
    /** ID for the shader program. */
    GLuint m_program;
    std::unique_ptr<OpenGLShape> m_shape;

    static std::vector<GLfloat> vertexTimesMatrix(const glm::mat4& matrix, const std::vector<GLfloat>& vertexData);

};

#endif // DRAWER_H
