/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 1.10.2025
Summary : Header file for the DP Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "Blueprint/UserWidget.h"
#include "Structs/DPData.h"
#include "DPSlot.generated.h"

class UDPDragDropImage;
class UButton;
class UImage;
class UDragDropOperation;
class UInventoryComponent;
UCLASS(Blueprintable)
class PROJECT_IK_API UDPSlot : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
public:
	void ClearData();
	void SetImageTexture();
	
private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UButton* button_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	UImage* image_;
	
	//Class는 meta - bind widget가 안먹히는것 같다.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UDragDropOperation> dragdrop_class_;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UDPDragDropImage> dragdrop_image_class_;
public:
	UPROPERTY(Transient)
	EDPSlotType slot_type_ = EDPSlotType::Inventory;

	UPROPERTY(Transient)
	int grid_idx_;
	
	UPROPERTY(Transient)
	FDPData dp_data_;
};
