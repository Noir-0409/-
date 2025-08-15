#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Player;

class CameraController {

public:

void Initialize();

void Update();

void SetTarget(Player* target) { target_ = target; }

void SetCamera(Camera* camera) { camera_ = camera; }

void Reset();

private:

Camera* camera_ = nullptr;

Player* target_ = nullptr;

Vector3 targetOffset_ = {0, 0, -15.0f};

};