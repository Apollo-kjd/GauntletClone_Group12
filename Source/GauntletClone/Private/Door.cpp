//Copyright Epic Games, Inc. All Rights Reserved.
//Brandon

#include "Door.h"
#include "Components/BoxComponent.h"
//Include player character header here
//#include "GauntletCharacter.h"

//Sets default values
ADoor::ADoor()
{
    //Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = false;

    //Create Collider
    DoorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorCollision"));
    RootComponent = DoorCollision;

    DoorCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    DoorCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    DoorCollision->SetBoxExtent(FVector(50.0f, 5.0f, 100.0f));

    //Create and attach the mesh component
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(RootComponent);

    //Set default mesh for door
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (MeshAsset.Succeeded())
    {
        DoorMesh->SetStaticMesh(MeshAsset.Object);
        DoorMesh->SetRelativeScale3D(FVector(1.0f, 0.1f, 2.0f)); // Make it look door-shaped
    }

    //Set default values
    DoorID = 1;
    bLocked = true;
}

void ADoor::BeginPlay()
{
    Super::BeginPlay();

    //Bind the overlap event
    DoorCollision->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
}

void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    //If door is not locked, allow passage
    if (!bLocked)
    {
        //Door is already open, no need to do anything
        return;
    }

    //Check if the overlapping actor is a player
    // APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
    // if (PlayerCharacter)
    // {
    //     //Check if player has the required key
    //     if (PlayerCharacter->HasKey(DoorID))
    //     {
    //         //Try to use the key
    //         bool bKeyUsed = PlayerCharacter->UseKey(DoorID);
    //         if (bKeyUsed)
    //         {
    //             //Unlock Door
    //             SetLocked(false);
    //             OpenDoor();
    //         }
    //     }
    //     else
    //     {
    //         // PlayerCharacter->ShowMessage(TEXT("You need a key to open this door"));
    //     }
    // }

    UE_LOG(LogTemp, Display, TEXT("Player attempted to open door: DoorID=%d, Locked=%s"),
        DoorID, bLocked ? TEXT("true") : TEXT("false"));

    OnInteract(OtherActor);
}

void ADoor::OnInteract(AActor* InteractingActor)
{
    if (bLocked)
    {
        //Door is locked, check if player has key via player class
        UE_LOG(LogTemp, Display, TEXT("Door is locked. Need key with ID: %d"), DoorID);
    }
    else
    {
        //If door is unlocked
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
    DoorCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    DoorMesh->SetVisibility(false);

    UE_LOG(LogTemp, Display, TEXT("Door opened: DoorID=%d"), DoorID);
}