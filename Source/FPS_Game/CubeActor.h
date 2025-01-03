// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/MapErrors.h"
#include "CubeActor.generated.h"

UCLASS()
class FPS_GAME_API ACubeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeActor();
	UStaticMeshComponent* GetStaticMeshComponent(){return CubeMesh;};
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void Shrink();
	int32 CubeSocre;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="CubeActor");
	UStaticMeshComponent* CubeMesh;

private:
	UPROPERTY(EditAnywhere,Category="Physics")
	float ShrinkFactor;    //缩放因子
	UPROPERTY(EditAnywhere,Category="Physics")
	int32 HitCount;        // 被击中次数
};
