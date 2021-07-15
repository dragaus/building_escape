// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component but no PressurePlate set!"), *GetOwner()->GetName());
	}
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else 
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened >= DoorCloseDelay) 
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	ChangeDoorStatus(TargetYaw, DeltaTime, OpenSpeed);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	ChangeDoorStatus(InitialYaw, DeltaTime, CloseSpeed);
}

void UOpenDoor::ChangeDoorStatus(float DesiredYaw, float DeltaTime, float SpeedOfChange)
{
	/*FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw += 90.f;

	GetOwner()->SetActorRotation(CurrentRotation);*/
	CurrentYaw = FMath::FInterpTo(CurrentYaw, DesiredYaw, DeltaTime, SpeedOfChange);
	GetOwner()->SetActorRotation(FRotator{ 0.f, CurrentYaw, 0.f });
}

