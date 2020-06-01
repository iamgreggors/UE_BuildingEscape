// Copyright Greg is Cool 2020


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

//#define CHECKNULL(CheckMe) if(!CheckMe) { UE_LOG(LogTemp, Error, TEXT("NULL Pointer Found in %s : %s"), __FILE__, __LINE__); return; }

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

	// FRotator CurrentRotation = GetOwner()->GetActorRotation();
	// CurrentRotation.Yaw = -90.f;
	// GetOwner()->SetActorRotation(CurrentRotation);

	float InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw = TargetYaw;

	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has an OpenDoor Component without a PressurePlate assigned"),*GetOwner()->GetName());
	}

	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	//CHECKNULL(AudioComponent)
	if(!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("NULL Pointer Found in %s : %d"), __FILE__, __LINE__); return;
	}

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if(TotalMassOfActors() > MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if(GetWorld()->GetTimeSeconds() - DoorLastOpened >= DoorClosedDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	if(!DoorIsOpen)
		{
		DoorIsOpen = true;
		if(!AudioComponent) return;
		AudioComponent->Play();
		}
	
}


void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	if(DoorIsOpen)
		{
		DoorIsOpen = false;
		if(!AudioComponent) return;
		AudioComponent->Play();
		}
		
}


float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	// Find All Overlapping Actors
	TArray<AActor*> OverlappingActors;

	
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Sum Mass
	for(auto& Actor : OverlappingActors)
	{
		TotalMass +=  Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}