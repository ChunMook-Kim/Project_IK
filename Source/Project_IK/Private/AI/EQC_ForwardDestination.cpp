/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.04.2024
Summary : Source file for ForwardDestination Environment Query Context.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "AI/EQC_ForwardDestination.h"

#include "AIController.h"
#include "Characters/Gunner.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"

void UEQC_ForwardDestination::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);
	if(AGunner* casted_gunner = Cast<AGunner>(QueryInstance.Owner))
	{
		FVector new_location = casted_gunner->GetActorLocation() + casted_gunner->GetForwardDir() * move_amount_;
		if (FAISystem::IsValidLocation(new_location))
		{
			UEnvQueryItemType_Point::SetContextHelper(ContextData, new_location);
		}
	}
}