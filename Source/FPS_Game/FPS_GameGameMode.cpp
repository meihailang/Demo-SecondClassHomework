// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_GameGameMode.h"

#include "CubeActor.h"
#include "FPS_GameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPS_GameGameMode::AFPS_GameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	RandomlyChangeSomeCubeActorMaterials();
}

void AFPS_GameGameMode::RandomlyChangeSomeCubeActorMaterials()
{
	TArray<AActor*> CubeActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACubeActor::StaticClass(), CubeActors);

	// 确保获取到了ACubeActor
	if (CubeActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("未获取到任何ACubeActor"));
		return;
	}

	// 加载那唯一的一种另外的材质，需替换为实际项目中的材质路径
	UMaterialInterface* NewMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/Materials/M_SpecCubeMatrial.M_SpecCubeMatrial'"));
	if (!NewMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("未能成功加载指定的材质"));
		return;
	}

	// 随机决定要改变材质的CubeActor的数量，这里设为1到5个
	int32 NumToChange = FMath::RandRange(1, 5);

	// 用于记录已经改变了材质的CubeActor的数量
	int32 ChangedCount = 0;

	// 用于记录已经处理过的索引，避免重复选择
	TSet<int32> ProcessedIndices;

	while (ChangedCount < NumToChange)
	{
		// 随机选择一个未处理过的索引
		int32 RandomIndex;
		do
		{
			RandomIndex = FMath::RandRange(0, CubeActors.Num() - 1);
		} while (ProcessedIndices.Contains(RandomIndex));

		ProcessedIndices.Add(RandomIndex);

		AActor* RandomActor = CubeActors[RandomIndex];
		ACubeActor* ActualCubeActor = Cast<ACubeActor>(RandomActor);
		if (ActualCubeActor)
		{
			// 设置新的材质到Actor上，这里假设ACubeActor有一个SetMaterial之类的函数来设置材质
			ActualCubeActor->GetStaticMeshComponent()->SetMaterial(0, NewMaterial);
			ActualCubeActor->CubeSocre = 2*ActualCubeActor->CubeSocre;
			ChangedCount++;
		}
	}
}
