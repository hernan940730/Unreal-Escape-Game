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
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    OpenDoorTrigger();
}

void UOpenDoor::OpenDoor() {
    AActor* Owner = GetOwner();
    FRotator Rotation = Owner->GetActorRotation();
    Rotation.SetComponentForAxis(EAxis::Z, -90.0f);
    Owner->SetActorRotation(Rotation);
}

void UOpenDoor::OpenDoorTrigger() {
    if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
        OpenDoor();
    }
}
