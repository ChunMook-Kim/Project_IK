/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.27.2024
Summary : Source file for Item class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Managers/ItemDataManager.h"
#include "Item.generated.h"

struct FTargetResult;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void InitializeItemUsingData(FItemData item_data);

	UFUNCTION()
	void UseItem(const FTargetResult& TargetResult);

	UFUNCTION()
	FItemData GetData() const;

	UFUNCTION()
	FTargetParameters GetTargetParameters() const;
private:
	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemData item_data_;

	void RestoreHP(AActor* actor);
	void LaunchMissile(TArray<AActor*> actors);
};
