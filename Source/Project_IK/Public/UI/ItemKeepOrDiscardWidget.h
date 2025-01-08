/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.08.2025
Summary : Header file of widget that choose whether keep the item or discard.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemKeepOrDiscardWidget.generated.h"

class UHorizontalBox;
class UButton;
class UCheckboxButtonWidget;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UItemKeepOrDiscardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCheckboxButtonWidget> check_box_button_class_;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnConfirmButtonClicked();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UHorizontalBox> candidates_item_container_;
	UPROPERTY()
	TArray<UCheckboxButtonWidget*> candidates_items_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UTextBlock> item_text_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UHorizontalBox> inventory_item_container_;
	UPROPERTY()
	TArray<UCheckboxButtonWidget*> inventory_items_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UButton> confirm_button_;
};
