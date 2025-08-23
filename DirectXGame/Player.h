#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class MapChipField;

enum class LRDirection {

	kRight,
	kLeft,

};

class Player {

public:

	struct CollisionMapInfo {

		bool ceiling = false;
		bool landing = false;
		bool hitwall = false;
		Vector3 move;
	};

	enum Corner {

		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumCorner // 要素数

	};

	~Player();

	void Initialize(Model* model, Camera* camera, const Vector3& position);

	void Update();

	void Draw(Camera& camera);

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const Vector3& GetVelocity() const { return velocity_; }

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	void InputMove();

	void CollisionMove(const CollisionMapInfo& info);

	void CheckMapCollision(CollisionMapInfo& info);

	void CheckMapCollisionUp(CollisionMapInfo& info);

	void CheckMapCollisionDown(CollisionMapInfo& info);

	//void CheckMapCollisionLeft(CollisionMapInfo& info);

	//void CheckMapCollisionRight(CollisionMapInfo& info);

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	void UpdateOnGround(const CollisionMapInfo& info);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Input* input_ = nullptr;

	Vector3 velocity_ = {};

	static inline const float kAcceleration = 0.003f;
	static inline const float kLimitRunSpeed = 0.5f;
	static inline const float kAttenuation = 0.1f;

	LRDirection lrDirection_ = LRDirection::kRight;

	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;

	static inline const float kTimeTurn = 0.3f;

	bool onGround_ = true;

	static inline const float kGravityAcceleration = 0.05f;
	static inline const float kLimitFallSpeed = 1.0f;
	static inline const float kJumpAcceleration = 1.0f;

	MapChipField* mapChipField_ = nullptr;

	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	static inline const float kBlank = 0.04f;

	static inline const float kAttenuationLanding = 0.0f;

	static inline const float kGroundSearchHeight = 0.05f;

};