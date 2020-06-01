// Copyright Greg is Cool 2020


#include "Vanisher.h"

// Sets default values for this component's properties
UVanisher::UVanisher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVanisher::BeginPlay()
{
	Super::BeginPlay();

	

}


// Called every frame
void UVanisher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

