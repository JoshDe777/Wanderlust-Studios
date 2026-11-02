// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <random>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGeneration/DiffNet.h"
#include "MapGeneration/Heightmap.h"

#include "A_MapManager.generated.h"

namespace WanderlustStudios::MapGeneration {
	const int MAX_UPSCALES = 4;
	const float FILL = 0.33f;
	const float PASS_WEIGHT = 1 / (MAX_UPSCALES + 1);
	const int MAX_START_PTS = 3;

	UCLASS()
	class WANDERLUSTSTUDIOS_API AA_MapManager : public AActor
	{
		// test case classes to access private members.
		friend class FStartNetGenerationTest;
		friend class FDiffusionLayerAggregationTest;
		friend class FDiffusionRunTest;
		friend class FDiffusionNetUpscalingTest;

		GENERATED_BODY()
	public:
		/// Constructor
		AA_MapManager();

		/// Kicks off the map generation process using a given seed, which defaults to random.
		void GenerateMap(int seed = -1);

		/// Called every frame
		virtual void Tick(float DeltaTime) override;
	protected:
		/// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	private:
		/// Generates a default StartNet with a certain amount of starting points. Defaults to random
		/// @param rnd: std::mt19937& - a reference to an existing seeded random number generator.
		/// @param nStartPoints: int - The amount of start points. Will be clamped down to MAX_START_PTS if exceeding. 
		/// Default value of -1 determines a random amount at start based on the stored seed.
		static DiffNet GenerateStartNet(std::mt19937& rnd, int nStartPoints = -1);

		/// Runs one pass of Diffusion Layer Aggregation, and exits out returning a heightmap if nUpscales is <= 0.
		/// Implementation greatly inspired by the explainer by Josh's Channel on YouTube (https://youtu.be/gsJHzBTPG0Y).
		/// @param rnd: std::mt19937& - a reference to an existing seeded random number generator.
		/// @param image: DiffNet* - A pointer to a pre-filled diffusion net (net must have at least 1 value) to fill with diffusion.
		///	May be null (will generate a new BASE_WIDTH^2 DiffNet)
		/// @param heightmap: Heightmap* - A pointer to a heightmap to apply the new DLA results to and upscale x blur. 
		/// Its result will be output. May be null (will generate a fresh heightmap from the first DiffNet).
		/// @param nUpscalesLeft: int - The amount of upscales the algorithm will perform before exiting when the value is <= 0. 
		/// Defaults to MAX_UPSCALES.
		/// @returns Heightmap* An image/texture representing the heightmap of generated terrain.
		static Heightmap* DiffusionLayerAggregation(std::mt19937& rnd, DiffNet* image = nullptr, Heightmap* heightmap = nullptr, int nUpscalesLeft = MAX_UPSCALES);
		
		/// Runs a single pass of Pixel Diffusion on an existing DiffNet, until a certain amount of the net is filled.
		/// @param rnd: std::mt19937& - a reference to an existing seeded random number generator.
		/// @param image: DiffNet* - A pointer to a pre-filled diffusion net (net may not be empty) that will be populated with pixels.
		/// The results will be directly applied to the image, not explicitly returned (image may not be const).
		/// @param neighbours: TMap<FVector2D, TArray<FVector2D>>& - a reference to a dictionary pointing populated pixels to its neighbours.
		/// New neighbours will be applied directly to the map, not explicitly returned (neighbours may not be const).
		/// @param fillPercent: float[0, 1] - The percentage of the image that needs to be filled until the pass can exit. 
		/// Value will be clamped to the range of [0, 1] if outside.
		static void DiffusionPass(std::mt19937& rnd, DiffNet* image, float fillPercent);
	};
}
