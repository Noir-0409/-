#pragma once
#include "KamataEngine.h"
#include "Player.h"

using namespace KamataEngine;

// ゲームシーン
class GameScene {

public:

	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// カメラ
	Camera camera_;

	Input* input_ = nullptr;

	Model* modelPlayer_ = nullptr;

	Player* player_ = nullptr;
};