// Copyright Epic Games, Inc. All Rights Reserved.

#include "SphereKillerGameMode.h"
#include "SphereKillerCharacter.h"

#include "GameFramework/Actor.h"

#include "UObject/ConstructorHelpers.h"

// The intial spawn radius
const float cInitialSpawnRadius = 2000.0f;

// Scale value for the amount of spheres in the next wave (1% - 100%)
const float cSphereAmountScale = 10.0f;

// Scale value for the spawn radius in the next wave (1% - 100%)
const float cSpawnRadiusScale = 5.0f;

// Minimal distance between spheres
const float cMinSpahereDistance = 80.0f;

// Initial amount of spheres
const int cInitialSphereCount = 15;

// Amount of spheres to the next level
const int cGoalSphereCount = 10;

// Spawn radius inside which that the killed spheres counting as goal sphere
const float cGoalSphereRadius = 1500.0f;

ASphereKillerGameMode::ASphereKillerGameMode()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn>
		PlayerPawnClassFinder(
				TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<APawn>
		PlayerSpherePawnClassFinder(
				TEXT("/Game/Blueprints/Sphere_BP"));
	PlayerSphere = PlayerSpherePawnClassFinder.Class;

	// Init params
	InitialSpawnRadius = cInitialSpawnRadius;
	SphereAmountScale = cSphereAmountScale;
	SpawnRadiusScale = cSpawnRadiusScale;
	MinSpahereDistance = cMinSpahereDistance;
	InitialSphereCount = cInitialSphereCount;
	GoalSphereCount = cGoalSphereCount;
	GoalSphereRadius = cGoalSphereRadius;
}

void ASphereKillerGameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer( UnusedHandle, this,
		&ASphereKillerGameMode::SpawnSphere, FMath::RandRange(2, 5), true
	);
}

void ASphereKillerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASphereKillerGameMode::SpawnSphere()
{
	FVector SpawnPosition = FVector(400.0f, 400.0f, 10.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	UWorld* world = GetWorld();
	if (nullptr == PlayerSphere) {
		UE_LOG(LogTemp, Error, TEXT("No spawn selected!"));

		return;
	}
	world->SpawnActor(PlayerSphere, &SpawnPosition, &SpawnRotation);

	UE_LOG(LogTemp, Warning, TEXT("Spawn!"));
}

void ASphereKillerGameMode::DestroySphere(AActor* sphere)
{
	if (nullptr == sphere) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid sphere pointer!"));
	}

	// TODO: Add goal sphere detection algorithm

	sphere->Destroy();
}

