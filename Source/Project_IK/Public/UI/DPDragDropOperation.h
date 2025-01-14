/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 1.10.2025
Summary : Header file for the Drag Drop operation for the inventory.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "DPSlot.h"
#include "Blueprint/DragDropOperation.h"
#include "DPDragDropOperation.generated.h"

UCLASS()
class PROJECT_IK_API UDPDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UDPDragDropOperation();

public:
	UPROPERTY(VisibleAnywhere)
	UDPSlot* dragged_slot_data_;
};