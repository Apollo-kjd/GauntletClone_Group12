// Copyright Epic Games, Inc. All Rights Reserved.

#include "Door.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
// Include player character header here
// #include "GauntletCharacter.h"

// Sets default values
ADoor::ADoor()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = false;

    // Create components
    DoorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorCollision"));
    RootComponent = DoorCollision;

    DoorCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    DoorCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    DoorCollision->SetBoxExtent(FVector(50.0f, 5.0f, 100.0f));

    // Create and attach the mesh component
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(RootComponent);

    // Set default mesh for door
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (MeshAsset.Succeeded())
    {
        DoorMesh->SetStaticMesh(MeshAsset.Object);
        DoorMesh->SetRelativeScale3D(FVector(1.0f, 0.1f, 2.0f)); // Make it look door-shaped
    }

    // You would want to set a proper door mesh in your game
    // DoorMesh->SetStaticMesh(YourDoorMesh);

    // Set default values
    DoorID = 1;
    bLocked = true;
    bAutoClose = false;
    AutoCloseDelay = 5.0f;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
    Super::BeginPlay();

    // Bind the overlap event
    DoorCollision->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
}

void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    // If door is not locked, allow passage
    if (!bLocked)
    {
        // Door is already open, no need to do anything
        return;
    }

    // Check if the overlapping actor is a player
    // AYourPlayerCharacter* PlayerCharacter = Cast<AYourPlayerCharacter>(OtherActor);
    // if (PlayerCharacter)
    // {
    //     // Check if player has the required key
    //     if (PlayerCharacter->HasKey(DoorID))
    //     {
    //         // Try to use the key
    //         bool bKeyUsed = PlayerCharacter->UseKey(DoorID);
    //         if (bKeyUsed)
    //         {
    //             // Unlock and open the door
    //             SetLocked(false);
    //             OpenDoor();
    //         }
    //     }
    //     else
    //     {
    //         // Player doesn't have the key, maybe show a message
    //         // PlayerCharacter->ShowMessage(TEXT("You need a key to open this door"));
    //     }
    // }

    // For now, we'll just log that a player tried to use the door
    UE_LOG(LogTemp, Display, TEXT("Player attempted to open door: DoorID=%d, Locked=%s"),
        DoorID, bLocked ? TEXT("true") : TEXT("false"));

    // You would implement proper player-door interaction here
    OnInteract(OtherActor);
}

void ADoor::OnInteract(AActor* InteractingActor)
{
    // This function would be called when a player interacts with the door
    // You could implement this to show a "Need key" message or similar

    if (bLocked)
    {
        // Door is locked, check if player has key via your own player class
        // For demo, let's just print a message
        UE_LOG(LogTemp, Display, TEXT("Door is locked. Need key with ID: %d"), DoorID);
    }
    else
    {
        // Door is unlocked, open it
        OpenDoor();
    }
}

bool ADoor::TryUnlock(int32 KeyID)
{
    // Check if the key matches the door
    if (KeyID == DoorID || KeyID == 0)  // KeyID 0 is a master key
    {
        SetLocked(false);
        return true;
    }
    return false;
}

void ADoor::SetLocked(bool NewLockedState)
{
    bLocked = NewLockedState;
}

void ADoor::OpenDoor()
{
    // Implementation for opening the door
    // This could be an animation, moving the door, disabling collision, etc.
    DoorCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    DoorMesh->SetVisibility(false);

    UE_LOG(LogTemp, Display, TEXT("Door opened: DoorID=%d"), DoorID);

    // If auto close is enabled, set timer
    if (bAutoClose)
    {
        GetWorldTimerManager().SetTimer(
            AutoCloseTimerHandle,
            this,
            &ADoor::CloseDoor,
            AutoCloseDelay,
            false
        );
    }
}

void ADoor::CloseDoor()
{
    // Implementation for closing the door
    // Re-enable collision and visibility
    DoorCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    DoorMesh->SetVisibility(true);

    UE_LOG(LogTemp, Display, TEXT("Door closed: DoorID=%d"), DoorID);
}