// Implementation of base class for all pickup items in Gauntlet game

#include "GauntletPickupBase.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
// Include your character class
#include "GauntletCharacter.h"

UGauntletPickupBase::UGauntletPickupBase()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Setup network replication
    bReplicates = true;

    // Create and setup sphere collision component
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    SetRootComponent(CollisionComponent);
    CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    CollisionComponent->SetSphereRadius(50.0f);

    // Create and setup the static mesh component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // Set default values
    PickupType = EPickupType::PT_Treasure;
    PickupValue = 10;
    bShouldRespawn = true;
    RespawnTime = 30.0f;
    bIsActive = true;
}

void UGauntletPickupBase::BeginPlay()
{
    Super::BeginPlay();

    // Register overlap event
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UGauntletPickupBase::OnOverlapBegin);
}

void UGauntletPickupBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Optional: Add rotating or bobbing effect for visual appeal
    if (bIsActive)
    {
        // Example: Rotate the pickup item
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += DeltaTime * 60.0f; // Rotate at 60 degrees per second
        SetActorRotation(NewRotation);
    }
}

void UGauntletPickupBase::OnPickedUp_Implementation(AGauntletCharacter* Character)
{
    if (Character && bIsActive)
    {
        // Apply the pickup's effect
        ApplyPickupEffect(Character);

        // Play sound if set
        if (PickupSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
        }

        // Deactivate the pickup
        DeactivatePickup();

        // Schedule respawn if enabled
        if (bShouldRespawn)
        {
            GetWorldTimerManager().SetTimer(
                RespawnTimerHandle,
                this,
                &UGauntletPickupBase::ReactivatePickup,
                RespawnTime,
                false
            );
        }
    }
}

//Custom Effects for Each Pickup
void UGauntletPickupBase::ApplyPickupEffect_Implementation(AGauntletCharacter* Character)
{
    // Base implementation does nothing - override in derived classes
    // Example: Character->AddHealth(PickupValue);
}

//Handles Pickup Deactivation
void UGauntletPickupBase::DeactivatePickup()
{
    bIsActive = false;

    // Hide the pickup
    SetActorHiddenInGame(true);

    // Disable collision
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // Stop any particle effects
    if (EffectComponent)
    {
        EffectComponent->DeactivateSystem();
    }
}

void UGauntletPickupBase::ReactivatePickup()
{
    bIsActive = true;

    // Show the pickup
    SetActorHiddenInGame(false);

    // Enable collision
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    // Restart any particle effects
    if (EffectComponent)
    {
        EffectComponent->ActivateSystem();
    }
}

void UGauntletPickupBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the overlapping actor is a player character
    if (bIsActive && OtherActor)
    {
        AGauntletCharacter* Character = Cast<AGauntletCharacter>(OtherActor);
        if (Character)
        {
            OnPickedUp(Character);
        }
    }
}

void UGauntletPickupBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Replicate the active state so all clients know when a pickup is available
    DOREPLIFETIME(UGauntletPickupBase, bIsActive);
}