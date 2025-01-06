/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.06.2025
Summary : Source file for an abstract class that has helper functions related to handle assets have rarity.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/RarityAbstractObject.h"
#include "Managers/EnumCluster.h"

ERarity URarityAbstractObject::GetRarityRandomly(ERarity weight_rarity) const
{
	// Weights for each rarity
	TArray<TPair<ERarity, int32>> weights;
	switch (weight_rarity)
	{
	case ERarity::S:
		weights = {
			TPair<ERarity, int32>(ERarity::B, 15),
			TPair<ERarity, int32>(ERarity::A, 35),
			TPair<ERarity, int32>(ERarity::S, 50)
		};
		break;
	case ERarity::A:
		weights = {
			TPair<ERarity, int32>(ERarity::B, 20),
			TPair<ERarity, int32>(ERarity::A, 60),
			TPair<ERarity, int32>(ERarity::S, 20)
		};
		break;
	case ERarity::B:
		weights = {
			TPair<ERarity, int32>(ERarity::B, 60),
			TPair<ERarity, int32>(ERarity::A, 30),
			TPair<ERarity, int32>(ERarity::S, 10)
		};
		break;
	default:
		break;
	}

	constexpr int32 total_weight = 100;
	int32 random_value = FMath::RandRange(0, total_weight);

	// Return rarity based on the random value
	int32 cumulative_weight = 0;
	for (const auto& pair : weights)
	{
		cumulative_weight += pair.Value;
		if (random_value <= cumulative_weight)
		{
			return pair.Key;
		}
	}
	return ERarity::B;
}

void URarityAbstractObject::CategorizeByRarity(UDataTable* data_table)
{
	if (!data_table)
	{
		return;
	}

	for (auto& row_pair : data_table->GetRowMap())
	{
		FRarityData* item = reinterpret_cast<FRarityData*>(row_pair.Value);
		if (!item)
		{
			continue;
		}

		// Sort the item into the correct array based on its rarity
		switch (item->rarity_)
		{
		case ERarity::B:
			rarity_B.Add(item);
			break;
		case ERarity::A:
			rarity_A.Add(item);
			break;
		case ERarity::S:
			rarity_S.Add(item);
			break;
		default:
			break;
		}
	}
}

FRarityData* URarityAbstractObject::GetRandomDataByRarity(ERarity rarity) const
{
	int32 rand_index = 0;
	switch (rarity)
	{
	case ERarity::S:
		rand_index = FMath::RandRange(0, rarity_S.Num() - 1);
		return rarity_S[rand_index];
		break;
	case ERarity::A:
		rand_index = FMath::RandRange(0, rarity_A.Num() - 1);
		return rarity_A[rand_index];
		break;
	case ERarity::B:
	default:
		rand_index = FMath::RandRange(0, rarity_B.Num() - 1);
		return rarity_B[rand_index];
		break;
	}
}
