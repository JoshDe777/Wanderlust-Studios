#if WITH_DEV_AUTOMATION_TESTS

#include <vector>
#include "Misc/AutomationTest.h"
#include "A_MapManager.h"

// Test the generation of the default net
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStartNetGenerationTest, "WanderlustStudios.Tests.StartNetGenerationTest", 
	EAutomationTestFlags_ApplicationContextMask |
	EAutomationTestFlags::ProductFilter)

bool FStartNetGenerationTest::RunTest(const FString& Parameters) {
	// generate a default DiffNet
	DiffNet result = AA_MapManager::GenerateStartNet();

	// test that the output is a square of dims DEFAULT squared, and that there's at least one tile with a non-zero value.
	TestEqual("Start Net Start size", result.count(), BASE_WIDTH * BASE_WIDTH);
	TestGreaterThan("Start Net population", result.sum(), 0);

	// test fixed amount of starting points.
	DiffNet res2 = AA_MapManager::GenerateStartNet(1);
	TestEqual("Start Net Generation with Fixed Population", result.sum(), 1)

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

	// attempt to 'jailbreak' the algorithm by bypassing the exit floor
	AA_MapManager::DiffusionLayerAggregation(nullptr, nullptr, -1);

	return true;
}

// Test an individual diffusion run
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDiffusionRunTest, "WanderlustStudios.Tests.DiffusionRunTest",
	EAutomationTestFlags_ApplicationContextMask |
	EAutomationTestFlags::ProductFilter)

bool ::RunTest(const FString& Parameters) {
	// generate default diffnet
	DiffNet result = AA_MapManager::GenerateStartNet();
	DiffNet start = result.Copy();

	TMap<FVector2D, TArray<FVector2D>> neighbours = {};
	AA_MapManager::DiffusionPass(result, neighbours, FILL);

	// test output density
	neighbours = {};
	TestGreaterThan("Diffusion Density Test", result.sum(), FILL * result.count());
	
	// test with empty net, request 100% density
	DiffNet empty = DiffNet();
	AA_MapManager::DiffusionPass(empty, neighbours, FILL);

	// test a request for 100% density
	neighbours = {};
	AA_MapManager::DiffusionPass(start, neighbours, 1.0f);

	return true;
}

// test that the upscale of a diffnet worked.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDiffusionNetUpscalingTest, "WanderlustStudios.Tests.DiffusionNetUpscalingTest",
	EAutomationTestFlags_ApplicationContextMask |
	EAutomationTestFlags::ProductFilter)

bool FDiffusionNetUpscalingTest::RunTest(const FString& Parameters) {
	// do a diffusion run on a base map with exactly one starting point
	DiffNet start = AA_MapManager::GenerateStartNet(1);
	TMap<FVector2D, TArray<FVector2D>> neighbours = {};
	AA_MapManager::DiffusionPass(start, neighbours, FILL);

	DiffNet upscale = start.Upscale(neighbours);
	TestEqual("Upscale = 4*Input", upscale.count(), 4 * start.count());
	
	// test adjacencies:
	// - every tile has neighbours (should be guaranteed if exactly 1 starting point)
	// - every tile has at most 8 neighbours (straight & diagonal adjacency)
	// - every neighbour is a direct neighbour (distance <= sqrt(2) because diagonal adjacency possible from rasterisation)
	for (FVector2D& tile : upscale) {
		TestTrue("tile has neighbours", neighbours.Contains(tile));
		TestLessEqual("1 <= n(neighbours) <= 8", neighbours[tile].Num(), 8);
		for (FVector2D& n : neighbours[tile]) {
			TestLessEqual("Distance to neighbour at most sqrt(2)", FVector2D::Distance(tile, n), sqrt(2));
		}
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
	// - output dimensions (should be 8x8)
	// - values & clamping (any negative or >1 values?)

	// further tests for edge-cases:
	// 1x1 'heightmap'
	// empty 0-value HM,
	// empty 1-value HM

	return true;
}



#endif // WITH_DEV_AUTOMATION_TESTS