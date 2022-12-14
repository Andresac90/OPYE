// Copyright Epic Games, Inc. All Rights Reserved.

#include "OPYEProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "AddRadialImpulse.h"
#include "GameFramework/Actor.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"

AOPYEProjectile::AOPYEProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AOPYEProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	//UE_LOG(LogTemp, Log, TEXT("Actor location: %s"), *ProjectileMovement->GetActorLocation().ToString());

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);

}

void AOPYEProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		FActorSpawnParameters SpawnInfo;

		UE_LOG(LogTemp, Log, TEXT("Projectile location OnHit: %s"), *SpawnLocation.ToString());

		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, SpawnLocation, SpawnRotation);
		}

		GetWorld()->SpawnActor<AAddRadialImpulse>(RadialImpulseClass, SpawnLocation, SpawnRotation);
		//GetWorld()->SpawnActor<AAddRadialImpulse>(SpawnLocation, SpawnRotation, SpawnInfo);

		Destroy();
	}

}