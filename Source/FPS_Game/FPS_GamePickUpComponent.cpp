// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_GamePickUpComponent.h"

UFPS_GamePickUpComponent::UFPS_GamePickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UFPS_GamePickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UFPS_GamePickUpComponent::OnSphereBeginOverlap);
}

void UFPS_GamePickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AFPS_GameCharacter* Character = Cast<AFPS_GameCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
