#include "shapes/drawer.h"
#include "lib/ResourceLoader.h"
#include "glm/gtx/transform.hpp"

using namespace CS123::GL;

Drawer::Drawer() {

    loadPhongShader();
    createLights();

    // setting up global data
    m_global_data.ka = 0.5;
    m_global_data.kd = 0.5;
    m_global_data.ks = 0.5;

    // change later
    setData(std::vector<SegmentData>());
}


Drawer::~Drawer() {
}

void Drawer::setData(const std::vector<SegmentData>& data) {
    //m_data = data;

    Turtle turtle;
    vector<pair<string, float>> v;
    v.push_back(std::make_pair(F, 1.));
    v.push_back(std::make_pair(left, 30.));
    v.push_back(std::make_pair(F, .5));

    turtle.parse(v);

    m_data = turtle.getSegmentData();
}

void Drawer::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void Drawer::createLights() {
    m_light_data = {};

    CS123SceneLightData ptLight1;
    ptLight1.id = 0;
    ptLight1.pos = glm::vec4(3, 3, 3, 1);

    // these two are not used yet but we can use if we implement phong's on our own ... not the sceneview way
    ptLight1.color = glm::vec4(1, 1, 1, 1);
    ptLight1.function = glm::vec3();

    m_light_data.push_back(ptLight1);

}

std::vector<GLfloat> Drawer::vertexTimesMatrix(const glm::mat4& matrix, const std::vector<GLfloat>& vertexData) {
    // first three is location, last three is normal
    assert(vertexData.size() %6 == 0);

    std::vector<GLfloat> result;
    for (size_t i = 0; i < vertexData.size(); i += 6) {
        // get world space location
        glm::vec4 loc = glm::vec4(vertexData[i], vertexData[i + 1], vertexData[i + 2], 1.);
        loc = matrix * loc;
        insertVec3(result, loc.xyz());

        // get world-space normal
        glm::vec3 normal = glm::vec3(vertexData[i + 3], vertexData[i + 4], vertexData[i + 5]);
        glm::mat3 m = glm::mat3(matrix); // extract the 3x3 matrix
        normal = glm::transpose(glm::inverse(m)) * normal; // no need to translate ?
        insertVec3(result, glm::normalize(normal));

        // texture mapping (if any)
    }

    return result;
}

void Drawer::render(SupportCanvas3D *context) {
    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_phongShader->bind();
    setSceneUniforms(context);
    setLights();
    draw(m_data); // prime function here
    glBindTexture(GL_TEXTURE_2D, 0);
    m_phongShader->unbind();
}

void Drawer::setSceneUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    m_phongShader->setUniform("useLighting", true);
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getViewMatrix());
}

void Drawer::setLights()
{
    for (auto light : this->m_light_data)
        m_phongShader->setLight(light);
}

void Drawer::draw(const std::vector<SegmentData>& segmentData) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // create the tessellation of the cylinder
    std::unique_ptr<Shape> shapePtr = std::make_unique<Cylinder>(PARAM1, PARAM2);

    for (SegmentData data : segmentData) {
        // already finished the rotation and translation,
        // need to do the scaling here
        // note that need to do the translation from center of the bottom circle
        // to the center of the cylinder
        glm::mat4 mat(1.); // identity matrix
        // scaling
        float diameter = START_DIAMETER * glm::pow(d, (float)data.depth);
        mat = glm::scale(glm::vec3(diameter, data.length, diameter)) * mat;
        mat = glm::translate(glm::vec3(0., data.length / 2., 0.)) * mat; // move "to the ground" (y >= 0)
        mat = data.matrix * mat;

        // set up the material here ?
        CS123SceneMaterial material;


        material.cAmbient = glm::vec4(0.3, 0.3, 0.2, 1.);
        material.cDiffuse = glm::vec4(1., 1., 1., 1.);
        material.cSpecular = glm::vec4(0., 0., 0., 1.);
        material.cAmbient *= m_global_data.ka;
        material.cDiffuse *= m_global_data.kd;


        m_phongShader->applyMaterial(material);

        // set as model matrix (transforming on GPU)
        m_phongShader->setUniform("m", mat);

        shapePtr->draw();
    }

    return ;
}
