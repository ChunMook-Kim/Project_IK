/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.04.2024
Summary : Header file for ForwardDestination Environment Query Context.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQC_ForwardDestination.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UEQC_ForwardDestination : public UEnvQueryContext
{
	GENERATED_BODY()
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
	
private:
	float move_amount_ = 1000.f;
};
