// Fill out your copyright notice in the Description page of Project Settings.


#include "AddRadialImpulse.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "GameFramework/Character.h" 

// Sets default values
AAddRadialImpulse::AAddRadialImpulse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAddRadialImpulse::BeginPlay()
{
	Super::BeginPlay();
	
	float impulseRadius = 250.f;
	float impulseForce = 1000.f;

	TArray<FHitResult> OutHits;
	FVector ImpulseLocation = GetActorLocation();
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(impulseRadius);

	DrawDebugSphere(GetWorld(), ImpulseLocation, MyColSphere.GetSphereRadius(), 50, FColor::Cyan, true);

	UE_LOG(LogTemp, Log, TEXT("AddImpulse Actor location BeginPlay: %s"), *ImpulseLocation.ToString());

	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, ImpulseLocation, ImpulseLocation, FQuat::Identity, ECC_WorldDynamic, MyColSphere);

	if (isHit)
	{
		for (auto& Hit : OutHits)
		{
			UE_LOG(LogClass, Log, TEXT("Impulse hit component: %s"), *((Hit.GetActor())->GetName()));

			UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>((Hit.GetActor())->GetRootComponent());
			ACharacter* CharComp = Cast<ACharacter>((Hit.GetActor()));

			if (MeshComp)
			{
				MeshComp->AddRadialImpulse(ImpulseLocation, impulseRadius, impulseForce, ERadialImpulseFalloff::RIF_Constant, true);
			}
			
			if (CharComp)
			{
				//Currently launch force is equal to "scale", regardless of distance from impulse origin.
				//TODO: make launch froce origin distance dependent

				FVector CharLocation = CharComp->GetActorLocation();
				FVector LaunchDirection = CharLocation - ImpulseLocation;
				float distance; //Player distance from impulse origin, not used currently.
				float scale = impulseForce;
				LaunchDirection.ToDirectionAndLength(LaunchDirection, distance);
				LaunchDirection = LaunchDirection * scale;

				CharComp->LaunchCharacter(LaunchDirection, false, true);
			}
		}
	}
}

// Called every frame
void AAddRadialImpulse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

