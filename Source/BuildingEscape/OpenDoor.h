// Copyright David Olarte 2018.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorEvent);

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
    float TriggerWeight = 50.f;
    
    UPROPERTY(BlueprintAssignable)
    FOnDoorEvent OnOpen;
    
    UPROPERTY(BlueprintAssignable)
    FOnDoorEvent OnClose;
    
    AActor* Owner = nullptr;
    
    void OpenDoor();
    void CloseDoor();
    bool ShouldOpenDoor();
    void OpenDoorTrigger();
    float GetTotalMassOfActorsOnPlate();
    float GetTotalMassInComponentsArray(const TArray<UPrimitiveComponent*>& Components);
};
