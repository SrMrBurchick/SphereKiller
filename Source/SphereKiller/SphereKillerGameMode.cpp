// Copyright Epic Games, Inc. All Rights Reserved.

#include "SphereKillerGameMode.h"
#include "SphereKillerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASphereKillerGameMode::ASphereKillerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn>
		PlayerPawnClassFinder(
				TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

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
	// TODO: Add sphere spawn algorithm
}

void ASphereKillerGameMode::DestroySphere(AActor* sphere)
{
	if (nullptr == sphere) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid sphere pointer!"));
	}

	// TODO: Add goal sphere detection algorithm

	sphere->Destroy();
}

