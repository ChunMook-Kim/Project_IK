/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.17.2024
Summary : Header file for a slot UserWidget for Store.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreSlot.generated.h"

class UCheckboxButtonWidget;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UStoreSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetTexture(UTexture2D* texture);
	UFUNCTION(BlueprintCallable)
	void SetPrice(int32 price);

	void BindOnClicked(const FSimpleDelegate& Callback);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckboxButtonWidget> checkbox_button_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> price_text_;
	
	int32 price_;
};
