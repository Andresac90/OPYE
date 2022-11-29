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

	//SetActorLocation(FVector(1000, 1000, 50));
	
	TArray<FHitResult> OutHits;

	FVector ImpulseLocation = GetActorLocation();

	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(500.f);

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
				MeshComp->AddRadialImpulse(ImpulseLocation, 1000.f, 3000.f, ERadialImpulseFalloff::RIF_Constant, true);
			}
			
			if (CharComp)
			{
				FVector CharLocation = CharComp->GetActorLocation();
				FVector LaunchDirection = CharLocation - ImpulseLocation;
				float mag = 0;
				LaunchDirection.ToDirectionAndLength(LaunchDirection, mag);
				LaunchDirection = LaunchDirection * 1000;

				UE_LOG(LogClass, Log, TEXT("Impulse Direction vector: %s"), *(LaunchDirection.ToString()));
				
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

