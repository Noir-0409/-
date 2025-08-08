#include "GameScene.h"

GameScene::~GameScene() {

		delete modelPlayer_;
	delete player_;

}

void GameScene::Initialize() {

	modelPlayer_ = Model::CreateFromOBJ("Player");

	// カメラの初期化
	camera_.Initialize();

		player_ = new Player();

	player_->Initialize(modelPlayer_);

		input_ = Input::GetInstance();


}

void GameScene::Update() {

	player_->Update();


}

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