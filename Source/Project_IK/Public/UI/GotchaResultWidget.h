/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.3.2025
Summary : Header file for a user widget to display gotcha result.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GotchaResultWidget.generated.h"

class UGridPanel;
class UImage;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UGotchaResultWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void DisplayResults(TArray<UTexture2D*> textures);
	void DisplayResult(UTexture2D* texture);
	
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UGridPanel> image_containers_;

	TArray<TWeakObjectPtr<UImage>> images_;

	static constexpr int32 MAX_IMAGE = 10;
};
