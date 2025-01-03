// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPS_GameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_GAME_API AFPS_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	AFPS_GameStateBase();
	// 游戏总时长（单位：秒），可根据实际需求调整
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GameRules")
	float GameDuration;  

	//玩家分数
	int32 PlayerScore;
	
	// 用于倒计时的定时器句柄，用于后续操作定时器（比如取消定时器等）
	FTimerHandle CountdownTimerHandle;

	// 剩余游戏时间（初始化为游戏总时长）
	float RemainingTime;
	
	// 游戏开始时调用的函数，用于启动游戏时间计时和倒计时显示相关逻辑
	virtual void BeginPlay() override;
   

private:
	
	
	// 游戏结束定时器句柄
	FTimerHandle GameTimerHandle;

	// 新增一个成员变量用于保存CountdownWidget的引用
	UUserWidget* CountdownWidget;

	// 函数用于更新UMG界面上的倒计时显示
	void UpdateCountdownUI();
  

	// 游戏结束时调用的函数，前面已经介绍过，这里可以添加更多游戏结束相关逻辑
	void EndGame();
   

	// 函数用于显示游戏结束的UMG界面，前面已实现
	void ShowEndGameUI();
};
