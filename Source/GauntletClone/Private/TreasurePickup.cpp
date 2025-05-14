//Copyright Epic Games, Inc. All Rights Reserved.
//Brandon

#include "TreasurePickup.h"
#include "Kismet/GameplayStatics.h"
//Include player character header here
//#include "GauntletCharacter.h"

ATreasurePickup::ATreasurePickup()
{
    //Set default values
    ScoreValue = 100;

    //Set default mesh for treasure
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
    if (MeshAsset.Succeeded())
    {
        PickupMesh->SetStaticMesh(MeshAsset.Object);
        PickupMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.1f)); // Make it look like a coin
    }
}

void ATreasurePickup::OnPickedUp(AActor* PickupActor)
{
    //Call parent implementation
    Super::OnPickedUp(PickupActor);
    UE_LOG(LogTemp, Display, TEXT("Treasure pickup collected: Adding %d score"), ScoreValue);

    //Check for specific player class
    // AYourPlayerCharacter* PlayerCharacter = Cast<AYourPlayerCharacter>(PickupActor);
    // if (PlayerCharacter)
    // {
    //     // Add score to the player
    //     PlayerCharacter->AddScore(ScoreValue);
    // }
}