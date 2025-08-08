#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Player {

public:
	~Player();

	void Initialize(Model* model);

	void Update();

	void Draw(Camera& camera);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Input* input_ = nullptr;
};