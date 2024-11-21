/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Header file for the Drone Plugin base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/PassiveSkill.h"
#include "DronePlugIn.generated.h"

class ADrone;

UCLASS()
class PROJECT_IK_API ADronePlugIn : public APassiveSkill
{
	GENERATED_BODY()
public:
	ADronePlugIn();
	virtual void Initialize(AActor* caster) override;
	bool IsPeriodic() const;
	void SetPeriodic(bool bIs_Periodic);

protected:
	bool is_periodic_;
	
private:
	//드론 플러그인은 패시브 스킬에서 추가적으로 드론을 참조한다.
	AActor* owner_hero_;
	AActor* owner_drone_;
};
