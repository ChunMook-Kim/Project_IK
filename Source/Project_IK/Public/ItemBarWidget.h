/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.20.2024
Summary : Header file for ItemBarWidget.
					A class that derived by UserWidget displays item and works like an interface.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemBarWidget.generated.h"

class UButton;
class UItemInventory;
class UTargetingComponent;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UItemBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonClicked0();

	UFUNCTION()
	void OnButtonClicked1();

	UFUNCTION()
	void OnButtonClicked2();

	UFUNCTION()
	void UseItem(const FTargetData& TargetData);

private:
	int32 selected_item_index_;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* item_button_0_;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* item_button_1_;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* item_button_2_;

	UPROPERTY(VisibleAnywhere, meta=(PrivateAccessAllow))
	TWeakObjectPtr<UItemInventory> item_inventory_;

	UTargetingComponent* targeting_component_;
};
