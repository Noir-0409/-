#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

enum class LRDirection {

	kRight,
	kLeft,

};

class Player {

public:
	~Player();

	void Initialize(Model* model, Camera* camera, const Vector3& position);

	void Update();

	void Draw(Camera& camera);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Input* input_ = nullptr;

	Vector3 velocity_ = {};

	static inline const float kAcceleration = 0.003f;

	static inline const float kLimitRunSpeed = 0.5f;

	LRDirection lrDirection_ = LRDirection::kRight;

};