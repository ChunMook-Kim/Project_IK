/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.08.2024
Summary : Header file for UI that displays buffs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuffDisplayer.generated.h"

class UOverlay;
class UImage;
class UTextBlock;
class UTexture2D;
class UMaterialInterface;
class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UBuffDisplayer : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	UFUNCTION()
	void SetImage(UTexture2D* Texture);
	UFUNCTION()
	void SetBackground(FLinearColor color);
	UFUNCTION()
	void SetDuplicatedText(int32 Duplicated);
	UFUNCTION()
	void HideText() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuffDisplayer")
	UMaterialInterface* image_material_;

protected:
	virtual void NativeConstruct() override;

	void InitializeRootWidget();
	void InitializeChildWidgets();

	UPROPERTY()
	UMaterialInstanceDynamic* dynamic_material_;

	UPROPERTY()
	TWeakObjectPtr<UOverlay> root_widget_;
	UPROPERTY()
	TWeakObjectPtr<UImage> buff_image_;
	UPROPERTY()
	TWeakObjectPtr<UTextBlock> duplicated_text_;
};
