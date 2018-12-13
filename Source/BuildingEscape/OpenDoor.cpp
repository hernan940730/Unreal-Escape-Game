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
    Owner = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    OpenDoorTrigger();
}

void UOpenDoor::OpenDoor() {
    FRotator Rotation = Owner->GetActorRotation();
    Rotation.SetComponentForAxis(EAxis::Z, OpenAngle);
    Owner->SetActorRotation(Rotation);
    LastDoorOpenTime = GetWorld()->GetTimeSeconds();
}

void UOpenDoor::CloseDoor() {
    FRotator Rotation = Owner->GetActorRotation();
    Rotation.SetComponentForAxis(EAxis::Z, 0.0f);
    Owner->SetActorRotation(Rotation);
}

void UOpenDoor::OpenDoorTrigger() {
    if (ShouldOpenDoor()) {
        OpenDoor();
    }
    else if (ShouldCloseDoor()){
        CloseDoor();
    }
}

bool UOpenDoor::ShouldOpenDoor() {
    return PressurePlate->IsOverlappingActor(ActorThatOpens);
}

bool UOpenDoor::ShouldCloseDoor() {
    return GetWorld()->GetTimeSeconds() - LastDoorOpenTime >= DoorCloseDelay;
}
