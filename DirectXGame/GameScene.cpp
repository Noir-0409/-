#include "GameScene.h"

GameScene::~GameScene() {

	delete modelPlayer_;
	delete player_;
	delete mapChipField_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}

	worldTransformBlocks_.clear();

}

void GameScene::Initialize() {

	modelPlayer_ = Model::CreateFromOBJ("Player");

	modelBlock_ = Model::CreateFromOBJ("block");

	// カメラの初期化
	camera_.Initialize();

	player_ = new Player();

	player_->Initialize(modelPlayer_);

	input_ = Input::GetInstance();

	worldTransform_.Initialize();

	mapChipField_ = new MapChipField;

	mapChipField_->LoadMapChipCSV("Resources/map.csv");

	GenerateBlocks();

}

void GameScene::Update() { player_->Update(); 

for (std::vector<WorldTransform*> worldTransformBlockTate : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlockYoko : worldTransformBlockTate) {
			if (!worldTransformBlockYoko)
				continue;

			// アフィン変換行列の作成
			worldTransformBlockYoko->UpdateMatrix();
		}
	}

}

void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();

	Model::PreDraw();

	player_->Draw(camera_);

	for (std::vector<WorldTransform*> worldTransformBlockTate : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlockYoko : worldTransformBlockTate) {
			if (!worldTransformBlockYoko)
				continue;

			modelBlock_->Draw(*worldTransformBlockYoko, camera_);
		}
	}

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}

void GameScene::GenerateBlocks() {

	//uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	//uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	worldTransformBlocks_.resize(MapChipField::kNumBlockVirtical);

	for (uint32_t i = 0; i < MapChipField::kNumBlockVirtical; ++i) {

		worldTransformBlocks_[i].resize(MapChipField::kNumBlockHorizontal);
	
	}

	for (uint32_t i = 0; i < MapChipField::kNumBlockVirtical; ++i) {

		worldTransformBlocks_[i].resize(MapChipField::kNumBlockHorizontal);
	}

	for (uint32_t i = 0; i < MapChipField::kNumBlockVirtical; ++i) {

		for (uint32_t j = 0; j < MapChipField::kNumBlockHorizontal; ++j) {

			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {

				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

}
