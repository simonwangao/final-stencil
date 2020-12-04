#include "shapes/drawer.h"
#include "lib/ResourceLoader.h"
#include "glm/gtx/transform.hpp"
#include "L_System/Utils.h"

Drawer::Drawer() {
}

Drawer::~Drawer() {
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

void Drawer::draw(const std::vector<SegmentData>& segmentData) {
    // Set the color to set the screen when the color buffer is cleared.scale
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Creates the shader program that will be used for drawing.
    m_program = ResourceLoader::createShaderProgram(":/shaders/shader.vert", ":/shaders/shader.frag");

    // create the tessellation of the cylinder
    Cylinder cylinder = Cylinder();
    cylinder.setParams(PARAM1, PARAM2, 0);

    std::vector<GLfloat> objectSpaceData = cylinder.getVertexData();
    std::vector<GLfloat> result;

    for (SegmentData data : segmentData) {
        // already finished the rotation and translation,
        // need to do the scaling here
        // note that need to do the translation from center of the bottom circle
        // to the center of the cylinder
        glm::mat4 m(1.); // identity matrix
        // scaling
        float diameter = 1 * glm::pow(d, (float)data.depth);
        m = glm::scale(glm::vec3(diameter, diameter, data.length)) * m;
        m = glm::translate(glm::vec3(0., data.length / 2., 0.)) * m;
        m = data.matrix * m;

        // get world space vertex and normal data
        std::vector<GLfloat> worldSpaceData = vertexTimesMatrix(m, objectSpaceData);
        result.insert(result.end(), worldSpaceData.begin(), worldSpaceData.end());
    }


    // draw the world space sylinders, which is the tree
    m_shape = std::make_unique<OpenGLShape>();
    const int numFloatsPerVertex = 6;
    m_shape->setVertexData(&result[0], result.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, result.size() / numFloatsPerVertex);
    m_shape->setAttribute(0, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_shape->buildVAO();

    glEnable(GL_DEPTH_TEST);

    //

}
