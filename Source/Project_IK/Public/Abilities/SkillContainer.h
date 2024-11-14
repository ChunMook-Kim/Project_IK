/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.26.2024
Summary : Header file for skill containers.
					An actor component class to contain skills.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillBase.h"

#include "components/TargetingComponent.h"

#include "SkillContainer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API USkillContainer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillContainer();

	virtual void InitializeComponent() override;

	UFUNCTION(BlueprintCallable)
	void InvokeSkills(const FTargetData& TargetData);

	UFUNCTION(BlueprintCallable)
	void SetSkill(TSubclassOf<class USkillBase> skill);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	TSubclassOf<class USkillBase> skill_class_;

	UPROPERTY()
	USkillBase* skill_;
};
