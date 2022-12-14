// Copyright Epic Games, Inc. All Rights Reserved.

#include "SphereKillerProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "SphereKiller/SphereKillerGameMode.h"

#include "Components/SphereComponent.h"

ASphereKillerProjectile::ASphereKillerProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");

	// set up a notification for when this component hits something blocking
	CollisionComp->OnComponentHit.AddDynamic(this,
			&ASphereKillerProjectile::OnHit);
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(
			FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement =
		CreateDefaultSubobject<UProjectileMovementComponent>(TEXT(
															"ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ASphereKillerProjectile::OnHit(UPrimitiveComponent* HitComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this)
		&& (OtherComp != nullptr))
	{
		UWorld* world = GetWorld();
		bool destroy = false;

		UE_LOG(LogTemp, Log, TEXT("Bullet class: %s"), *GetClass()->GetName());
		ASphereKillerGameMode* gamemode =
			world->GetAuthGameMode<ASphereKillerGameMode>();

		if (OtherActor->ActorHasTag("Sphere")) {
			destroy = true;
		}

		gamemode->ProcessActor(OtherActor);

		if (destroy) {
			Destroy();
		}

	}
}
