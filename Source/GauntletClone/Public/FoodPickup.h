//Copyright Epic Games, Inc. All Rights Reserved.
//Brandon

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "FoodPickup.generated.h"

/**
 * Food pickup that restores player health when collected
 */
UCLASS()
class GAUNTLETCLONE_API AFoodPickup : public ABasePickup
{
    GENERATED_BODY()

public:
    //Sets default values for this pickup's properties
    AFoodPickup();

protected:
    //Override the OnPickedUp function to implement health restoration
    virtual void OnPickedUp(AActor* PickupActor) override;

    //Amount of health this food item restores
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Food")
    float HealthRestoreAmount;
};