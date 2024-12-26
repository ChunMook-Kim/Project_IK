/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.23.2024
Summary : Header file for Dialogue Event Manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "Managers/EnumCluster.h"
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueEventManager.generated.h"

UCLASS(Blueprintable)
class PROJECT_IK_API UDialogueEventManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RunEvent(EDialogueEventType event_type) const;

private:
	void GetRandomDP() const;
	void GetRandomItem() const;
	void GetFireRateBurstDP() const;
	void GetFireRangeDP() const;
};
