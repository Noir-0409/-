#pragma once
#include <cstdint>
#include <vector>
#include <fstream>
#include <sstream>
#include <KamataEngine.h>
#include <math/Vector3.h>

using namespace KamataEngine;

enum class MapChipType {

kBlank,
kBlock,

};

struct MapChipData {

std::vector<std::vector<MapChipType>> data;

};

class MapChipField {

public:

void Initialize();

void Update();

void Draw();

void ResetMapChipData();

void LoadMapChipCSV(const std::string& filePath);

Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

uint32_t GetNumBlockVirtical();

uint32_t GetNumBlockHorizontal();

static inline const uint32_t kNumBlockVirtical = 20;
static inline const uint32_t kNumBlockHorizontal = 100;

private:

static inline const float kBlockWidth = 1.0f;
static inline const float kBlockHeight = 1.0f;

MapChipData mapChipData_;

};