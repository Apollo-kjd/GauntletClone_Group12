//Copyright Epic Games, Inc. All Rights Reserved.
//Brandon

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BasePickup.generated.h"

/**
 * Base class for all pickup items in the game
 * All specific pickup items should inherit from this class
 */
UCLASS(Abstract)
class GAUNTLETCLONE_API ABasePickup : public AActor
{
	GENERATED_BODY()

public:
	//Sets default values for this actor's properties
	ABasePickup();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	//Called when something overlaps with the collision sphere
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Will be implemented by child classes to define specific pickup behavior
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	virtual void OnPickedUp(AActor* PickupActor);

	//The amount of time this pickup remains in the world before despawning (-1 for never despawn)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float LifeSpan;

	//Whether the pickup is currently active and can be collected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool bIsActive;

	//Value that represents the "importance" of this pickup (can be used for UI indicators, etc)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	int32 PickupPriority;

	//The mesh for this pickup item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PickupMesh;

	//Sphere collision component for detecting overlaps
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionSphere;

public:
	//Getters and setters
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	bool IsActive() const { return bIsActive; }

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool NewActiveState);
};