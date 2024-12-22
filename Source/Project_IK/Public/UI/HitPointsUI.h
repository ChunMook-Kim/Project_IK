/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.13.2024
Summary : Header file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

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
UCLASS(Blueprintable)
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TSubclassOf<UBuffDisplayer> buff_displayer_class_;

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
