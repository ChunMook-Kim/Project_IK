/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.25.2024
Summary : Header file for UI to pick an item.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPickerUI.generated.h"

class UCanvasPanel;
class UBorder;
class UVerticalBox;
class UTextBlock;
class UHorizontalBox;
class UButton;
class UImage;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UItemPickerUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;


protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;

	void InitializeRootWidget();
	void InitializeChildWidgets();

	UFUNCTION()
	void SelectButtonBindingFunc();
	UFUNCTION()
	void ItemButtonOnClicked();

	TWeakObjectPtr<UCanvasPanel> root_canvas_panel_;
	TWeakObjectPtr<UBorder> background_;
	TWeakObjectPtr<UVerticalBox> widgets_holder_;
	TWeakObjectPtr<UTextBlock> title_;
	TWeakObjectPtr<UTextBlock> description_;
	TWeakObjectPtr<UHorizontalBox> buttons_holder_;
	TArray<TWeakObjectPtr<UButton>> buttons_;
	TWeakObjectPtr<UButton> select_button_;

	int32 selected_button_index_;
};
