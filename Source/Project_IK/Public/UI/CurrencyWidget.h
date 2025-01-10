/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.07.2025
Summary : Header file for a widget to display currency.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CurrencyWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UCurrencyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UTextBlock> money_text_;
};
