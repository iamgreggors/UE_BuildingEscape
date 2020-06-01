// Copyright Greg is Cool 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Reach = 150.f;
	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = NULL;

	UPROPERTY()
	UInputComponent* InputComponent = NULL;

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();

	// Return the first Actor within reach with the physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

	// Return the Line Trace End
	FVector GetPlayerReach() const;

	// Return the Player's Position in the World
	FVector GetPlayerPosition() const;

};
