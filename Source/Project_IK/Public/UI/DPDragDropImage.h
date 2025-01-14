/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 1.10.2025
Summary : Header file for the Drag Drop image for inventory.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "DPDragDropImage.generated.h"

UCLASS()
class PROJECT_IK_API UDPDragDropImage : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativePreConstruct() override;
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
public:
	void SetImage(UTexture2D* InImage);

private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UImage* dragged_image_;
};
