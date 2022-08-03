// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <list>

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameLevelFactory/IGameLevelFactory.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Runtime/UMG/Public/UMG.h"

#include "SphereKillerGameMode.generated.h"

UCLASS(minimalapi)
class ASphereKillerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASphereKillerGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APawn> PlayerSphere;

	// The initial spawn radius
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitialSpawnRadius;

	// Scale value for the amount of spheres in the next wave (1% - 100%)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SphereAmountScale;

	// Scale value for the spawn radius in the next wave (1% - 100%)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadiusScale;

	// Minimal distance between spheres
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinSphereDistance;

	// Initial amount of spheres
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InitialSphereCount;

	// Amount of spheres to the next level
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GoalSphereCount;

	// Spawn radius inside which that the killed spheres counting as goal sphere
	UPROPERTY(EditAnywhere)
	float GoalSphereRadius;

	// Spawn radius inside which that the killed spheres counting as goal sphere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI HUD")
		TSubclassOf<UUserWidget> HUDWidget_Class;
	UUserWidget* HUDWidget;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int SphereCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int WaveCount;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Invokes from the bullet class and processing actor
	void ProcessActor(AActor* actor);

private:
	// Initial spawn position for player
	AActor* pKillerActor;
	AActor* pTextActor;
	FVector InitialSpawnPosition;

	float SpawnRadius;

	bool bGameStarted;

	std::list<AActor*> SpheresList;

	FVector generateSphereLocation(float radius);

	// Spawn sphere at position
	void SpawnSphere(const FVector& position);
	// Checks if sphere is a goal one
	void ProcessSphere(AActor* sphere);

	void ClearLevel();
	void GenerateLevel();
};



