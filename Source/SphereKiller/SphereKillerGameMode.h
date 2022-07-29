// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SphereKillerGameMode.generated.h"

UCLASS(minimalapi)
class ASphereKillerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASphereKillerGameMode();

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> PlayerSphere;

	// The intial spawn radius
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float InitialSpawnRadius;

	// Scale value for the amount of spheres in the next wave (1% - 100%)
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SphereAmountScale;

	// Scale value for the spawn radius in the next wave (1% - 100%)
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SpawnRadiusScale;

	// Minimal distance between spheres
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MinSpahereDistance;

	// Initial amount of spheres
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int InitialSphereCount;

	// Amount of spheres to the next level
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int GoalSphereCount;

	// Spawn radius inside which that the killed spheres counting as goal sphere
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float GoalSphereRadius;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Invokes from the bullet class for checking if the sphere is a goal one
	void DestroySphere(AActor* sphere);

private:
	void SpawnSphere();

};



