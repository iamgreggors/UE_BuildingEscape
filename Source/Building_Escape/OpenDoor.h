// Copyright Greg is Cool 2020

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
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

private:
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;	

	UPROPERTY(EditAnywhere)
	float DoorClosedDelay = 2.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = - 0.1f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = - 0.2f;

	UPROPERTY(EditAnywhere)
	float TargetYaw = -90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.f;

	float DoorLastOpened = 0.f;
	float CurrentYaw = 0.f;
	float InitialYaw = 0.f;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

	bool DoorIsOpen = false;

};
