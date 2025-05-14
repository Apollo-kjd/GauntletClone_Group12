// Copyright Epic Games, Inc. All Rights Reserved.
//Brandon

#include "FoodPickup.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
//Include player character header here
//#include "GauntletCharacter.h"

AFoodPickup::AFoodPickup()
{
    //Set default values
    HealthRestoreAmount = 10.0f;

    //Set mesh for food item
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (MeshAsset.Succeeded())
    {
        PickupMesh->SetStaticMesh(MeshAsset.Object);
        PickupMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.1f)); // Make it look like a small food item
    }
}

void AFoodPickup::OnPickedUp(AActor* PickupActor)
{
    //Call parent implementation
    Super::OnPickedUp(PickupActor);
    UE_LOG(LogTemp, Display, TEXT("Food pickup collected: Restoring %.1f health"), HealthRestoreAmount);

    // Check for specific player class
    // AYourPlayerCharacter* PlayerCharacter = Cast<AYourPlayerCharacter>(PickupActor);
    // if (PlayerCharacter)
    // {
    //     PlayerCharacter->RestoreHealth(HealthRestoreAmount);
    // }
}