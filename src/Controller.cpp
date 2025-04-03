#include "Controller.h"
#include"DeltaTime.h"
#include<iostream>> //remove
Controller::Controller() {

}

void Controller::SwitchState(GLFWwindow* window, int key, int scancode, int action, int mods) {

    Controller& instance = Controller::GetInstance();
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_X && action == GLFW_PRESS)
        instance.isXaxisEnabled = !instance.isXaxisEnabled;
    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
        instance.isYaxisEnabled = !instance.isYaxisEnabled;
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        instance.isZaxisEnabled = !instance.isZaxisEnabled;

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        instance.isScaling = !instance.isScaling;
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        instance.isRotating = !instance.isRotating;
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
        instance.isTranslating = !instance.isTranslating;


    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        instance.isXaxisEnabled = false;
        instance.isYaxisEnabled = false;
        instance.isZaxisEnabled = false;

        instance.isTranslating = false;
        instance.isScaling = false;
        instance.isRotating = false;
    }


}
void Controller::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Controller& instance = Controller::GetInstance();
    instance.mouseXoffset = xpos - instance.mouseLastX;
    instance.mouseYoffset = instance.mouseLastY - ypos; // reversed since y-coordinates range from bottom to top
    instance.mouseLastX = xpos;
    instance.mouseLastY = ypos;

    instance.mouseXoffset *= instance.mouseSensitivity;
    instance.mouseYoffset *= instance.mouseSensitivity;

}





bool Controller::GetScaling() {
    return GetInstance().isScaling;
}
bool Controller::GetRotating() {
    return GetInstance().isRotating;
}
bool Controller::GetTranslating() {
    return GetInstance().isTranslating;
}

glm::vec3 Controller::GetTransformVector(Camera* currentCamera) {
    glm::vec3 v(0, 0, 0);
    Controller& instance = Controller::GetInstance();

    glm::vec3 mouseVector = currentCamera->GetRight() * instance.mouseXoffset + currentCamera->GetUp() * instance.mouseYoffset;
    if (instance.isXaxisEnabled)
        v += mouseVector.x * glm::vec3(1, 0, 0);

    if (instance.isYaxisEnabled)
        v += mouseVector.y * glm::vec3(0, 1, 0);

    if (instance.isZaxisEnabled)
        v += mouseVector.z * glm::vec3(0, 0, 1);

    return v * -1.0f * instance.panSpeed;
}

void Controller::MoveCamera(GLFWwindow* window, Camera* currentCamera) {
    Controller& instance = Controller::GetInstance();

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        currentCamera->Pan(glm::vec3(instance.mouseXoffset, instance.mouseYoffset, 0) * DeltaTime::GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
        currentCamera->Pan(glm::vec3(0, 0, 1) * instance.panSpeed * DeltaTime::GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
        currentCamera->Pan(glm::vec3(0, 0, -1) * instance.panSpeed * DeltaTime::GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        currentCamera->Orbit(-glm::vec3(instance.mouseYoffset, instance.mouseXoffset, 0) * DeltaTime::GetDeltaTime());
    }
}


void Controller::ResetMouse() {
    Controller& instance = GetInstance();

    instance.mouseXoffset = 0;
    instance.mouseYoffset = 0;
}

// float* Controller::GetActiveColor(){
//     return activeColor;
// }

