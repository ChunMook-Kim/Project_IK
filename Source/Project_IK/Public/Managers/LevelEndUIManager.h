// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelEndUIManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API ULevelEndUIManager : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void InitializeUI(TSubclassOf<class UCombatResultUI> combat_result_widget_class, TSubclassOf<class UUserWidget> map_widget_class, UWorld* world);

	UFUNCTION()
	void ToggleMapWidget();

	UFUNCTION()
	void DisplayCombatResult(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map);

//protected:

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TWeakObjectPtr<UCombatResultUI> combat_result_widget_;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TWeakObjectPtr<UUserWidget> map_widget_;
};
