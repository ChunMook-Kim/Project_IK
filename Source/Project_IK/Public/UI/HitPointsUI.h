// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HitPointsUI.generated.h"

class UProgressBar;
class UHorizontalBox;
class UBuffDisplayer;
class UTextureManager;

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
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void UpdateHPWidget();

	UFUNCTION()
	void UpdateShieldWidget();

	UFUNCTION()
	void UpdateBuffWidgets();

	UFUNCTION()
	void InitializeImages();

private:
	TWeakObjectPtr<class UCharacterStatComponent> character_stat_;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UProgressBar> shield_progress_bar_;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UProgressBar> hp_progress_bar_;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UHorizontalBox> buffs_container_;

	UPROPERTY()
	TArray<TWeakObjectPtr<UBuffDisplayer>> buff_displayers_;

	TWeakObjectPtr <const UTextureManager> texture_manager_;

	static constexpr int32 DISPLAYER_SIZE = 3;
};
