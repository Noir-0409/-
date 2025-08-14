#define NOMINMAX

#include "Player.h"
#include <algorithm>
#include <numbers>
#include "MathUtillity.h"

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

//void Player::Update() {
//
//	if (onGround_) {
//
//		if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)) {
//
//			Vector3 acceleration = {};
//
//			if (Input::GetInstance()->PushKey(DIK_D)) {
//
//				if (lrDirection_ != LRDirection::kRight) {
//
//					lrDirection_ = LRDirection::kRight;
//
//					turnFirstRotationY_ = worldTransform_.rotation_.y;
//
//					turnTimer_ = kTimeTurn;
//				}
//
//				if (velocity_.x < 0.0f) {
//
//					velocity_.x *= (1.0f - kAcceleration);
//				}
//
//				acceleration.x += kAcceleration;
//
//			} else if (Input::GetInstance()->PushKey(DIK_A)) {
//
//				if (lrDirection_ != LRDirection::kLeft) {
//
//					lrDirection_ = LRDirection::kLeft;
//
//					turnFirstRotationY_ = worldTransform_.rotation_.y;
//
//					turnTimer_ = kTimeTurn;
//				}
//
//				if (velocity_.x > 0.0f) {
//
//					velocity_.x *= (1.0f - kAcceleration);
//				}
//
//				acceleration.x -= kAcceleration;
//			}
//
//			velocity_.x += acceleration.x;
//
//			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
//
//		} else {
//
//			velocity_.x *= (1.0f - kAcceleration);
//		}
//
//		if (turnTimer_ > 0.0f) {
//
//			// 旋回タイマーをカウントダウン
//			turnTimer_ -= 1.0f / 60.0f;
//
//			float destinationRotationYTable[] = {
//
//			    std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f
//
//			};
//
//			float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
//
//			worldTransform_.rotation_.y = destinationRotationY;
//
//			float t = 1.0f - (turnTimer_ / kTimeTurn);
//
//			worldTransform_.rotation_.y = std::lerp(turnFirstRotationY_, destinationRotationY, t);
//	
//		}
//	
//	} else {
//	
//		velocity_.y -= kGravityAcceleration;
//		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
//	}
//
//	if (Input::GetInstance()->PushKey(DIK_W)) {
//	
//	velocity_.y += kJumpAcceleration;
//	
//	}
//
//	bool landing = false;
//
//	if (velocity_.y < 0) {
//	
//	if (worldTransform_.translation_.y <= 1.0f) {
//	
//		landing = true;
//	
//	}
//	
//	}
//
//	if (onGround_) {
//	
//		if (velocity_.y > 0.0f) {
//		
//			onGround_ = false;
//		
//		}
//	
//	} else {
//	
//		if (landing) {
//		
//			worldTransform_.translation_.y = 1.0f;
//
//			velocity_.x *= (1.0f - kAttenuation);
//
//			velocity_.y = 0.0f;
//
//			onGround_ = true;
//		
//		}
//	
//	}
//
//	worldTransform_.translation_.x += velocity_.x;
//	worldTransform_.translation_.y += velocity_.y;
//
//	worldTransform_.TransferMatrix();
//	worldTransform_.UpdateMatrix();
//}

void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	// 移動入力

	// 接地状態
	if (onGround_) {

		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)) {

			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_D)) {

				// 左移動中の右入力
				if (velocity_.x < 0.0f) {

					// 速度と逆方向に入力中はブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x += kAcceleration;

				if (lrDirection_ != LRDirection::kRight) {

					lrDirection_ = LRDirection::kRight;

					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマーに時間を設定
					turnTimer_ = kTimeTurn;
				}

			} else if (Input::GetInstance()->PushKey(DIK_A)) {

				// 右移動中の左入力
				if (velocity_.x > 0.0f) {

					// 速度と逆方向に入力中はブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x -= kAcceleration;

				if (lrDirection_ != LRDirection::kLeft) {

					lrDirection_ = LRDirection::kLeft;

					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマーに時間を設定
					turnTimer_ = kTimeTurn;
				}
			}

			// 加速、減速
			velocity_ += acceleration;

			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		} else {

			// 非入力時は減衰
			velocity_.x *= (1.0f - kAcceleration);
		}

		// 旋回制御
		if (turnTimer_ > 0.0f) {

			// 旋回タイマーをカウントダウン
			turnTimer_ -= 1.0f / 60.0f;

			// 左右の自キャラの角度テーブル
			float destinationRotationYTable[] = {

			    std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f

			};

			// 状態に応じた角度を取得
			float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

			// 自キャラの角度を設定
			worldTransform_.rotation_.y = destinationRotationY;

			float t = 1.0f - (turnTimer_ / kTimeTurn);

			worldTransform_.rotation_.y = std::lerp(turnFirstRotationY_, destinationRotationY, t);

		} else {

			float destinationRotationYTable[] = {

			    std::numbers::pi_v<float> / 2.0f,       // 右方向
			    std::numbers::pi_v<float> * 3.0f / 2.0f // 左方向

			};

			float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

			worldTransform_.rotation_.y = destinationRotationY;
		}

		// 移動
		worldTransform_.translation_ += velocity_;

		if (Input::GetInstance()->PushKey(DIK_W)) {

			// ジャンプ初速
			velocity_ += Vector3(0, kJumpAcceleration, 0);
		}

		// ジャンプ開始
		if (velocity_.y > 0.0f) {

			onGround_ = false;
		}

		// 空中
	} else {

		// 落下速度
		velocity_ += Vector3(0, -kGravityAcceleration, 0);

		worldTransform_.translation_ += Vector3(velocity_);

		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

		// 着地フラグ
		bool landing = false;

		// 地面との当たり判定
		// 下降中
		if (velocity_.y < 0) {

			// Y座標が地面以下になったら着地
			if (worldTransform_.translation_.y <= 1.0f) {

				landing = true;
			}
		}

		// 着地
		if (landing) {

			// めり込み排除
			worldTransform_.translation_.y = 1.0f;

			// 摩擦で横方向速度が減衰
			velocity_.x *= (1.0f - kAttenuation);

			// 下方向速度をリセット
			velocity_.y = 0.0f;

			// 接地状態に移行
			onGround_ = true;
		}
	}

	// 行列計算
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Player::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }
