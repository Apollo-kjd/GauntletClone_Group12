// Base class for all pickup items in Gauntlet game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GauntletPickupBase.generated.h"

// Forward declaration
class AGauntletCharacter;

UENUM(BlueprintType)
enum class EPickupType : uint8
{
    PT_Key UMETA(DisplayName = "Key"),
    PT_Food UMETA(DisplayName = "Food"),
    PT_Potion UMETA(DisplayName = "Potion"),
    PT_Treasure UMETA(DisplayName = "Treasure"),
    PT_Special UMETA(DisplayName = "Special Item")
};

UCLASS(Abstract, BlueprintType, Blueprintable)
class GauntletClone_API UGauntletPickupBase : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    UGauntletPickupBase();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Collision component for triggering pickup
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* CollisionComponent;

    // Visual representation of the pickup
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshComponent;

    // Optional particle system for pickup effects
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UParticleSystemComponent* EffectComponent;

    // Sound to play when picked up
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundBase* PickupSound;

    // Type of pickup item
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Properties")
    EPickupType PickupType;

    // Value of the pickup (health points, score, etc.)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Properties")
    int32 PickupValue;

    // Should this pickup respawn after being collected?
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Properties")
    bool bShouldRespawn;

    // Time until respawn after being collected (if respawnable)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Properties", meta = (EditCondition = "bShouldRespawn", ClampMin = "0.0"))
    float RespawnTime;

    // Is this pickup currently active/available?
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Pickup Properties")
    bool bIsActive;

    // Timer handle for respawning
    FTimerHandle RespawnTimerHandle;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function called when player collects this pickup
    UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
    void OnPickedUp(AGauntletCharacter* Character);
    virtual void OnPickedUp_Implementation(AGauntletCharacter* Character);

    // Apply the pickup's effect to the character
    UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
    void ApplyPickupEffect(AGauntletCharacter* Character);
    virtual void ApplyPickupEffect_Implementation(AGauntletCharacter* Character);

    // Deactivate the pickup after being collected
    UFUNCTION(BlueprintCallable, Category = "Pickup")
    virtual void DeactivatePickup();

    // Reactivate the pickup (used for respawning)
    UFUNCTION(BlueprintCallable, Category = "Pickup")
    virtual void ReactivatePickup();

    // Overlap begin event
    UFUNCTION()
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // Getters
    FORCEINLINE EPickupType GetPickupType() const { return PickupType; }
    FORCEINLINE int32 GetPickupValue() const { return PickupValue; }
    FORCEINLINE bool IsActive() const { return bIsActive; }

    // For network replication
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};