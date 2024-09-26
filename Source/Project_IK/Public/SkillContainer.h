// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillBase.h"
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
	void InvokeSkills();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	TSubclassOf<class USkillBase> skill_class_;

	UPROPERTY()
	USkillBase* skill_;
};
