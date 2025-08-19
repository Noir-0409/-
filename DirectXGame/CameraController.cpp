#define NOMINMAX

#include "CameraController.h"
#include "Player.h"
#include "MathUtillity.h"
using namespace KamataEngine::MathUtility;

void CameraController::Initialize() {

	camera_->Initialize();

}

void CameraController::Update() {

	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	targetPosition_.x = targetWorldTransform.translation_.x + targetOffset_.x;
	targetPosition_.y = targetWorldTransform.translation_.y + targetOffset_.y;
	targetPosition_.z = targetWorldTransform.translation_.z + targetOffset_.z;

	camera_->translation_.x = Lerp(camera_->translation_.x, targetPosition_.x, kInterpolationRate_);
	camera_->translation_.y = Lerp(camera_->translation_.y, targetPosition_.y, kInterpolationRate_);

	camera_->translation_.x = std::max(camera_->translation_.x, movableArea_.left);
	camera_->translation_.x = std::min(camera_->translation_.x, movableArea_.right);
	camera_->translation_.y = std::max(camera_->translation_.y, movableArea_.bottom);
	camera_->translation_.y = std::min(camera_->translation_.y, movableArea_.top);

	camera_->UpdateMatrix();

}

void CameraController::Reset() {

	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	camera_->translation_.x = targetWorldTransform.translation_.x + targetOffset_.x;
	camera_->translation_.y = targetWorldTransform.translation_.y + targetOffset_.y;
	camera_->translation_.z = targetWorldTransform.translation_.z + targetOffset_.z;

}
