/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.10.2024
Summary : Header file for Common functions.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
class ACover;

class PROJECT_IK_API CommonFunctions
{
public:
	static ACover* FindBestCover(TArray<AActor*>& cover_candidates, FVector attack_target_pos, float fire_range);
};
