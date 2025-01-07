/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.5.2025
Summary : Header file for a gotcha slot.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GotchaSlot.generated.h"

class UImage;
class UWidgetAnimation;
class UTexture2D;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UGotchaSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetImage(UTexture2D* texture);
	UWidgetAnimation* GetAnimation();
	// Force the status to be end of animation
	void ResetAnimationStatus();

protected:
	virtual void NativeConstruct() override;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UImage> slot_image_;
	UPROPERTY(VisibleAnywhere, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* slot_animation_;

};
