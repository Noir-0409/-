#include "Player.h"
#include <algorithm>
#include <numbers>

using namespace KamataEngine;

Player::~Player() {}

void Player::Initialize(Model* model, Camera* camera, const Vector3& position) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	camera;

	worldTransform_.rotation_.y = 3.14159f / 2.0f;

	input_ = Input::GetInstance();
}

void Player::Update() {

	if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)) {

		Vector3 acceleration = {};

		if (Input::GetInstance()->PushKey(DIK_D)) {

			if (lrDirection_ != LRDirection::kRight) {

				lrDirection_ = LRDirection::kRight;

				turnFirstRotationY_ = worldTransform_.rotation_.y;

				turnTimer_ = kTimeTurn;
			}

			if (velocity_.x < 0.0f) {

				velocity_.x *= (1.0f - kAcceleration);
			}

			acceleration.x += kAcceleration;

		} else if (Input::GetInstance()->PushKey(DIK_A)) {

			if (lrDirection_ != LRDirection::kLeft) {

				lrDirection_ = LRDirection::kLeft;

				turnFirstRotationY_ = worldTransform_.rotation_.y;

				turnTimer_ = kTimeTurn;
			}

			if (velocity_.x > 0.0f) {

				velocity_.x *= (1.0f - kAcceleration);
			}

			acceleration.x -= kAcceleration;
		}

		velocity_.x += acceleration.x;

		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

	} else {

		velocity_.x *= (1.0f - kAcceleration);
	}

	if (turnTimer_ > 0.0f) {

		// 旋回タイマーをカウントダウン
		turnTimer_ -= 1.0f / 60.0f;

		float destinationRotationYTable[] = {

		    std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f

		};

		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		worldTransform_.rotation_.y = destinationRotationY;

		float t = 1.0f - (turnTimer_ / kTimeTurn);

		worldTransform_.rotation_.y = std::lerp(turnFirstRotationY_, destinationRotationY, t);
	
	}

	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;

	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();
}

void Player::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }
