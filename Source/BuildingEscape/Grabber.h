// Copyright David Olarte 2018.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


struct LineTrace;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    
    /// Distance in Centimeters of Reach to grab an object
    UPROPERTY(EditAnywhere)
    float Reach = 100.f;
    
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UInputComponent* Input = nullptr;
    
    /// Get physics handle component of player
    void FindPhysicsHandleComponent();
    
    /// Setup functions asociated with grab keys
    void SetupInputComponent();
    
    /// Grab an object
    void Grab();
    
    /// Release an object
    void Release();
    
    /// Get Hit Result of physics Body in reach
    const FHitResult GetFirstPhysicsBodyInReach();
    
    /// Get Line Trace of Player view
    const LineTrace GetPlayerViewLineTrace();
    
    /// Get Hit Result of physics body in a line trace
    const FHitResult GetFirstPhysicsBodyInLineTrace(const LineTrace& MyLineTrace);
    
    /// Update position of component that is grabbed (if one)
    void UpdateGrabComponentLocation();
};


struct LineTrace {
    FVector Begin;
    FVector End;
};
