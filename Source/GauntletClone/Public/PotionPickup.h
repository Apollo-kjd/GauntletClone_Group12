// Copyright Epic Games, Inc. All Rights Reserved.
//Brandon

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "PotionPickup.generated.h"

/**
 * Potion pickup that eliminates all enemies on screen when collected
 */
UCLASS()
class GAUNTLETCLONE_API APotionPickup : public ABasePickup
{
    GENERATED_BODY()

public:
    //Sets default values for this pickup's properties
    APotionPickup();

protected:
    //Override the OnPickedUp function to implement enemy elimination
    virtual void OnPickedUp(AActor* PickupActor) override;

    //Tag for enemies that should be affected by this potion
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Potion")
    FName EnemyTag;

    //Range within which enemies will be affected (0 means all enemies in level)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Potion")
    float EffectRange;
};