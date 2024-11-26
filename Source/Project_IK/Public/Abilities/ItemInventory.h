/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.19.2024
Summary : Header file for Item inventory.
					It contains a technical data of items.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInventory.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UItemInventory : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void AddItem(TSubclassOf<USkillBase> item_class);

	UFUNCTION(BlueprintPure)
	USkillBase* GetItem(int32 index);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(int32 index);

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<USkillBase*> item_inventory_;
};
