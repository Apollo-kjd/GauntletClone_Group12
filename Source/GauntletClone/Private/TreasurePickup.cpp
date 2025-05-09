// Copyright Epic Games, Inc. All Rights Reserved.

#include "TreasurePickup.h"
#include "Kismet/GameplayStatics.h"
//#include "GauntletCharacter.h" // You'll need to create or modify this to handle points
#include "GauntletPlayerState.h" // You'll need to create this to handle player score

ATreasurePickup::ATreasurePickup()
{
    // Set default values
    TreasureType = ETreasureType::Gold;
    PointValue = 100;
    bAutoSetAppearance = true;

    // Set this pickup to rotate slowly
    PickupMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    PickupMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

    // Configure the base pickup settings
    bShouldRespawn = true;
    RespawnTime = 30.0f;
    PickupPriority = 5; // Treasure is relatively important

    // Make the collision sphere smaller for treasure
    CollisionSphere->SetSphereRadius(40.0f);

    // By default, treasure pickups will be destroyed when picked up
    // This can be changed in BP editor for specific treasures that should respawn
}

void ATreasurePickup::BeginPlay()
{
    Super::BeginPlay();

    // Set the appearance based on the treasure type if auto-appearance is enabled
    if (bAutoSetAppearance)
    {
        UpdateAppearanceForType();
    }
}

void ATreasurePickup::OnPickedUp(AActor* PickupActor)
{
    Super::OnPickedUp(PickupActor);

    // Try to cast the actor to a player character
    // Note: You'll need to create GauntletCharacter class or use your own player class
    //AGauntletCharacter* PlayerCharacter = Cast<AGauntletCharacter>(PickupActor);

    /*
    if (PlayerCharacter)
    {
        // Add points to the player's score
        // This assumes you have a PlayerState class that handles the score
        APlayerState* PS = PlayerCharacter->GetPlayerState();
        if (PS)
        {
            // Try to cast to your custom player state if you have one
            AGauntletPlayerState* GauntletPS = Cast<AGauntletPlayerState>(PS);
            if (GauntletPS)
            {
                // Call a custom function to add points
                GauntletPS->AddPoints(PointValue);
            }
            else
            {
                // Fallback to using the standard score
                PS->SetScore(PS->GetScore() + PointValue);
            }
        }
    }*/
}

void ATreasurePickup::SetTreasureType(ETreasureType NewType)
{
    TreasureType = NewType;

    // Update point value based on type
    switch (TreasureType)
    {
    case ETreasureType::Gold:
        PointValue = 100;
        break;
    case ETreasureType::Silver:
        PointValue = 50;
        break;
    case ETreasureType::Bronze:
        PointValue = 25;
        break;
    case ETreasureType::Gem:
        PointValue = 200;
        break;
    case ETreasureType::Chest:
        PointValue = 500;
        break;
    default:
        PointValue = 10;
        break;
    }

    // Update the appearance if auto-appearance is enabled
    if (bAutoSetAppearance)
    {
        UpdateAppearanceForType();
    }
}

void ATreasurePickup::UpdateAppearanceForType()
{
    // This function would be implemented to set the appropriate mesh and materials
    // based on the treasure type.
    // In a real implementation, you might load different static meshes and materials
    // For this example, we'll just change the color to represent different treasures

    // Define colors for different treasure types
    FLinearColor Color;
    switch (TreasureType)
    {
    case ETreasureType::Gold:
        Color = FLinearColor(1.0f, 0.8f, 0.0f); // Gold
        break;
    case ETreasureType::Silver:
        Color = FLinearColor(0.75f, 0.75f, 0.75f); // Silver
        break;
    case ETreasureType::Bronze:
        Color = FLinearColor(0.8f, 0.5f, 0.2f); // Bronze
        break;
    case ETreasureType::Gem:
        Color = FLinearColor(0.0f, 0.5f, 1.0f); // Blue gem
        break;
    case ETreasureType::Chest:
        Color = FLinearColor(0.5f, 0.25f, 0.0f); // Brown chest
        break;
    default:
        Color = FLinearColor::White;
        break;
    }

    // Create a dynamic material instance
    if (PickupMesh && PickupMesh->GetStaticMesh())
    {
        UMaterialInterface* BaseMaterial = PickupMesh->GetMaterial(0);
        if (BaseMaterial)
        {
            UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
            if (DynMaterial)
            {
                // Set the color parameter (assuming your material has a Color parameter)
                DynMaterial->SetVectorParameterValue(TEXT("Color"), Color);
                PickupMesh->SetMaterial(0, DynMaterial);
            }
        }
    }
}