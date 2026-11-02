#if WITH_DEV_AUTOMATION_TESTS

#include <vector>
#include<memory>
#include "Misc/AutomationTest.h"
// Wanderlust members
#include "A_MapManager.h"

// using statements
using namespace std;
using WanderlustStudios::MapGeneration::AA_MapManager;
using WanderlustStudios::MapGeneration::BASE_WIDTH;
using WanderlustStudios::MapGeneration::MAX_UPSCALES;
using WanderlustStudios::MapGeneration::FILL;
using WanderlustStudios::MapGeneration::PASS_WEIGHT;
using WanderlustStudios::MapGeneration::DiffNet;
using WanderlustStudios::MapGeneration::DiffNetPixel;
using WanderlustStudios::MapGeneration::Heightmap;

// Test the generation of the default net
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStartNetGenerationTest, "WanderlustStudios.Tests.StartNetGenerationTest", 
	EAutomationTestFlags_ApplicationContextMask |
	EAutomationTestFlags::ProductFilter)

bool FStartNetGenerationTest::RunTest(const FString& Parameters) {
	// generate a default DiffNet
	DiffNet result = AA_MapManager::GenerateStartNet();

	// test that the output is a square of dims DEFAULT squared, and that there's at least one tile with a non-zero value.
	TestEqual("Start Net Start size", result.FlatDimensions(), BASE_WIDTH * BASE_WIDTH);
	TestGreaterThan("Start Net population", result.Sum(), 0.0f);

	// test fixed amount of starting points.
	DiffNet res2 = AA_MapManager::GenerateStartNet(1);
	TestEqual("Start Net Generation with Fixed Population", result.Sum(), 1.0f);

	return true;
}

// stress filter because tests the entire algorithm.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDiffusionLayerAggregationTest, "WanderlustStudios.Tests.DiffusionLayerAggregationTest",
	EAutomationTestFlags_ApplicationContextMask |
	EAutomationTestFlags::StressFilter)

bool FDiffusionLayerAggregationTest::RunTest(const FString& Parameters) {
	double startTime = FPlatformTime::Seconds();
	// run the generation algorithm without parameters, and make sure it exits.
	AA_MapManager::DiffusionLayerAggregation();

	double runtime = FPlatformTime::Seconds() - startTime;
	UE_LOG(LogTemp, Log, TEXT("DLA Algorithm completed in %.4f s, starting with a %dx%d grid, with %d recursion steps."), runtime, BASE_WIDTH, BASE_WIDTH, MAX_UPSCALES);

	// attempt to 'jailbreak' the algorithm by bypassing the exit floor & nullify test if it's not a nullptr (== heightmap fed in.)
	if (AA_MapManager::DiffusionLayerAggregation(nullptr, nullptr, nullptr, -1) != nullptr)
		return false;

	return true;
}

// Test an individual diffusion run
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDiffusionRunTest, "WanderlustStudios.Tests.DiffusionRunTest",
	EAutomationTestFlags_ApplicationContextMask |
	EAutomationTestFlags::ProductFilter)

bool FDiffusionRunTest::RunTest(const FString& Parameters) {
	// generate default diffnet
	unique_ptr<DiffNet> result = make_unique<DiffNet>(AA_MapManager::GenerateStartNet());
	unique_ptr<DiffNet> start = make_unique<DiffNet>(result->Copy());

	AA_MapManager::DiffusionPass(nullptr, result.get(), FILL);

	// test output density
	TestGreaterThan("Diffusion Density Test", result->Sum(), FILL * (float) result->FlatDimensions());
	
	// test with empty net, request 100% density
	DiffNet empty = DiffNet();
	AA_MapManager::DiffusionPass(nullptr, &empty, FILL);

	// test a request for 100% density
	AA_MapManager::DiffusionPass(nullptr, start.get(), 1.0f);

	return true;
}

// test that the upscale of a diffnet worked.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDiffusionNetUpscalingTest, "WanderlustStudios.Tests.DiffusionNetUpscalingTest",
	EAutomationTestFlags_ApplicationContextMask |
	EAutomationTestFlags::ProductFilter)

bool FDiffusionNetUpscalingTest::RunTest(const FString& Parameters) {
	// do a diffusion run on a base map with exactly one starting point
	DiffNet start = AA_MapManager::GenerateStartNet(1);
	AA_MapManager::DiffusionPass(nullptr, &start, FILL);
	int oldDimensions = start.FlatDimensions();

	start.Upscale();
	TestEqual("Upscale = 4*Input", start.FlatDimensions(), 4 * oldDimensions);
	
	// test adjacency
	for (DiffNetPixel* tile : start.Enumerate()) {
		// skip if starter pixel (no predecessor)
		if (tile->predecessor == nullptr)
			continue;

		FVector2D tilePos = FVector2D(tile->gridCoords.first, tile->gridCoords.second);
		FVector2D predTilePos = FVector2D(tile->predecessor->gridCoords.first, tile->predecessor->gridCoords.second);
		TestLessEqual("Distance to predecessor at most sqrt(2)", FVector2D::Distance(tilePos, predTilePos), sqrt(2));
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHeightmapUpscalingTest, "WanderlustStudios.Tests.HeightmapUpscalingTest",
	EAutomationTestFlags_ApplicationContextMask |
	EAutomationTestFlags::ProductFilter)

bool FHeightmapUpscalingTest::RunTest(const FString& Parameters) {
	std::vector<float> dummyHeightmap = {
		0.12f, 0.18f, 0.25f, 0.31f,
		0.19f, 0.43f, 0.67f, 0.52f,
		0.38f, 0.71f, 0.89f, 0.74f,
		0.29f, 0.55f, 0.68f, 0.41f
	};

	// upscale the given dummy and check for:
	// - output dimensions (should be 8x8=64)
	// - values & clamping (any negative or >1 values?)
	Heightmap upscale = Heightmap(dummyHeightmap).Upscale();
	TestEqual("Heightmap Upscale dimensions", upscale.dimensions(), 64);
	for (auto& value : upscale.values()) {
		TestGreaterEqual("Positive-only values", value, 0.0f);
		TestLessEqual("Values in range [0, 1]", value, 1.0f);
	}

	// further tests for edge-cases:
	// 1x1 'heightmap'
	dummyHeightmap = {0.65f}; 
	upscale = Heightmap(dummyHeightmap).Upscale();
	TestEqual("Heightmap Upscale dimensions", upscale.dimensions(), 9);
	for (auto& value : upscale.values()) {
		TestGreaterEqual("Positive-only values", value, 0.0f);
		TestLessEqual("Values in range [0, 1]", value, 1.0f);
	}

	// empty 0-value HM,
	dummyHeightmap = {}; 
	upscale = Heightmap(dummyHeightmap).Upscale();
	TestEqual("Heightmap Upscale dimensions", upscale.dimensions(), 0);

	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS