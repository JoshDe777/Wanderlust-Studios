// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_MapManager.generated.h"

const int BASE_WIDTH = 4;
const int MAX_UPSCALES = 4;
const float FILL = 0.33f;
const float PASS_WEIGHT = 1 / (MAX_UPSCALES + 1);

UCLASS()
class WANDERLUSTSTUDIOS_API AA_MapManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_MapManager();

	/// Kicks off the map generation process using a given seed, which defaults to random.
	void GenerateMap(int seed = -1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
