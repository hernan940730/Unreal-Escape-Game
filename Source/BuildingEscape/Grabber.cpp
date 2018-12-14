// Copyright David Olarte 2018.

#include "Grabber.h"
#include "Engine/Public/DrawDebugHelpers.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay() {
	Super::BeginPlay();
    FindPhysicsHandleComponent();
    SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    UpdateGrabComponentLocation();
}

void UGrabber::FindPhysicsHandleComponent() {
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (!PhysicsHandle) {
        UE_LOG(LogTemp, Error, TEXT("Actor \"%s\" missing PhysicsHandleComponent"), *(GetOwner()->GetName()))
    }
}

void UGrabber::SetupInputComponent() {
    Input = GetOwner()->InputComponent;
    if (Input) {
        Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("Actor \"%s\" missing InputComponent"), *(GetOwner()->GetName()));
    }
}

void UGrabber::Grab() {
    FHitResult Hit = GetFirstPhysicsBodyInReach();
    UPrimitiveComponent* HitComponent = Hit.GetComponent();
    if (HitComponent) {
        PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitComponent->GetOwner()->GetActorLocation(), FRotator::ZeroRotator);
    }
}

void UGrabber::Release() {
    PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
    LineTrace PlayerViewPointLineTrace = GetPlayerViewPointLineTrace();
    return GetFirstPhysicsBodyInLineTrace(PlayerViewPointLineTrace);
}

const LineTrace UGrabber::GetPlayerViewPointLineTrace() {
    LineTrace PlayerViewPointLineTrace;
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
    PlayerViewPointLineTrace.Begin = PlayerViewPointLocation;
    PlayerViewPointLineTrace.End = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
    return PlayerViewPointLineTrace;
}

const FHitResult UGrabber::GetFirstPhysicsBodyInLineTrace(const LineTrace& MyLineTrace){
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(
                                            Hit,
                                            MyLineTrace.Begin,
                                            MyLineTrace.End,
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            FCollisionQueryParams(NAME_None, false, GetOwner()));
    return Hit;
}

void UGrabber::UpdateGrabComponentLocation() {
    if (PhysicsHandle->GetGrabbedComponent()) {
        PhysicsHandle->SetTargetLocation(GetPlayerViewPointLineTrace().End);
    }
}
