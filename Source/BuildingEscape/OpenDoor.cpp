// Copyright David Olarte 2018.

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

    AActor* Owner = GetOwner();
    FRotator Rotation = Owner->GetActorRotation();
    UE_LOG(LogTemp, Warning, TEXT("Door initial rotation %s"), *(Rotation.ToString()));
    Rotation.SetComponentForAxis(EAxis::Z, Rotation.GetComponentForAxis(EAxis::Z) - 90.0f);
    UE_LOG(LogTemp, Warning, TEXT("Door final rotation %s"), *(Rotation.ToString()));
    Owner->SetActorRotation(Rotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

