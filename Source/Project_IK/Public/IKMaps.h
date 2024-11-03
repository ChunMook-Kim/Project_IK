/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Map system.
					This file handles all actions about map.
					For example: procedurally generation of map, getter&setter, ...

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IKMaps.generated.h"

enum class NodeType
{
	None,
	Enemy,
};

struct MapNode
{
	NodeType type;
	TArray<int32> next;
};

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UIKMaps : public UObject
{
	GENERATED_BODY()
	
public:
	UIKMaps();

	UFUNCTION(BlueprintCallable, Category="Map")
	void GenerateMaps(int32 row, int32 col);

protected:
	TArray<TArray<MapNode>> map;
};
