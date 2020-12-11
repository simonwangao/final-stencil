#include "particlegenerator.h"
#include <iostream>

ParticleGenerator::ParticleGenerator()
{

}

ParticleGenerator::ParticleGenerator(glm::mat4 modelMat) :
    m_modelMat(modelMat), m_numParticles(500), m_evenPass(true), m_firstPass(true),
    m_particlesFBO1(nullptr), m_particlesFBO2(nullptr)
{
    loadParticleUpdateShader();
    loadParticleDrawShader();
    initializeParticleShaders();
}

void ParticleGenerator::loadParticleUpdateShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/quad.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/particles_update.frag");
    m_particleUpdateProgram = std::make_unique<CS123::GL::Shader>(vertexSource, fragmentSource);
}

void ParticleGenerator::loadParticleDrawShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/particles_draw.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/particles_draw.frag");
    m_particleDrawProgram = std::make_unique<CS123::GL::Shader>(vertexSource, fragmentSource);
}

void ParticleGenerator::initializeParticleShaders() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    std::vector<GLfloat> quadData;
    quadData = {-1, 1, 0, 0, 1, \
                -1, -1, 0, 0, 0, \
                 1, 1, 0, 1, 1, \
                 1, -1, 0, 1, 0};
    m_quad = std::make_unique<OpenGLShape>();
    m_quad->setVertexData(&quadData[0], quadData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, 4);
    m_quad->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->setAttribute(ShaderAttrib::TEXCOORD0, 2, 3*sizeof(GLfloat), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->buildVAO();

    glGenVertexArrays(1, &m_particlesVAO);

    m_particlesFBO1 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, \
                                            TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    m_particlesFBO2 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, \
                                            TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);

    GLint maxRenderBufferSize;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &maxRenderBufferSize);
    std::cout << "Max FBO size: " << maxRenderBufferSize << std::endl;
}
