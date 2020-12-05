/**
 * @file   CamtransCamera.cpp
 *
 * This is the perspective camera class you will need to fill in for the Camtrans lab.  See the
 * lab handout for more details.
 */

#include "CamtransCamera.h"
#include <Settings.h>

CamtransCamera::CamtransCamera()
{
    // @TODO: [CAMTRANS] Fill this in...
    m_near = 1.;
    m_far = 30.;
    m_thetaH = 60.;
    m_aspectRatio = 1.;
    m_eye = glm::vec4(2, 2, 2, 1);
    m_look = glm::vec4(-2, -2, -2, 0);
    m_up = glm::vec4(0, 1, 0, 0);
    orientLook(m_eye, m_look, m_up);
}

void CamtransCamera::setAspectRatio(float a)
{
    // @TODO: [CAMTRANS] Fill this in...
    m_aspectRatio = a;
    updateProjectionMatrix();

}

glm::mat4x4 CamtransCamera::getProjectionMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_perspectiveTransformation * m_scaleMatrix;
}

glm::mat4x4 CamtransCamera::getViewMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_rotationMatrix * m_translationMatrix;
}

glm::mat4x4 CamtransCamera::getScaleMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_scaleMatrix;
}

glm::mat4x4 CamtransCamera::getPerspectiveMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_perspectiveTransformation;
}

glm::vec4 CamtransCamera::getPosition() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_eye;
}

glm::vec4 CamtransCamera::getLook() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_look;
}

glm::vec4 CamtransCamera::getUp() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_up;
}

glm::vec4 CamtransCamera::getU() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_u;
}

glm::vec4 CamtransCamera::getV() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_v;
}

glm::vec4 CamtransCamera::getW() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_w;
}

float CamtransCamera::getAspectRatio() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_aspectRatio;
}

float CamtransCamera::getHeightAngle() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_thetaH;
}

void CamtransCamera::orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up) {
    // @TODO: [CAMTRANS] Fill this in...
    m_eye = eye;
    m_look = look;
    m_up = up;

    m_w = -glm::normalize(m_look);
    m_v = glm::normalize(m_up - (glm::dot(m_up, m_w) * m_w));
    m_u = glm::vec4(glm::cross(m_v.xyz(), m_w.xyz()), 0);

    updateViewMatrix();
    updateProjectionMatrix();

}

void CamtransCamera::setHeightAngle(float h) {
    // @TODO: [CAMTRANS] Fill this in...
    m_thetaH = h;
    float height = 2 * m_far * glm::tan(glm::radians(m_thetaH)/2.);
    float width = m_aspectRatio * (height);
    m_thetaW = glm::atan(width / (2 * m_far)) * 2;

    updateProjectionMatrix();

}

void CamtransCamera::translate(const glm::vec4 &v) {
    // @TODO: [CAMTRANS] Fill this in...
    m_eye = m_eye + v;
    updateViewMatrix();
}

void CamtransCamera::rotateU(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...

    float angle = glm::radians(degrees);
    glm::vec4 m_v_new = m_w * glm::sin(angle) + m_v * glm::cos(angle);
    glm::vec4 m_w_new = m_w * glm::cos(angle) - m_v * glm::sin(angle);

    m_v = m_v_new;
    m_w = m_w_new;

    updateViewMatrix();

}

void CamtransCamera::rotateV(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    float angle = glm::radians(degrees);
    glm::vec4 m_u_new = m_u * glm::cos(angle) - m_w * glm::sin(angle);
    glm::vec4 m_w_new = m_u * glm::sin(angle) + m_w * glm::cos(angle);

    m_u = m_u_new;
    m_w = m_w_new;

    updateViewMatrix();
}

void CamtransCamera::rotateW(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    float angle = glm::radians(degrees);
    glm::vec4 m_u_new = m_u * glm::cos(angle) - m_v * glm::sin(angle);
    glm::vec4 m_v_new = m_u * glm::sin(angle) + m_v * glm::cos(angle);

    m_u = m_u_new;
    m_v = m_v_new;

    updateViewMatrix();
}

void CamtransCamera::setClip(float nearPlane, float farPlane) {
    m_near = nearPlane;
    m_far = farPlane;

    updateProjectionMatrix();

}

void CamtransCamera::updateProjectionMatrix() {
    updateScaleMatrix();
    updatePerspectiveMatrix();

}
void CamtransCamera::updatePerspectiveMatrix() {
    float c = -m_near / m_far;
    m_perspectiveTransformation = glm::transpose(glm::mat4x4(1, 0, 0, 0,
                                              0, 1, 0, 0, 
                                              0, 0, -1./(c + 1.), c/(c + 1.),
                                              0, 0, -1, 0));

}
void CamtransCamera::updateScaleMatrix() {
    float y = 1./glm::tan(glm::radians(m_thetaH) / 2.);
    float x = y / m_aspectRatio;
    m_scaleMatrix = glm::transpose(glm::mat4x4(x/m_far, 0, 0, 0,
                                0, 1./glm::tan(glm::radians(m_thetaH) / 2.)/m_far, 0, 0,
                                0, 0, 1./m_far, 0,
                                0, 0, 0, 1));
}
void CamtransCamera::updateViewMatrix() {
    updateRotationMatrix();
    updateTranslationMatrix();

}
void CamtransCamera::updateRotationMatrix() {
    m_rotationMatrix = glm::transpose(glm::mat4x4(m_u.x, m_u.y, m_u.z, 0,
                                   m_v.x, m_v.y, m_v.z, 0,
                                   m_w.x, m_w.y, m_w.z, 0,
                                   0, 0, 0, 1));

}
void CamtransCamera::updateTranslationMatrix() {
    m_translationMatrix = glm::transpose(glm::mat4x4(1, 0, 0, -m_eye.x,
                                      0, 1, 0, -m_eye.y,
                                      0, 0, 1, -m_eye.z,
                                      0, 0, 0, 1));
}

