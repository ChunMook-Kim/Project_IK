/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.10.2024
Summary : Source file for managing characters data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/CharacterDataManager.h"

UCharacterDataManager::UCharacterDataManager()
	: Super::UObject()
{
	FString character_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Proto_GameData.IK_Proto_GameData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_character_data(*character_data_path);
	if (dt_character_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a game file data (IK_Proto_GameData)"));
	}
	character_table = dt_character_data.Object;
}

FCharacterData* UCharacterDataManager::GetCharacterData(int32 char_id) const
{
	if (character_table)
	{
		return character_table->FindRow<FCharacterData>(*FString::FromInt(char_id), TEXT(""));
	}
	return nullptr;
}
