#include "GameScene.h"

GameScene::~GameScene() {

	delete modelPlayer_;
	delete player_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}

	worldTransformBlocks_.clear();

}

void GameScene::Initialize() {

	modelPlayer_ = Model::CreateFromOBJ("Player");

	modelBlock_ = Model::CreateFromOBJ("cube");

	// カメラの初期化
	camera_.Initialize();

	player_ = new Player();

	player_->Initialize(modelPlayer_);

	input_ = Input::GetInstance();

	worldTransform_.Initialize();
}

void GameScene::Update() { player_->Update(); }

void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();

	Model::PreDraw();

	player_->Draw(camera_);

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}