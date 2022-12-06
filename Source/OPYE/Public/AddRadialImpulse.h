// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AddRadialImpulse.generated.h"

UCLASS()
class OPYE_API AAddRadialImpulse : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Radius Properties", meta = (AllowPrivateAccess = "true"))
		float ImpulseRadius = 250.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Radius Properties", meta = (AllowPrivateAccess = "true"))
		float ImpulseForce = 1000.f;

public:	
	// Sets default values for this actor's properties
	AAddRadialImpulse();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
