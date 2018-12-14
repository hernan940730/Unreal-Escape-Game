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
    
    UPROPERTY(EditAnywhere)
    float Reach = 100.f;
    
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UInputComponent* Input = nullptr;
    
    void FindPhysicsHandleComponent();
    void SetupInputComponent();
    void Grab();
    void Release();
    const FHitResult GetFirstPhysicsBodyInReach();
    const LineTrace GetPlayerViewPointLineTrace();
    const FHitResult GetFirstPhysicsBodyInLineTrace(const LineTrace& MyLineTrace);
    void UpdateGrabComponentLocation();
};


struct LineTrace {
    FVector Begin;
    FVector End;
};
