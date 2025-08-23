#define NOMINMAX

#include "Player.h"
#include "MapChipField.h"
#include "MathUtillity.h"
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

//void Player::Update() {
//
//	// 行列を定数バッファに転送
//	worldTransform_.TransferMatrix();
//
//	InputMove();
//
//	CollisionMapInfo collisionMapInfo;
//
//	collisionMapInfo.move = velocity_;
//
//	CheckMapCollision(collisionMapInfo);
//
//	UpdateOnGround(collisionMapInfo);
//
//	// 行列計算
//	worldTransform_.UpdateMatrix();
//	worldTransform_.TransferMatrix();
//}

void Player::Update() {

	worldTransform_.TransferMatrix();

	InputMove(); // velocity_ 計算

	CollisionMapInfo collisionMapInfo;
	collisionMapInfo.move = velocity_;

	CheckMapCollision(collisionMapInfo); // move を補正
	CollisionMove(collisionMapInfo);     // 実際に位置を更新
	UpdateOnGround(collisionMapInfo);    // onGround 更新

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}


void Player::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }

//void Player::InputMove() {
//
//	// 移動入力
//
//	// 接地状態
//	if (onGround_) {
//
//		// 左右移動操作
//		if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)) {
//
//			// 左右加速
//			Vector3 acceleration = {};
//			if (Input::GetInstance()->PushKey(DIK_D)) {
//
//				// 左移動中の右入力
//				if (velocity_.x < 0.0f) {
//
//					// 速度と逆方向に入力中はブレーキ
//					velocity_.x *= (1.0f - kAttenuation);
//				}
//
//				acceleration.x += kAcceleration;
//
//				if (lrDirection_ != LRDirection::kRight) {
//
//					lrDirection_ = LRDirection::kRight;
//
//					// 旋回開始時の角度を記録
//					turnFirstRotationY_ = worldTransform_.rotation_.y;
//
//					// 旋回タイマーに時間を設定
//					turnTimer_ = kTimeTurn;
//				}
//
//			} else if (Input::GetInstance()->PushKey(DIK_A)) {
//
//				// 右移動中の左入力
//				if (velocity_.x > 0.0f) {
//
//					// 速度と逆方向に入力中はブレーキ
//					velocity_.x *= (1.0f - kAttenuation);
//				}
//
//				acceleration.x -= kAcceleration;
//
//				if (lrDirection_ != LRDirection::kLeft) {
//
//					lrDirection_ = LRDirection::kLeft;
//
//					// 旋回開始時の角度を記録
//					turnFirstRotationY_ = worldTransform_.rotation_.y;
//
//					// 旋回タイマーに時間を設定
//					turnTimer_ = kTimeTurn;
//				}
//			}
//
//			// 加速、減速
//			velocity_ += acceleration;
//
//			// 最大速度制限
//			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
//
//		} else {
//
//			// 非入力時は減衰
//			velocity_.x *= (1.0f - kAcceleration);
//		}
//
//		// 旋回制御
//		if (turnTimer_ > 0.0f) {
//
//			// 旋回タイマーをカウントダウン
//			turnTimer_ -= 1.0f / 60.0f;
//
//			// 左右の自キャラの角度テーブル
//			float destinationRotationYTable[] = {
//
//			    std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f
//
//			};
//
//			// 状態に応じた角度を取得
//			float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
//
//			// 自キャラの角度を設定
//			worldTransform_.rotation_.y = destinationRotationY;
//
//			float t = 1.0f - (turnTimer_ / kTimeTurn);
//
//			worldTransform_.rotation_.y = std::lerp(turnFirstRotationY_, destinationRotationY, t);
//
//		} else {
//
//			float destinationRotationYTable[] = {
//
//			    std::numbers::pi_v<float> / 2.0f,       // 右方向
//			    std::numbers::pi_v<float> * 3.0f / 2.0f // 左方向
//
//			};
//
//			float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
//
//			worldTransform_.rotation_.y = destinationRotationY;
//		}
//
//		// 移動
//		worldTransform_.translation_ += velocity_;
//
//		if (Input::GetInstance()->PushKey(DIK_W)) {
//
//			// ジャンプ初速
//			velocity_ += Vector3(0, kJumpAcceleration, 0);
//		}
//
//		// ジャンプ開始
//		if (velocity_.y > 0.0f) {
//
//			onGround_ = false;
//		}
//
//		// 空中
//	} else {
//
//		// 落下速度
//		velocity_ += Vector3(0, -kGravityAcceleration, 0);
//
//		worldTransform_.translation_ += Vector3(velocity_);
//
//		// 落下速度制限
//		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
//
//		// 着地フラグ
//		bool landing = false;
//
//		// 地面との当たり判定
//		// 下降中
//		if (velocity_.y < 0) {
//
//			// Y座標が地面以下になったら着地
//			if (worldTransform_.translation_.y <= 1.0f) {
//
//				landing = true;
//			}
//		}
//
//		// 着地
//		if (landing) {
//
//			// めり込み排除
//			worldTransform_.translation_.y = 1.0f;
//
//			// 摩擦で横方向速度が減衰
//			velocity_.x *= (1.0f - kAttenuation);
//
//			// 下方向速度をリセット
//			velocity_.y = 0.0f;
//
//			// 接地状態に移行
//			onGround_ = true;
//		}
//	}
//}

void Player::InputMove() {

	// 接地状態
	if (onGround_) {
		Vector3 acceleration{};
		if (Input::GetInstance()->PushKey(DIK_D)) {
			if (velocity_.x < 0.0f)
				velocity_.x *= (1.0f - kAttenuation);
			acceleration.x += kAcceleration;
			lrDirection_ = LRDirection::kRight;
		} else if (Input::GetInstance()->PushKey(DIK_A)) {
			if (velocity_.x > 0.0f)
				velocity_.x *= (1.0f - kAttenuation);
			acceleration.x -= kAcceleration;
			lrDirection_ = LRDirection::kLeft;
		} else {
			velocity_.x *= (1.0f - kAttenuation);
		}

		velocity_ += acceleration;
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		// ジャンプ
		if (Input::GetInstance()->PushKey(DIK_W)) {
			velocity_.y = kJumpAcceleration;
			onGround_ = false;
		}

	} else {
		// 空中では重力加算
		velocity_.y -= kGravityAcceleration;
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	// 移動は CollisionMove で行う
}


void Player::CollisionMove(const CollisionMapInfo& info) { worldTransform_.translation_ += info.move; }

void Player::CheckMapCollision(CollisionMapInfo& info) {
	CheckMapCollisionUp(info);
	CheckMapCollisionDown(info);
}

void Player::CheckMapCollisionUp(CollisionMapInfo& info) {

	if (info.move.y <= 0) {

		return;
	}

	std::array<Vector3, kNumCorner> positionsNew;

	// 移動後の中心座標を計算
	Vector3 center;
	center.x = worldTransform_.translation_.x + info.move.x;
	center.y = worldTransform_.translation_.y + info.move.y;
	center.z = worldTransform_.translation_.z + info.move.z;

	// 各コーナーの位置を計算
	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(center, static_cast<Corner>(i));
	}

	MapChipType mapChipType;

	bool hit = false;

	MapChipField::IndexSet indexSet;

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {

		hit = true;
	}

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {

		hit = true;
	}

	if (hit) {

		// indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_.y + (kHeight / 2.0f));
		Vector3 pos = worldTransform_.translation_;
		pos.y += kHeight / 2.0f;
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(pos);

		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);

		info.move.y = std::max(0.0f, rect.bottom - worldTransform_.translation_.y - (kHeight / 2.0f + kBlank));

		info.ceiling = true;
	}

	if (info.ceiling) {

		DebugText::GetInstance()->ConsolePrintf("hit\n");

		velocity_.y = 0;
	}
}

//void Player::CheckMapCollisionDown(CollisionMapInfo& info) {
//
//	if (info.move.y >= 0) {
//
//		return;
//	}
//
//	std::array<Vector3, kNumCorner> positionsNew;
//
//	// 移動後の中心座標を計算
//	Vector3 center;
//	center.x = worldTransform_.translation_.x + info.move.x;
//	center.y = worldTransform_.translation_.y + info.move.y;
//	center.z = worldTransform_.translation_.z + info.move.z;
//
//	// 各コーナーの位置を計算
//	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
//		positionsNew[i] = CornerPosition(center, static_cast<Corner>(i));
//	}
//
//	MapChipType mapChipType;
//
//	bool hit = false;
//
//	MapChipField::IndexSet indexSet;
//
//	/*indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom] + Vector3(0, -kGroundSearchHeight, 0));*/
//	Vector3 checkPosL = positionsNew[kLeftBottom];
//	checkPosL.y -= kGroundSearchHeight;
//	indexSet = mapChipField_->GetMapChipIndexSetByPosition(checkPosL);
//
//	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
//
//	if (mapChipType == MapChipType::kBlock) {
//
//		hit = true;
//	}
//
//	//indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom] + Vector3(0, -kGroundSearchHeight, 0));
//	Vector3 checkPosR = positionsNew[kRightBottom];
//	checkPosR.y -= kGroundSearchHeight;
//	indexSet = mapChipField_->GetMapChipIndexSetByPosition(checkPosR);
//	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
//
//	if (mapChipType == MapChipType::kBlock) {
//
//		hit = true;
//	}
//
//	if (hit) {
//
//		// プレイヤー下端の位置を計算
//		Vector3 pos = worldTransform_.translation_;
//		pos.y -= kHeight / 2.0f; // 下端に調整
//
//		// 衝突しているマップチップのインデックス取得
//		indexSet = mapChipField_->GetMapChipIndexSetByPosition(pos);
//
//		// マップチップの矩形を取得
//		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
//
//		// 移動量をブロック上に補正
//		info.move.y = std::min(0.0f, rect.top - worldTransform_.translation_.y + (kHeight / 2.0f + kBlank));
//
//		// 床に当たったフラグ
//		info.landing = true;
//	}
//}

void Player::CheckMapCollisionDown(CollisionMapInfo& info) {

	if (info.move.y >= 0.0f)
		return; // 上方向なら無視

	std::array<Vector3, kNumCorner> positionsNew;

	// 移動後の中心座標
	Vector3 center;
	center.x = worldTransform_.translation_.x + info.move.x;
	center.y = worldTransform_.translation_.y + info.move.y;
	center.z = worldTransform_.translation_.z + info.move.z;

	// コーナー座標を計算
	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(center, static_cast<Corner>(i));
	}

	MapChipField::IndexSet indexSet;
	MapChipType mapChipType;
	bool hit = false;

	// 左下チェック
	Vector3 checkPosL = positionsNew[kLeftBottom];
	checkPosL.y -= kGroundSearchHeight;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(checkPosL);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock)
		hit = true;

	// 右下チェック
	Vector3 checkPosR = positionsNew[kRightBottom];
	checkPosR.y -= kGroundSearchHeight;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(checkPosR);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock)
		hit = true;

	if (hit) {
		// 衝突しているブロックの矩形を取得
		Vector3 bottomPos = worldTransform_.translation_;
		bottomPos.y -= kHeight / 2.0f;
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(bottomPos);
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);

		// 移動量をブロック上に補正
		info.move.y = std::min(0.0f, rect.top - worldTransform_.translation_.y + kHeight / 2.0f + kBlank);

		// 着地フラグ
		info.landing = true;
	} else {
		info.landing = false;
	}
}


Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {

	Vector3 offsetTable[kNumCorner] = {

	    {+kWidth / 2.0f, -kHeight / 2.0f, 0},
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0},
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0},
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0},
	};

	return Vector3(center.x + offsetTable[static_cast<uint32_t>(corner)].x, center.y + offsetTable[static_cast<uint32_t>(corner)].y, center.z + offsetTable[static_cast<uint32_t>(corner)].z);
}

void Player::UpdateOnGround(const CollisionMapInfo& info) {

	// 接地フラグを更新
	if (info.landing) {
		onGround_ = true;
		velocity_.y = 0.0f;
		velocity_.x *= (1.0f - kAttenuationLanding);
	} else if (velocity_.y > 0.0f) {
		// 上昇中は接地解除
		onGround_ = false;
	} else {
		// 下端の下にブロックがあるか確認して接地
		Vector3 bottomPos = worldTransform_.translation_;
		bottomPos.y -= kHeight / 2.0f + 0.01f; // 少し下に補正
		MapChipField::IndexSet indexSet = mapChipField_->GetMapChipIndexSetByPosition(bottomPos);
		MapChipType mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
		onGround_ = (mapChipType == MapChipType::kBlock);
	}
}


//void Player::UpdateOnGround(const CollisionMapInfo& info) {
//
//	//if (onGround_) {
//
//	//	if (velocity_.y > 0.0f) {
//
//	//		onGround_ = false;
//
//	//	} else {
//
//	//		std::array<Vector3, kNumCorner> positionsNew;
//
//	//		// 移動後の中心座標を計算
//	//		Vector3 center;
//	//		center.x = worldTransform_.translation_.x + info.move.x;
//	//		center.y = worldTransform_.translation_.y + info.move.y;
//	//		center.z = worldTransform_.translation_.z + info.move.z;
//
//	//		// 各コーナーの位置を計算
//	//		for (uint32_t i = 0; i < positionsNew.size(); ++i) {
//	//			positionsNew[i] = CornerPosition(center, static_cast<Corner>(i));
//	//		}
//
//	//		MapChipType mapChipType;
//
//	//		// 真下の判定
//	//		bool hit = false;
//
//	//		// 左下の判定
//	//		MapChipField::IndexSet indexSet;
//
//	//		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
//	//		mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
//
//	//		if (mapChipType == MapChipType::kBlock) {
//
//	//			hit = true;
//	//		}
//
//	//		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
//	//		mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
//
//	//		if (mapChipType == MapChipType::kBlock) {
//
//	//			hit = true;
//	//		}
//
//	//		if (!hit) {
//
//	//			onGround_ = false;
//	//		}
//	//	}
//
//	//} else {
//
//	//	if (info.landing) {
//
//	//		onGround_ = true;
//
//	//		velocity_.x *= (1.0f - kAttenuationLanding);
//
//	//		velocity_.y = 0.0f;
//	//	}
//	//}
//
//	if (onGround_) {
//
//		if (velocity_.y > 0.0f) {
//			onGround_ = false;
//		} else {
//			std::array<Vector3, kNumCorner> positionsNew;
//
//			// 移動後の中心座標
//			//Vector3 center = worldTransform_.translation_ + info.move;
//
//			Vector3 center;
//			center.x = worldTransform_.translation_.x + info.move.x;
//			center.y = worldTransform_.translation_.y + info.move.y;
//			center.z = worldTransform_.translation_.z + info.move.z;
//
//			for (uint32_t i = 0; i < positionsNew.size(); ++i) {
//				positionsNew[i] = CornerPosition(center, static_cast<Corner>(i));
//			}
//
//			bool hit = false;
//			MapChipField::IndexSet indexSet;
//			MapChipType mapChipType;
//
//			// 左下
//			Vector3 checkPosL = positionsNew[kLeftBottom];
//			checkPosL.y -= kGroundSearchHeight;
//			indexSet = mapChipField_->GetMapChipIndexSetByPosition(checkPosL);
//			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
//			if (mapChipType == MapChipType::kBlock)
//				hit = true;
//
//			// 右下
//			Vector3 checkPosR = positionsNew[kRightBottom];
//			checkPosR.y -= kGroundSearchHeight;
//			indexSet = mapChipField_->GetMapChipIndexSetByPosition(checkPosR);
//			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
//			if (mapChipType == MapChipType::kBlock)
//				hit = true;
//
//			// 地面にヒットしていなければ落下開始
//			if (!hit) {
//				onGround_ = false;
//			}
//		}
//
//	} else {
//		// 着地していたら接地状態に
//		if (info.landing) {
//			onGround_ = true;
//			velocity_.x *= (1.0f - kAttenuationLanding);
//			velocity_.y = 0.0f;
//		}
//	}
//
//
//}
