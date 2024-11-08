// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HitPointsUI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UHitPointsUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void BindCharacterStat(class UCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UCharacterStatComponent> character_stat_;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* hp_progress_bar_;
};
