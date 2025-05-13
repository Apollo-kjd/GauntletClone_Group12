// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "KeyPickup.generated.h"

/**
 * Key pickup that allows the player to unlock doors when collected
 */
UCLASS()
class GAUNTLETCLONE_API AKeyPickup : public ABasePickup
{
    GENERATED_BODY()

public:
    // Sets default values for this pickup's properties
    AKeyPickup();

protected:
    // Override the OnPickedUp function to implement key collection
    virtual void OnPickedUp(AActor* PickupActor) override;

    // Key ID to identify which door(s) this key can open
    // Use 0 for a master key that opens all doors
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Key")
    int32 KeyID;

    // Whether this key disappears after a single use
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Key")
    bool bSingleUse;

    // Optional color to visually distinguish different key types
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Key")
    FLinearColor KeyColor;
};