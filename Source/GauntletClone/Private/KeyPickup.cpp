//Copyright Epic Games, Inc. All Rights Reserved.
//Brandon

#include "KeyPickup.h"
#include "Kismet/GameplayStatics.h"
//#Include player character header here
//#include "GauntletCharacter.h"

AKeyPickup::AKeyPickup()
{
    //Set default values
    KeyID = 1;
    bSingleUse = true;

    //Set default mesh for key
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cone.Cone"));
    if (MeshAsset.Succeeded())
    {
        PickupMesh->SetStaticMesh(MeshAsset.Object);
        PickupMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.8f));
        PickupMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
    }
    PickupPriority = 2; //Higher priority for UI indicators
}

void AKeyPickup::OnPickedUp(AActor* PickupActor)
{
    //Call parent implementation
    Super::OnPickedUp(PickupActor);

    UE_LOG(LogTemp, Display, TEXT("Key pickup collected: KeyID=%d, SingleUse=%s"),
        KeyID, bSingleUse ? TEXT("true") : TEXT("false"));

    //Check for your specific player class
    // APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PickupActor);
    // if (PlayerCharacter)
    // {
    //     // Add key to player's inventory
    //     PlayerCharacter->AddKey(KeyID, bSingleUse);
    // }
}