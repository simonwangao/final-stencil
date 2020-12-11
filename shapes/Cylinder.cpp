#include "Cylinder.h"
#include "gl/datatype/VAO.h"
#include <iostream>

const float EPSILON = 1e-2;

inline bool equal(float a, float b) {
    return glm::abs(a - b) < EPSILON;
}

Cylinder::Cylinder() {
    m_param1 = 0;
    m_param2 = 0;
    loadTextureImage();
}

Cylinder::~Cylinder() {
}

Cylinder::Cylinder(int param1, int param2) :
    m_param1(param1),
    m_param2(param2)
{
    loadTextureImage();
    setParams(param1, param2, 0.f);
}

void Cylinder::setParams(int param1, int param2, float param3) {
    // m_param1 indicates the number of layers of triangles on the side surface
    // m_param2 indicates how many sectors in total
    // param3 is not needed for Cylinder

    // set the range of m_param1 to [1, 100]
    m_param1 = std::max(1, param1);
    m_param1 = std::min(100, param1);

    // set the range of m_param2 to [3, 100]
    m_param2 = std::max(3, param2);
    m_param2 = std::min(100, param2);

    m_vertexData.clear();

    // get the bottom circle of the Cylinder
    std::vector<GLfloat> bottomCircle = getCircleVertexData(true, m_param1, m_param2);
    m_vertexData.insert(m_vertexData.end(), bottomCircle.begin(), bottomCircle.end());

    // get the top circle of the Cylinder
    std::vector<GLfloat> topCircle = getCircleVertexData(false, m_param1, m_param2);
    m_vertexData.insert(m_vertexData.end(), topCircle.begin(), topCircle.end());

    // get the faces of the Cylinder
    std::vector<GLfloat> faces = getFaceVertexData(m_param1, m_param2);
    m_vertexData.insert(m_vertexData.end(), faces.begin(), faces.end());

    // add texture uv
    assert (m_vertexData.size() % 6 == 0);
    std::vector<GLfloat> tmp;
    for (size_t i = 0; i < m_vertexData.size(); i += 6) {
        for (int j = 0; j < 6; j++)
            tmp.push_back(m_vertexData[i + j]);
        glm::vec4 point = glm::vec4(m_vertexData[i], m_vertexData[i + 1], m_vertexData[i + 2], 1.);
        glm::vec2 uv = getCylinderTexture(point, m_image.width(), m_image.height(), m_repeatU, m_repeatV);
        tmp.push_back(uv[0]);
        tmp.push_back(uv[1]);
    }
    m_vertexData = tmp;

    buildVAO();
}

std::vector<GLfloat> Cylinder::getFaceVertexData(int param1, int param2) {
    // set the range of m_param1 to [1, 100]
    param1 = std::max(1, param1);
    param1 = std::min(100, param1);

    // set the range of m_param2 to [3, 100]
    param2 = std::max(3, param2);
    param2 = std::min(100, param2);

    float theta = 0.f;
    const float thetaDelta = 2.f * M_PI / param2;

    std::vector<GLfloat> result;
    std::vector<std::vector<GLfloat>> vertexCoordinatesVector;
    std::vector<glm::vec3> vectorNormal;

    for (int sector = 0; sector < param2; sector++) {
        float newTheta = theta + thetaDelta;
        // store the coordinates of the vertex, up to down, left to right
        std::vector<GLfloat> vertexCoordinates;
        float yDelta = 1.f / param1, y = -RADIUS;
        for (int i = 0; i <= param1; i++) {
            insertVec3(vertexCoordinates, glm::vec3(-sin(newTheta) * RADIUS, y, cos(newTheta) * RADIUS));
            insertVec3(vertexCoordinates, glm::vec3(-sin(theta) * RADIUS, y, cos(theta) * RADIUS));
            y += yDelta;
        }
        vertexCoordinatesVector.push_back(vertexCoordinates);

        // to get normal is a bit tricky
        glm::vec3 normal = getNormalVec(glm::vec3(vertexCoordinates[0], vertexCoordinates[1], vertexCoordinates[2]),
                glm::vec3(vertexCoordinates[3], vertexCoordinates[4], vertexCoordinates[5]),
                glm::vec3(vertexCoordinates[6], vertexCoordinates[7], vertexCoordinates[8]));
        vectorNormal.push_back(normal);

        theta += thetaDelta;
    }

    for (int sector = 0; sector < param2; sector++) {
        // calculate average normal
        glm::vec3 normal = vectorNormal[sector];
        glm::vec3 lNormal = vectorNormal[(sector + 1) % param2];
        glm::vec3 rNormal = vectorNormal[(sector + param2 - 1) % param2];

        // take the average of two surfaces' normals
        glm::vec3 lAverage = glm::normalize(normal + lNormal);
        glm::vec3 rAverage = glm::normalize(normal + rNormal);

        std::vector<GLfloat> vertexCoordinates = vertexCoordinatesVector[sector];
        for (int i = 0; i < 2 * param1; i += 2) {
            // upper left triangle
            insertVec3(result, glm::vec3(vertexCoordinates[3 * i], vertexCoordinates[3 * i + 1], vertexCoordinates[3 * i + 2]));
            insertVec3(result, lAverage);
            insertVec3(result, glm::vec3(vertexCoordinates[3 * i + 3], vertexCoordinates[3 * i + 4], vertexCoordinates[3 * i + 5]));
            insertVec3(result, rAverage);
            insertVec3(result, glm::vec3(vertexCoordinates[3 * i + 6], vertexCoordinates[3 * i + 7], vertexCoordinates[3 * i + 8]));
            insertVec3(result, lAverage);

            // lower right triangle
            insertVec3(result, glm::vec3(vertexCoordinates[3 * i + 3], vertexCoordinates[3 * i + 4], vertexCoordinates[3 * i + 5]));
            insertVec3(result, rAverage);
            insertVec3(result, glm::vec3(vertexCoordinates[3 * i + 9], vertexCoordinates[3 * i + 10], vertexCoordinates[3 * i + 11]));
            insertVec3(result, rAverage);
            insertVec3(result, glm::vec3(vertexCoordinates[3 * i + 6], vertexCoordinates[3 * i + 7], vertexCoordinates[3 * i + 8]));
            insertVec3(result, lAverage);
        }
    }

    return result;
}

glm::vec2 Cylinder::getCylinderTexture(const glm::vec4& point, int w, int h, float repeatU, float repeatV) {
    // point is at object space
    // find uv first
    glm::vec2 uv;

    // up
    if (equal(point[1], 0.5))
        uv = glm::vec2(point[0] + 0.5, point[2] + 0.5);
    // down
    else if (equal(point[1], -0.5))
        uv = glm::vec2(point[0] + 0.5, -point[2] + 0.5);
    else {
        // body
        uv[1] = -point[1] + 0.5;
        float theta = atan2(point[2], point[0]);
        if (theta < 0.)
            uv[0] = -theta / (2 * M_PI);
        else
            uv[0] = 1. - theta / (2 * M_PI);
    }
    uv[0] = uv[0] < 0. ? 0. : uv[0];
    uv[0] = uv[0] > 1. ? 1. : uv[0];
    uv[1] = uv[1] < 0. ? 0. : uv[1];
    uv[1] = uv[1] > 1. ? 1. : uv[1];
    return uv;
}

void Cylinder::loadTextureImage() {
    std::string path = ":/texture/images/cactus.jpg";
    m_image.load(QString(path.c_str()));
    //m_image = QGLWidget::convertToGLFormat(m_image);
}
