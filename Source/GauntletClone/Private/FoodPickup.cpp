// Copyright Epic Games, Inc. All Rights Reserved.

#include "FoodPickup.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
// Include your player character header here
// #include "GauntletCharacter.h"

AFoodPickup::AFoodPickup()
{
    // Set default values
    HealthRestoreAmount = 10.0f;

    // Set default mesh for food item
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (MeshAsset.Succeeded())
    {
        PickupMesh->SetStaticMesh(MeshAsset.Object);
        PickupMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.1f)); // Make it look like a small food item
    }

    // You would want to set a proper food mesh in your game
    // PickupMesh->SetStaticMesh(YourFoodMesh);
}

void AFoodPickup::OnPickedUp(AActor* PickupActor)
{
    // Call parent implementation
    Super::OnPickedUp(PickupActor);

    // Check if the actor is a character (check for your specific player class)
    // AYourPlayerCharacter* PlayerCharacter = Cast<AYourPlayerCharacter>(PickupActor);
    // if (PlayerCharacter)
    // {
    //     // Add health to the player
    //     PlayerCharacter->RestoreHealth(HealthRestoreAmount);
    // }

    // Generic implementation that would work with any player interface
    // In a real implementation, you'd probably have a health interface or component
    UE_LOG(LogTemp, Display, TEXT("Food pickup collected: Restoring %.1f health"), HealthRestoreAmount);

    // For now, we'll just log that health would be restored
    // Uncomment and implement the proper player character interaction once you have that class
}