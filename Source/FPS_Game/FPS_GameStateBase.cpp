// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_GameStateBase.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

AFPS_GameStateBase::AFPS_GameStateBase()
{
	GameDuration = 10.0f;
	CountdownWidget = nullptr;
	RemainingTime = GameDuration;
	PlayerScore = 0;
}

void AFPS_GameStateBase::BeginPlay()
{
	Super::BeginPlay();
	// 使用定时器，每秒调用一次UpdateCountdownUI函数来更新倒计时显示
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AFPS_GameStateBase::UpdateCountdownUI, 1.0f, true);
	// 设置定时器，在GameDuration秒后调用EndGame函数来结束游戏
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AFPS_GameStateBase::EndGame, GameDuration, false);

	// 获取当前世界的玩家控制器
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		// 加载带有倒计时显示的UMG界面的蓝图类
		UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG/GameUMG.GameUMG_C'"));
		if (WidgetClass)
		{
			// 创建UMG界面实例并保存引用
			CountdownWidget = CreateWidget(PlayerController, WidgetClass);
			if (CountdownWidget)
			{
				// 将UMG界面添加到视口中显示（首次添加）
				CountdownWidget->AddToViewport();
			}
		}
	}
}

void AFPS_GameStateBase::UpdateCountdownUI()
{
	RemainingTime -= 1.0f;
	if (RemainingTime < 0.0f)
	{
		RemainingTime = 0.0f;
		// 停止更新倒计时的定时器（因为游戏结束了）
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		// 调用游戏结束逻辑（这里调用之前定义的EndGame函数）
		EndGame();
		return;
	}

	if (CountdownWidget)
	{
		// 获取UMG界面上的文本组件，文本组件名为"CountdownText"
		UTextBlock* TextBlock = Cast<UTextBlock>(CountdownWidget->GetWidgetFromName(TEXT("CountdownText")));
		if (TextBlock)
		{
			// 将剩余时间格式化为字符串（例如显示为 "0:00" 格式）
			FString TimeString = FString::Printf(TEXT("%02d:%02d"), FMath::FloorToInt(RemainingTime / 60), FMath::FloorToInt(RemainingTime));
			TextBlock->SetText(FText::FromString(TimeString));
		}
	}
}

void AFPS_GameStateBase::EndGame()
{
	// 目前先简单打印一个日志信息
	UE_LOG(LogTemp, Warning, TEXT("游戏时间结束，游戏结束！"));
	// 调用显示游戏结束的UMG界面的函数（前面已实现）
	ShowEndGameUI();
}

void AFPS_GameStateBase::ShowEndGameUI()
{
	// 获取当前世界的玩家控制器
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		// 加载UMG界面的蓝图类
		UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG/GameEndUMG.GameEndUMG_C'"));
		if (WidgetClass)
		{
			// 创建UMG界面实例
			UUserWidget* EndGameWidget = CreateWidget(PlayerController, WidgetClass);
			if (EndGameWidget)
			{
				// 获取UMG界面上用于显示积分的文本组件，根据之前设置的名称来获取
				UTextBlock* ScoreTextBlock = Cast<UTextBlock>(EndGameWidget->GetWidgetFromName(TEXT("ScoreText")));
				if (ScoreTextBlock)
				{
					// 将玩家积分格式化为字符串，例如 "积分: 100" 的格式
					FString ScoreString = FString::Printf(TEXT("积分: %d"), PlayerScore);
					ScoreTextBlock->SetText(FText::FromString(ScoreString));
					// 将UMG界面添加到视口中显示
					EndGameWidget->AddToViewport();
				}
			}
		}
	}
}
