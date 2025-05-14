// Copyright Epic Games, Inc. All Rights Reserved.
//Brandon

#include "PotionPickup.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
// Include enemy base class header here
// #include "GauntletEnemy.h"

APotionPickup::APotionPickup()
{
    // Set default values
    EnemyTag = FName("Enemy");
    EffectRange = 0.0f; // 0 means affect all enemies in level

    // Set default mesh for potion
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (MeshAsset.Succeeded())
    {
        PickupMesh->SetStaticMesh(MeshAsset.Object);
        PickupMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.6f));
    }
    PickupPriority = 3; // Higher priority for UI indicators
}

void APotionPickup::OnPickedUp(AActor* PickupActor)
{
    //Call parent implementation
    Super::OnPickedUp(PickupActor);

    //Get all enemies in the level with the specified tag
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), EnemyTag, FoundEnemies);

    //Filter by distance
    if (EffectRange > 0.0f)
    {
        TArray<AActor*> InRangeEnemies;
        FVector PickupLocation = GetActorLocation();

        for (AActor* Enemy : FoundEnemies)
        {
            if (Enemy)
            {
                float Distance = FVector::Dist(PickupLocation, Enemy->GetActorLocation());
                if (Distance <= EffectRange)
                {
                    InRangeEnemies.Add(Enemy);
                }
            }
        }

        //Replace the original array with filtered results
        FoundEnemies = InRangeEnemies;
    }

    //Eliminate all found enemies
    int32 EliminatedCount = 0;
    for (AActor* Enemy : FoundEnemies)
    {
        UE_LOG(LogTemp, Display, TEXT("Potion pickup collected: Eliminated %d enemies"), EliminatedCount);
        if (Enemy)
        {
            //Call enemy class
            // AGauntletEnemy* GauntletEnemy = Cast<AGauntletEnemy>(Enemy);
            // if (GauntletEnemy)
            // {
            //     GauntletEnemy->Die(true); // true for potion death, which might have special effects
            // }

            //Destroy Enemies
            Enemy->Destroy();
            EliminatedCount++;
        }
    }
}