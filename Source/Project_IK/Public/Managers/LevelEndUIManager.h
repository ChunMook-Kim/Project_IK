// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelEndUIManager.generated.h"

UENUM(BlueprintType)
enum class ELevelEndState : uint8
{
	ShowingCombatResultUI UMETA(DisplayName = "ShowingCombatResultUI"),
	ShowingMapUI UMETA(DisplayName = "ShowingMapUI"),
};

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
	void DisplayCombatResult(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map);

	UFUNCTION()
	void SwitchUIByState(ELevelEndState state);

protected:

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TWeakObjectPtr<UCombatResultUI> combat_result_widget_;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TWeakObjectPtr<UUserWidget> map_widget_;
};
