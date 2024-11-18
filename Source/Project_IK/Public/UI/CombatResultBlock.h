/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.17.2024
Summary : Header file for Combat Result block class.
						It is an attachment for CombatResultUI. It is not be used itself alone.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatResultBlock.generated.h"

class UVerticalBox;
class UImage;
class USpacer;
class USizeBox;
class UProgressBar;
class UHorizontalBox;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UCombatResultBlock : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable)
	void SetHPPercent(float ratio);

	UFUNCTION(BlueprintPure)
	float GetHPPercent();

	UFUNCTION(BlueprintCallable)
	void SetHPOpacity(float opacity);

	UFUNCTION(BlueprintCallable)
	void SetDamageDealt(float damage);

protected:
	virtual void NativeConstruct() override;

	void InitializeRootWidget();
	void InitializeChildWidgets();

	UPROPERTY()
	TWeakObjectPtr<UVerticalBox> root_vertical_box_;

	UPROPERTY()
	TWeakObjectPtr<UImage> hero_portrait_;
	
	UPROPERTY()
	TWeakObjectPtr<USpacer> spacer_hero_hp_;

	UPROPERTY()
	TWeakObjectPtr<USizeBox> hp_holder_;

	UPROPERTY()
	TWeakObjectPtr<UProgressBar> hp_;

	UPROPERTY()
	TWeakObjectPtr<USpacer> spacer_hp_deal_;

	UPROPERTY()
	TWeakObjectPtr<UHorizontalBox> deal_holder_;

	UPROPERTY()
	TWeakObjectPtr<UImage> deal_icon_;

	UPROPERTY()
	TWeakObjectPtr<UTextBlock> deal_text_;
};
