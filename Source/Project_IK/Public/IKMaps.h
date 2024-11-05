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

UENUM(BlueprintType)
enum class NodeType : uint8
{
	None UMETA(DisplayName = "None"),
	Enemy UMETA(DisplayName = "Enemy"),
};

USTRUCT(BlueprintType)
struct FMapNode
{
	GENERATED_BODY()

	FMapNode()
		:type(NodeType::None)
	{}

	UPROPERTY(VisibleAnywhere, Category="MapNode")
	NodeType type;
	UPROPERTY(VisibleAnywhere, Category = "MapNode")
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
	UFUNCTION(BlueprintCallable, Category="Map")
	inline int32 GetMaxNode() const;
	UFUNCTION(BlueprintCallable, Category = "Map")
	inline int32 GetWidth() const;
	UFUNCTION(BlueprintCallable, Category = "Map")
	inline int32 GetHeight() const;
	UFUNCTION(BlueprintCallable, Category = "Map")
	const FMapNode GetNode(int32 x, int32 y) const;

protected:
	TArray<TArray<FMapNode>> map;

	void ClearMaps();
	bool IsPathCrossed(int32 row, int32 col, int32 path_to) const;
	inline NodeType QueryNodeType() const;
};
