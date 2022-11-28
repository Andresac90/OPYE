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

	FVector MyLocation = GetActorLocation();

	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(500.f);

	DrawDebugSphere(GetWorld(), MyLocation, MyColSphere.GetSphereRadius(), 50, FColor::Cyan, true);

	UE_LOG(LogTemp, Log, TEXT("AddImpulse Actor location BeginPlay: %s"), *MyLocation.ToString());

	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, MyLocation, MyLocation, FQuat::Identity, ECC_WorldStatic, MyColSphere);

	if (isHit)
	{
		for (auto& Hit : OutHits)
		{
			UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>((Hit.GetActor())->GetRootComponent());
			ACharacter* CharComp = Cast<ACharacter>((Hit.GetActor())->GetRootComponent());
			//UCapsuleComponent* CapsComp = Cast<UCapsuleComponent>((Hit.GetActor())->GetRootComponent());

			if (MeshComp)
			{
				MeshComp->AddRadialImpulse(MyLocation, 1000.f, 3000.f, ERadialImpulseFalloff::RIF_Constant, true);
			}
			
			if (CharComp)
			{
				//CharComp->AddRadialImpulse(MyLocation, 2000.f, 500000.f, ERadialImpulseFalloff::RIF_Constant, true);
				//CharComp->LaunchCharacter(FVector(0,0, 5000.f), false, true);
			}
		}
	}
}

// Called every frame
void AAddRadialImpulse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

