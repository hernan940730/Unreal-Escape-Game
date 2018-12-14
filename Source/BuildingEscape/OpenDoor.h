// Copyright David Olarte 2018.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
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
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;
    
    UPROPERTY(EditAnywhere)
    float OpenAngle = -90.0f;
    
    UPROPERTY(EditAnywhere)
    float DoorCloseDelay = 1.f;
    
    UPROPERTY(EditAnywhere)
    float TriggerWeight = 50.f;
    
    AActor* Owner = nullptr;
    float LastDoorOpenTime;
    
    
    void OpenDoor();
    void CloseDoor();
    bool ShouldOpenDoor();
    bool ShouldCloseDoor();
    void OpenDoorTrigger();
    float GetTotalMassOfActorsOnPlate();
    float GetTotalMassInComponentsArray(const TArray<UPrimitiveComponent*>& Components);
};
