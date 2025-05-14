//Copyright Epic Games, Inc. All Rights Reserved.
//Brandon

#include "BasePickup.h"
#include "Kismet/GameplayStatics.h"

//Sets default values and Creates Mesh
ABasePickup::ABasePickup()
{
	//Sets this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	//Creates Collision Sphere
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;

	//Set default collision responses
	CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionSphere->SetSphereRadius(50.0f);

	//Creates and attaches the mesh component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(RootComponent);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set default values
	bIsActive = true;
	LifeSpan = -1.0f;
	PickupPriority = 1;
}

void ABasePickup::BeginPlay()
{
	Super::BeginPlay();

	//Bind overlap event
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::OnOverlapBegin);

	//Set lifespan
	if (LifeSpan > 0.0f)
	{
		SetLifeSpan(LifeSpan);
	}
}

void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Basic Item Functionality
void ABasePickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	//If pickup is not active, ignore overlap
	if (!bIsActive) return;

	//Check if the overlapping actor can pick up items
	if (OtherActor && OtherActor != this)
	{
		OnPickedUp(OtherActor);
		SetActive(false);
		Destroy();
	}
}

void ABasePickup::OnPickedUp(AActor* PickupActor)
{
	//Child classes should override this to provide specific pickup behavior
}

//Handles Active Status
void ABasePickup::SetActive(bool NewActiveState)
{
	bIsActive = NewActiveState;

	//Update visibility to match active state
	SetActorHiddenInGame(!bIsActive);

	//If pickup is inactive, disable collision
	CollisionSphere->SetCollisionEnabled(bIsActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}