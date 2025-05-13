// Copyright Epic Games, Inc. All Rights Reserved.

#include "TreasurePickup.h"
#include "Kismet/GameplayStatics.h"
// Include your player character header here
// #include "GauntletCharacter.h"
// Include your game mode header here
// #include "GauntletGameMode.h"

ATreasurePickup::ATreasurePickup()
{
    // Set default values
    ScoreValue = 100;

    // Set default mesh for treasure
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
    if (MeshAsset.Succeeded())
    {
        PickupMesh->SetStaticMesh(MeshAsset.Object);
        PickupMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.1f)); // Make it look like a coin
    }

    // You would want to set a proper treasure mesh in your game
    // PickupMesh->SetStaticMesh(YourTreasureMesh);
}

void ATreasurePickup::OnPickedUp(AActor* PickupActor)
{
    // Call parent implementation
    Super::OnPickedUp(PickupActor);

    // Check if the actor is a character (you might want to check for your specific player class)
    // AYourPlayerCharacter* PlayerCharacter = Cast<AYourPlayerCharacter>(PickupActor);
    // if (PlayerCharacter)
    // {
    //     // Add score to the player
    //     PlayerCharacter->AddScore(ScoreValue);
    // }

    // Alternative implementation using GameMode to track score
    // AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
    // AGauntletGameMode* GauntletGameMode = Cast<AGauntletGameMode>(GameMode);
    // if (GauntletGameMode)
    // {
    //     GauntletGameMode->AddScore(ScoreValue);
    // }

    UE_LOG(LogTemp, Display, TEXT("Treasure pickup collected: Adding %d score"), ScoreValue);

    // For now, we'll just log that score would be added
    // Uncomment and implement the proper score tracking once you have those classes
}