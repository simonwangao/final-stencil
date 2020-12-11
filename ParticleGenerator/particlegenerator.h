#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include <glm.hpp>
#include <string>
#include "lib/ResourceLoader.h"
#include "gl/shaders/Shader.h"
#include "gl/openglshape.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include "gl/datatype/FBO.h"

class ParticleGenerator
{
public:
    ParticleGenerator();
    ParticleGenerator(glm::mat4 modelMat);

private:
    void loadParticleUpdateShader();
    void loadParticleDrawShader();
    void initializeParticleShaders();

    std::unique_ptr<CS123::GL::Shader> m_particleUpdateProgram;
    std::unique_ptr<CS123::GL::Shader> m_particleDrawProgram;

    std::unique_ptr<OpenGLShape> m_quad;
    GLuint m_particlesVAO;
    std::shared_ptr<FBO> m_particlesFBO1;
    std::shared_ptr<FBO> m_particlesFBO2;
    glm::mat4 m_modelMat;
    int m_numParticles;
    bool m_evenPass;
    bool m_firstPass;

};

#endif // PARTICLEGENERATOR_H
