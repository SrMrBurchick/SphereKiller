// Copyright Epic Games, Inc. All Rights Reserved.

#include <algorithm>
#include <vector>

#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "SphereKillerCharacter.h"
#include "SphereKillerGameMode.h"

#include "UObject/ConstructorHelpers.h"

// The intial spawn radius
const float cInitialSpawnRadius = 2000.0f;

// Scale value for the amount of spheres in the next wave (1% - 100%)
const float cSphereAmountScale = 10.0f;

// Scale value for the spawn radius in the next wave (1% - 100%)
const float cSpawnRadiusScale = 5.0f;

// Minimal distance between spheres
const float cMinSphereDistance = 80.0f;

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
	MinSphereDistance = cMinSphereDistance;
	InitialSphereCount = cInitialSphereCount;
	GoalSphereCount = cGoalSphereCount;
	GoalSphereRadius = cGoalSphereRadius;
	WaveCount = 0;
	SphereCount = 0;

	// Game must been started after that when first sphere will be killed
	bGameStarted = false;
}

void ASphereKillerGameMode::BeginPlay()
{
	Super::BeginPlay();

	/* Find Text and Killer actors */
	FActorIterator AllActorIt = FActorIterator(GetWorld());
	while (AllActorIt) {
		if (AllActorIt->GetClass() != nullptr) {
			if (AllActorIt->ActorHasTag("GreeterText")) {
				UE_LOG(LogTemp, Log, TEXT("Text Pos: %s"),
						*AllActorIt->GetActorLocation().ToString());
				InitialSpawnPosition = AllActorIt->GetActorLocation();
				pTextActor = *AllActorIt;
			} else if (AllActorIt->ActorHasTag("Killer")) {
				UE_LOG(LogTemp, Log, TEXT("Killer Pos: %s"),
						*AllActorIt->GetActorLocation().ToString());
				pKillerActor = *AllActorIt;
			}
		}
		++AllActorIt;
	}

	// Initialize sphere position
	FVector spherePosition = InitialSpawnPosition;

	// Move Killer before greeter text
	InitialSpawnPosition.X -= 200.0f;
	InitialSpawnPosition.Y -= 200.0f;
	pKillerActor->SetActorLocation(InitialSpawnPosition);

	// Spawn initial sphere
	spherePosition.X += 200.0f;
	spherePosition.Y += 200.0f;
	spherePosition.Z += 20.0f;

	if (PlayerSphere != nullptr) {
		SpawnSphere(spherePosition);
	} else {
		UE_LOG(LogTemp, Error, TEXT("Sphere Class is not detected!"));
	}
}

void ASphereKillerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASphereKillerGameMode::SpawnSphere(const FVector& position)
{
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	UWorld* world = GetWorld();
	if (nullptr == PlayerSphere) {
		UE_LOG(LogTemp, Error, TEXT("No spawn selected!"));

		return;
	}

	SpheresList.push_back(world->SpawnActor(PlayerSphere, &position,
											&SpawnRotation));
}

void ASphereKillerGameMode::ProcessActor(AActor* actor)
{
	if (nullptr == actor) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid sphere pointer!"));

		return;
	}

	if (actor->ActorHasTag("Sphere")) {
		if (false == bGameStarted) {
			bGameStarted = true;

			SpawnRadius = InitialSpawnRadius;
			GenerateLevel();

			pTextActor->Destroy();
		} else {
			ProcessSphere(actor);
		}
	}
}


void ASphereKillerGameMode::ProcessSphere(AActor* sphere)
{
	if (nullptr == sphere) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid sphere pointer!"));

		return;
	}

	if (FVector::Distance(InitialSpawnPosition, sphere->GetActorLocation())
		<= GoalSphereRadius) {
		++SphereCount;

		UE_LOG(LogTemp, Log, TEXT("Killed: %d, Goal: %d"),
			   SphereCount, GoalSphereCount);
	}

	sphere->Destroy();

	if (SphereCount >= GoalSphereCount) {
		SphereCount = 0;
		GenerateLevel();
	}
}

FVector ASphereKillerGameMode::generateSphereLocation(float radius)
{
	std::function<FVector (float radius)> generator = [&] (float radius)
	{
		return FVector(
			FMath::RandRange(InitialSpawnPosition.X - radius,
							 InitialSpawnPosition.X + radius), // X position
			FMath::RandRange(InitialSpawnPosition.Y - radius,
							 InitialSpawnPosition.Y + radius), // Y position
			InitialSpawnPosition.Z // Z position
		);
	};

	auto position = generator(radius);
	while (FVector::Distance(InitialSpawnPosition, position) > radius) {
		position = generator(radius);
	}

	return position;
}

void ASphereKillerGameMode::GenerateLevel()
{
	if (false == bGameStarted) {
		UE_LOG(LogTemp, Warning, TEXT("Game has not started yet!"));

		return;
	}

	ClearLevel();

	InitialSpawnPosition = pKillerActor->GetActorLocation();

	std::vector<FVector> spheresLocations;
	spheresLocations.reserve(InitialSphereCount);

	FVector newLocation = FVector(0.0f, 0.0f, 0.0f);
	std::function<bool(FVector)> isNotInRange = [&](const FVector position) {
		return FVector::Distance(newLocation, position) <= MinSphereDistance;
	};

	for (int i = 0; i < GoalSphereCount; i++) {
		auto it = spheresLocations.end();
		do {
			newLocation = generateSphereLocation(GoalSphereRadius);
			it = std::find_if(spheresLocations.begin(), spheresLocations.end(),
							  isNotInRange);
		} while (it != spheresLocations.end());

		spheresLocations.push_back(newLocation);

		SpawnSphere(newLocation);
	}

	UE_LOG(LogTemp, Log, TEXT("Goal Spheres generated: %d"),
		   spheresLocations.size());

	for (int i = GoalSphereCount; i < InitialSphereCount; ++i) {
		auto it = spheresLocations.end();
		do {
			newLocation = generateSphereLocation(InitialSpawnRadius);
			it = std::find_if(spheresLocations.begin(), spheresLocations.end(),
							  isNotInRange);
		} while (it != spheresLocations.end());

		spheresLocations.push_back(newLocation);

		SpawnSphere(newLocation);
	}

	UE_LOG(LogTemp, Log, TEXT("Total Spheres generated: %d"),
		   SpheresList.size());

	// Preparing for the next level
	InitialSphereCount += InitialSphereCount * SphereAmountScale / 100;
	SpawnRadius += SpawnRadius * SpawnRadiusScale / 100;

	// Increase Wave
	++WaveCount;
}

void ASphereKillerGameMode::ClearLevel()
{
	for (auto actor : SpheresList) {
		actor->Destroy();
	}
}
