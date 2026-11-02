// Fill out your copyright notice in the Description page of Project Settings.

#include <algorithm>

#include "A_MapManager.h"
#include "MapGeneration/MapGenUtils.h"

namespace WanderlustStudios::MapGeneration {
	// Sets default values
	AA_MapManager::AA_MapManager()
	{
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;
	}

	// Called when the game starts or when spawned
	void AA_MapManager::BeginPlay()
	{
		Super::BeginPlay();
	}

	// Called every frame
	void AA_MapManager::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);
	}

	void AA_MapManager::GenerateMap(int seed) {

	}

	DiffNet AA_MapManager::GenerateStartNet(std::mt19937& rnd, int nStartPoints = -1) {
		DiffNet net = DiffNet();
		
		// determine random amount of start points if none specified
		if (nStartPoints == -1) {
			std::uniform_int_distribution<int> n(1, MAX_START_PTS);
			nStartPoints = n(rnd);
		}
		else {
			// if specified ensure it's within the specified range of 0 < x <= MAX_START_PTS
			nStartPoints = std::clamp(nStartPoints, 1, MAX_START_PTS);
		}

		for (int i = 0; i < nStartPoints; i++) {
			// pick a random coordinate in the DiffNet (repick if already mapped) and mark as a starter pixel.
			std::pair<int, int> dims = net.Dimensions();

			std::uniform_int_distribution<int> dimX(0, dims.first-1);
			std::uniform_int_distribution<int> dimY(0, dims.second-1);

			std::pair<int, int> coords;

			while (true) {
				// pick random x, y coords in the grid.
				coords = {
					/* x= */ dimX(rnd),
					/* y= */ dimY(rnd)
				};

				// exit loop if the chosen coords are not in the net.
				if (!net.Contains(coords))
					break;
			}

			// mark the coords into the net.
			net.MarkStarter(coords);
		}

		return net;
	}

	Heightmap* AA_MapManager::DiffusionLayerAggregation(std::mt19937& rnd, DiffNet* image, Heightmap* heightmap, int nUpscalesLeft)
	{
		if (nUpscalesLeft <= 0)
			return heightmap;

		if (image == nullptr)
			image = &AA_MapManager::GenerateStartNet(rnd);

		// populate the DiffNet until filled
		AA_MapManager::DiffusionPass(rnd, image, FILL);

		// generate a blank heightmap with the same dimensions as the DiffNet if no HM provided.
		if (heightmap == nullptr) {
			heightmap = &Heightmap(image->Dimensions());
		}

		// apply the image to the heightmap
		heightmap->apply_additive(image, PASS_WEIGHT/2);

		// blur & upscale the heightmap
		heightmap->UpscaleAndBlur();
		// upscale the image
		image->Upscale();

		// reapply the image to the heightmap for extra detail (?)
		heightmap->apply_additive(image, PASS_WEIGHT / 2);

		// and pass it on for another pass!
		return DiffusionLayerAggregation(rnd, image, heightmap, nUpscalesLeft-1);
	}

	void AA_MapManager::DiffusionPass(std::mt19937& rnd, DiffNet* image, float fillPercent) {
		// while image.count() < image.flat_dimensions() * fillPercent
		while (image->GetFill() < fillPercent) {
			// select random, unfilled pixel
			auto pool = image->GetUnmarkedPixels();
			std::uniform_int_distribution<int> size(0, pool.size() - 1);
			int index = size(rnd);

			std::pair<int, int> startPixel = pool[index];

			std::pair<int, int> currentPos = startPixel;
			std::pair<int, int> nextPos = startPixel;

			// from pixel do a random walk until neighbouring a mapped pixel
			while (true) {
				std::pair<int, int> step = ChooseRandomStep(rnd);
				nextPos = {currentPos.first + step.first, currentPos.second + step.second};

				// next iteration without moving if stepping out of bounds
				if (!image->InBounds(nextPos))
					continue;

				// exit loop if nextPos is mapped.
				if (image->Contains(nextPos))
					break;

				// otherwise do the step and continue the random walk.
				currentPos = nextPos;
			}

			// find the diffnetpixel object at position nextstep
			DiffNetPixel* px = image->Find(nextPos);
			// add currentposition to the diffnet.
			image->Mark(currentPos, px);

		}	/* end while (image->GetFill() < fillPercent) */ 
	}

	std::pair<int, int> ChooseRandomStep(std::mt19937& rnd) {
		std::uniform_int_distribution<int> i(0, 3);
		int index = i(rnd);
		return DirectionVectors.at(DIRECTIONS(index));
	}
 }
