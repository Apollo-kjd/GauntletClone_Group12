// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasePickup.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePickup::ABasePickup()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Create components
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;

	// Set default collision responses
	CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionSphere->SetSphereRadius(50.0f);

	// Create and attach the mesh component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(RootComponent);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set default values
	bIsActive = true;
	LifeSpan = -1.0f; // By default, pickups don't despawn automatically
	RespawnTime = 0.0f; // By default, pickups don't respawn
	bShouldRespawn = false;
	PickupPriority = 1;
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();

	// Bind the overlap event
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::OnOverlapBegin);

	// Set lifespan if specified
	if (LifeSpan > 0.0f)
	{
		SetLifeSpan(LifeSpan);
	}
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Optionally add rotating or bobbing animation here
}

void ABasePickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// If pickup is not active, ignore overlap
	if (!bIsActive) return;

	// Check if the overlapping actor can pick up items
	// This would typically be more specific in a full implementation
	if (OtherActor && OtherActor != this)
	{
		// Call the OnPickedUp function that child classes will implement
		OnPickedUp(OtherActor);

		// Deactivate pickup
		SetActive(false);

		// Handle respawning if needed
		if (bShouldRespawn && RespawnTime > 0.0f)
		{
			GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ABasePickup::Respawn, RespawnTime, false);
		}
		else if (!bShouldRespawn)
		{
			// If the pickup shouldn't respawn, destroy it
			Destroy();
		}
	}
}

void ABasePickup::OnPickedUp(AActor* PickupActor)
{
	// Base implementation does nothing
	// Child classes should override this to provide specific pickup behavior
}

void ABasePickup::SetActive(bool NewActiveState)
{
	bIsActive = NewActiveState;

	// Update visibility to match active state
	SetActorHiddenInGame(!bIsActive);

	// If pickup is inactive, disable collision
	CollisionSphere->SetCollisionEnabled(bIsActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

void ABasePickup::Respawn()
{
	// Reactivate the pickup
	SetActive(true);
}