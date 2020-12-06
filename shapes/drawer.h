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
#include "camera/Camera.h"
#include "scenegraph/OpenGLScene.h"
#include "shapes/Shape.h"
#include "shapes/Cylinder.h"
#include "gl/shaders/CS123Shader.h"
#include "gl/openglshape.h"
#include "L_System/turtle.h"
#include "ui/SupportCanvas3D.h"

namespace CS123 { namespace GL {

    class Shader;
    class CS123Shader;
}}

class SupportCanvas3D;

class Drawer : public OpenGLScene {
public:
    Drawer();
    ~Drawer();

    void render(SupportCanvas3D *context, const std::vector<SegmentData>& data);
    void draw(const std::vector<SegmentData>& data);

protected:
    /** ID for the shader program. */
    GLuint m_program;
    std::unique_ptr<OpenGLShape> m_shape;
    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    int m_shapeParameter1;
    int m_shapeParameter2;

    static std::vector<GLfloat> vertexTimesMatrix(const glm::mat4& matrix, const std::vector<GLfloat>& vertexData);
    void loadPhongShader();
    void setSceneUniforms(SupportCanvas3D *context);
    void setLights();

};

#endif // DRAWER_H
