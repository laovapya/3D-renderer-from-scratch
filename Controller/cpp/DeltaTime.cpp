#include"DeltaTime.h"

DeltaTime::DeltaTime() {

}
float DeltaTime::GetDeltaTime() {
	return GetInstance().deltaTime;
}
void DeltaTime::SetDeltaTime(float currentFrame) {
    GetInstance().deltaTime = currentFrame - GetInstance().lastFrame;
    GetInstance().lastFrame = currentFrame;
}