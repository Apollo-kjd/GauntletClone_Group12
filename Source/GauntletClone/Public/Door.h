//Copyright Epic Games, Inc. All Rights Reserved.
//Brandon

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

/**
 * Door actor that can be unlocked with keys
 */
UCLASS()
class GAUNTLETCLONE_API ADoor : public AActor
{
    GENERATED_BODY()

public:
    //Sets default values for this actor's properties
    ADoor();

protected:

    virtual void BeginPlay() override;

    //Door mesh component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* DoorMesh;

    //Collision box for the door
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UBoxComponent* DoorCollision;

    //ID that determines which key can open this door
    //Match this with KeyID in KeyPickup
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    int32 DoorID;

    //Whether the door is currently locked
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    bool bLocked;

    // Function to handle player interaction with the door
    UFUNCTION()
    void OnInteract(AActor* InteractingActor);

    // Function called when something overlaps with the door collision
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // Functions to open and close the door
    UFUNCTION(BlueprintCallable, Category = "Door")
    void OpenDoor();

public:
    // Function to try unlocking the door with a key
    UFUNCTION(BlueprintCallable, Category = "Door")
    bool TryUnlock(int32 KeyID);

    // Getters and setters
    UFUNCTION(BlueprintCallable, Category = "Door")
    bool IsLocked() const { return bLocked; }

    UFUNCTION(BlueprintCallable, Category = "Door")
    void SetLocked(bool NewLockedState);
};