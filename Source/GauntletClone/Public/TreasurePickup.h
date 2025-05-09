// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "TreasurePickup.generated.h"

// Enum for different treasure types
UENUM(BlueprintType)
enum class ETreasureType : uint8
{
    None    UMETA(DisplayName = "None"),
    Gold    UMETA(DisplayName = "Gold"),
    Silver  UMETA(DisplayName = "Silver"),
    Bronze  UMETA(DisplayName = "Bronze"),
    Gem     UMETA(DisplayName = "Gem"),
    Chest   UMETA(DisplayName = "Chest")
};

/**
 * Treasure pickup class for Gauntlet-style game
 * Represents collectable treasures that give points to the player
 */
UCLASS()
class GAUNTLETCLONE_API ATreasurePickup : public ABasePickup
{
    GENERATED_BODY()

public:
    // Constructor
    ATreasurePickup();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    // Override the base pickup behavior
    virtual void OnPickedUp(AActor* PickupActor) override;

    // The type of treasure this pickup represents
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Treasure")
    ETreasureType TreasureType;

    // Point value awarded when collected
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Treasure")
    int32 PointValue;

    // Whether this treasure automatically sets its appearance based on TreasureType
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Treasure")
    bool bAutoSetAppearance;

public:
    // Get the point value of this treasure
    UFUNCTION(BlueprintPure, Category = "Treasure")
    int32 GetPointValue() const { return PointValue; }

    // Get the treasure type
    UFUNCTION(BlueprintPure, Category = "Treasure")
    ETreasureType GetTreasureType() const { return TreasureType; }

    // Set the treasure type and update appearance if auto appearance is enabled
    UFUNCTION(BlueprintCallable, Category = "Treasure")
    void SetTreasureType(ETreasureType NewType);

private:
    // Updates the appearance based on the current treasure type
    void UpdateAppearanceForType();
};