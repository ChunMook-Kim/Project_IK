/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.02.2024
Summary : Source file for UI to display how much damage dealt.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageUI.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UDamageUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetDamageAmount(float Damage);

	UFUNCTION(BlueprintCallable)
	void SetMissed();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock> damage_text_;

	float opacity;
};
