// Fill out your copyright notice in the Description page of Project Settings.


#include "A_MapManager.h"

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

