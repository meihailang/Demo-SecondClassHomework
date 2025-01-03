// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeActor.h"

#include "BaseGizmos/GizmoElementArrow.h"

// Sets default values
ACubeActor::ACubeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create the static mesh component
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = CubeMesh;

	// Load the static mesh resource
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
	if (CubeMeshAsset.Succeeded())
	{
		CubeMesh->SetStaticMesh(CubeMeshAsset.Object);
	}

	// Set the material if needed
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/LevelPrototyping/Materials/MI_Solid_Blue.MI_Solid_Blue'"));
	if (MaterialAsset.Succeeded())
	{
		UMaterialInterface* CubeMaterial = MaterialAsset.Object;
		CubeMesh->SetMaterial(0, CubeMaterial);
	}
	// 初始化属性
	ShrinkFactor = 0.5f; // 缩小为原来的0.5倍
	HitCount = 0;
	CubeSocre = 1;
}

// Called when the game starts or when spawned
void ACubeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeActor::Shrink()
{
	// 增加击中次数
	HitCount++;
	UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(GetRootComponent());
	if(StaticMesh)
	{
		//缩小
		StaticMesh->SetWorldScale3D(FVector(StaticMesh->GetRelativeScale3D().X*ShrinkFactor, StaticMesh->GetRelativeScale3D().Y * ShrinkFactor, StaticMesh->GetRelativeScale3D().Z * ShrinkFactor));
		// 如果被击中两次，则销毁方块
		if (HitCount >= 2)
		{
			Destroy();
		}
	}
}

