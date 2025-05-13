// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "TreasurePickup.generated.h"

/**
 * Treasure pickup that increases player score when collected
 */
UCLASS()
class GAUNTLETCLONE_API ATreasurePickup : public ABasePickup
{
    GENERATED_BODY()

public:
    // Sets default values for this pickup's properties
    ATreasurePickup();

protected:
    // Override the OnPickedUp function to implement score increase
    virtual void OnPickedUp(AActor* PickupActor) override;

    // Amount of score this treasure gives
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Treasure")
    int32 ScoreValue;
};