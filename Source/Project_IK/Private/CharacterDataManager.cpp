#include "CharacterDataManager.h"

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
