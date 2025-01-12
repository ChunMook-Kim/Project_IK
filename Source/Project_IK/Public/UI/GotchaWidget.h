/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.3.2025
Summary : Header file of user widget class to gotcha.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GotchaWidget.generated.h"

class UButton;
class UTextBlock;
class UGotchaResultWidget;
struct FItemData;
struct FDronePluginData;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UGotchaWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UGotchaResultWidget> result_widget_class_;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void BackSpace();
	UFUNCTION()
	void PullOne();
	UFUNCTION()
	void PullTen();

	void SetTickets(int32 tickets);

	void UpdateGotchaTicketCount();

	void Gotcha(int32 pulls);

	void ClearContainers();

	UFUNCTION()
	void StorePulledData();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UButton> back_space_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UButton> pull_one_button_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UButton> pull_ten_button_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UTextBlock> tickets_count_text_;
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<UGotchaResultWidget> result_widget_;

	TArray<FItemData*> pulled_items_;
	TArray<FDronePluginData> pulled_dps_;
	int32 pulled_currency_;

	int32 tickets_;
};
