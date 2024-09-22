// Fill out your copyright notice in the Description page of Project Settings.


#include "IKGameInstance.h"

UIKGameInstance::UIKGameInstance()
{
	FString character_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Proto_GameData.IK_Proto_GameData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_character_data(*character_data_path);
	if (dt_character_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a game file data (IK_Proto_GameData)"));
	}
	character_table = dt_character_data.Object;
}

FCharacterData* UIKGameInstance::GetCharacterData(int32 char_id)
{
	return character_table->FindRow<FCharacterData>(*FString::FromInt(char_id), TEXT(""));
}

void UIKGameInstance::Init()
{
	Super::Init();

}
