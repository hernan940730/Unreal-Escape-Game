// Copyright David Olarte 2018.

#include "OpenDoor.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    Owner = GetOwner();
    if (!PressurePlate) {
        UE_LOG(LogTemp, Error, TEXT("\"%s\" missing pressure plate"), *(Owner->GetName()))
    }
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    OpenDoorTrigger();
}

void UOpenDoor::OpenDoor() {
    OnOpen.Broadcast();
}

void UOpenDoor::CloseDoor() {
    OnClose.Broadcast();
}

void UOpenDoor::OpenDoorTrigger() {
    if (ShouldOpenDoor()) {
        OpenDoor();
    }
    else {
        CloseDoor();
    }
}

bool UOpenDoor::ShouldOpenDoor() {
    return GetTotalMassOfActorsOnPlate() >= TriggerWeight;
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
    if (!PressurePlate) {
        return 0.f;
    }
    TArray<UPrimitiveComponent*> OverlappingComponents;
    PressurePlate->GetOverlappingComponents(OUT OverlappingComponents);
    return GetTotalMassInComponentsArray(OverlappingComponents);
}

float UOpenDoor::GetTotalMassInComponentsArray(const TArray<UPrimitiveComponent*>& Components) {
    float TotalMass = 0.f;
    for (UPrimitiveComponent* component : Components) {
        TotalMass += component->GetMass();
    }
    return TotalMass;
}
