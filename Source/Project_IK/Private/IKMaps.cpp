/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Map system.
					This file handles all actions about map.
					For example: procedurally generation of map, getter&setter, ...

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "IKMaps.h"

UIKMaps::UIKMaps()
	: Super::UObject()
{
}

void UIKMaps::GenerateMaps(int32 row, int32 col)
{
	ClearMaps();
	map.SetNum(row);

	for (int32 i = 0; i < row; i++)
	{
		map[i].SetNum(col);
	}
	// The First Rooms randomly chosen at the 1rst Floor cannot be the same.
	int32 departures_num = FMath::CeilToInt(col / 2.f);
	TArray<int32> departures;
	while (departures.Num() < departures_num)
	{
		int32 d = FMath::RandRange(0, col - 1);
		UE_LOG(LogTemp, Warning, TEXT("%d"), d);
		departures.AddUnique(d);
	}

	// then connects it with a Path to one of the 3 closest Rooms on the 2nd Floor. 
	for (int32 i = 0; i < departures_num; i++)
	{
		const int32 c = departures[i];
		int32 paths = FMath::CeilToInt32(FMath::RandRange(0.f, 1.1f));
		map[0][c].type = QueryNodeType();
		while (map[0][c].next.Num() < paths)
		{
			int32 next = FMath::Clamp(c + FMath::RandRange(-1, 1), 0, col - 1);
			if (!IsPathCrossed(0, c, next))
			{
				map[0][c].next.AddUnique(next);
			}
		}
	}
	
	// repeats this procces until reaches to the top floor
	for (int32 i = 0; i < row - 1; i++)
	{
		for (int32 j = 0; j < col; j++)
		{
			if (map[i][j].type != NodeType::None)
			{
				for (int32 t = 0; t < map[i][j].next.Num(); t++)
				{
					const int32 target = map[i][j].next[t];
					FMapNode& node = map[i + 1][target];
					node.type = QueryNodeType();

					int32 paths = FMath::CeilToInt32(FMath::RandRange(0.f, 1.1f));
					while (node.next.Num() < paths)
					{
						int32 next = FMath::Clamp(target + FMath::RandRange(-1, 1), 0, col - 1);
						if (!IsPathCrossed(i + 1, target, next))
						{
							map[i + 1][target].next.AddUnique(next);
						}
					}
				}
			}
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Map Generation has been done!"));
}

int32 UIKMaps::GetMaxNode() const
{
	return GetWidth() * GetHeight();
}

int32 UIKMaps::GetWidth() const
{
	 return map[0].Num();
}

int32 UIKMaps::GetHeight() const
{
	return map.Num();
}

const FMapNode UIKMaps::GetNode(int32 x, int32 y) const
{
	return map[y][x];
}

void UIKMaps::ClearMaps()
{
	for (int32 i = 0; i < map.Num(); i++)
	{
		map[i].Empty();
	}
	map.Empty();
}

bool UIKMaps::IsPathCrossed(int32 row, int32 col, int32 path_to) const
{
	// When the path points to left top node,
	if (col <= 0 || path_to >= col)
	{
		return false;
	}

	// If the left node points to right top node,
	return map[row][col - 1].next.Contains(col);
}

NodeType UIKMaps::QueryNodeType() const
{
	return NodeType::Enemy;
}