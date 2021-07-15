// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void ChangeDoorStatus(float DesiredYaw, float DeltaTime, float SpeedOfChange);

private:
	float InitialYaw;
	float CurrentYaw;
	// Determine the relative amount that this door will open in degrees limited to -100.0 and 100.0
	UPROPERTY(EditAnywhere, meta = (ClampMin = "-100.0", ClampMax = "100.0", UIMin = "-100.0", UIMax = "100.0"))
	float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = .5f;
	UPROPERTY(EditAnywhere)
	float CloseSpeed = 1.f;
	
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;
	float DoorLastOpened = 0.f;


	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;
};
