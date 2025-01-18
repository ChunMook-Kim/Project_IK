/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.15.2025
Summary : Header file for main Widget in StoreLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreWidget.generated.h"

class UHorizontalBox;
class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UStoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> item_container_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> dp_container_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> total_cost_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> pay_button_;


};
