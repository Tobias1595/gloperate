#include <glm/gtc/matrix_transform.hpp>

glm::mat4 orthographicFromPerspective(float fovy, float aspectRatio, float zNear, float zFar, float syncDist)
{
    //compute ortho params from fovy and aspect assuming symmetry
    float right = zNear*glm::tan(fovy/2.0);
    float top = right / aspectRatio;
    float left = -right;
    float bottom = -top;

    float c = syncDist / zNear;
    return glm::ortho(c*left, c*right, c*bottom, c*top, zNear, zFar);
}

glm::mat4 perspectiveFromOrthographic(float left, float right, float bottom, float top, float zNear, float zFar, float syncDist)
{
    float fovy = glm::atan(right / zNear) * 2; //assuming right = -left and bottom = -top
    float aspectRatio = (2 * right) / (2 * top);

    float c = zNear / syncDist;
    return glm::perspective(fovy, aspectRatio, zNear, zFar);


}
