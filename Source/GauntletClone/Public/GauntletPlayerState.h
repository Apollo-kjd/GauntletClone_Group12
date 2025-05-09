// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GauntletPlayerState.generated.h"

/**
 * Player State class for the Gauntlet clone
 * Tracks player stats like score, health, keys, etc.
 */
UCLASS()
class GAUNTLETCLONE_API AGauntletPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    AGauntletPlayerState();

    // Add points to the player's score with optional score multiplier
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddPoints(int32 Points, float ScoreMultiplier = 1.0f);

    // Get the current treasure collection count
    UFUNCTION(BlueprintPure, Category = "Score")
    int32 GetTreasureCount() const { return TreasureCount; }

    // Get the current key count
    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetKeyCount() const { return KeyCount; }

    // Add keys to inventory
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddKeys(int32 Amount);

    // Use a key (returns true if a key was available)
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool UseKey();

protected:
    // Number of treasures collected
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score", Replicated)
    int32 TreasureCount;

    // Number of keys in possession
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", Replicated)
    int32 KeyCount;

    // High score for this player (persistent between levels)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int32 HighScore;

public:
    // Override GetLifetimeReplicatedProps to setup property replication
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};