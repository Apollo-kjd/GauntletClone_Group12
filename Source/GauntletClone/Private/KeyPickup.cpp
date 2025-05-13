// Copyright Epic Games, Inc. All Rights Reserved.

#include "KeyPickup.h"
#include "Kismet/GameplayStatics.h"
// Include your player character header here
// #include "GauntletCharacter.h"

AKeyPickup::AKeyPickup()
{
    // Set default values
    KeyID = 1;
    bSingleUse = true;
    KeyColor = FLinearColor::Yellow; // Default key color

    // Set default mesh for key
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cone.Cone"));
    if (MeshAsset.Succeeded())
    {
        PickupMesh->SetStaticMesh(MeshAsset.Object);
        PickupMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.8f)); // Make it look key-shaped
        PickupMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f)); // Rotate to stand upright
    }

    // You would want to set a proper key mesh in your game
    // PickupMesh->SetStaticMesh(YourKeyMesh);

    // Keys are important pickups
    PickupPriority = 2; // Higher priority for UI indicators
}

void AKeyPickup::OnPickedUp(AActor* PickupActor)
{
    // Call parent implementation
    Super::OnPickedUp(PickupActor);

    // Check if the actor is a character (you might want to check for your specific player class)
    // AYourPlayerCharacter* PlayerCharacter = Cast<AYourPlayerCharacter>(PickupActor);
    // if (PlayerCharacter)
    // {
    //     // Add key to player's inventory
    //     PlayerCharacter->AddKey(KeyID, bSingleUse);
    // }

    // For now, we'll just log that a key was collected
    UE_LOG(LogTemp, Display, TEXT("Key pickup collected: KeyID=%d, SingleUse=%s"),
        KeyID, bSingleUse ? TEXT("true") : TEXT("false"));

    // You could also broadcast an event that doors can listen to
    // This is an alternative to having the player store keys
    // FString EventName = FString::Printf(TEXT("KeyCollected_%d"), KeyID);
    // UGameplayStatics::BroadcastDynamicEvent(GetWorld(), FName(*EventName), GetInstigator());
}