// Copyright Epic Games, Inc. All Rights Reserved.

#include "GauntletPlayerState.h"
#include "Net/UnrealNetwork.h"

AGauntletPlayerState::AGauntletPlayerState()
{
    // Set default values
    TreasureCount = 0;
    KeyCount = 0;
    HighScore = 0;

    // Enable replication
    bReplicates = true;
}

void AGauntletPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Register properties for replication
    DOREPLIFETIME(AGauntletPlayerState, TreasureCount);
    DOREPLIFETIME(AGauntletPlayerState, KeyCount);
}

void AGauntletPlayerState::AddPoints(int32 Points, float ScoreMultiplier)
{
    if (Points <= 0)
    {
        return;
    }

    // Calculate the actual points to add with the multiplier
    int32 PointsToAdd = FMath::RoundToInt(Points * ScoreMultiplier);

    // Add to score using the base class function
    SetScore(GetScore() + PointsToAdd);

    // Increment treasure count
    TreasureCount++;

    // Update high score if needed
    if (GetScore() > HighScore)
    {
        HighScore = GetScore();
    }
}

void AGauntletPlayerState::AddKeys(int32 Amount)
{
    if (Amount <= 0)
    {
        return;
    }

    KeyCount += Amount;
}

bool AGauntletPlayerState::UseKey()
{
    if (KeyCount > 0)
    {
        KeyCount--;
        return true;
    }

    return false;
}