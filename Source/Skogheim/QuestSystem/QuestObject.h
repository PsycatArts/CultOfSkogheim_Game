// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestObject.generated.h"

//UENUM(BlueprintType)
//enum class EQuestState : uint8 
//{
//	Pending UMETA(DisplayName = "Pending"),
//	Active UMETA(DisplayName = "Active"),
//	Completed UMETA(DisplayName = "Completed")
//};

/**
 * 
 */
UCLASS(Blueprintable)
class SKOGHEIM_API UQuestObject : public UObject
{
	GENERATED_BODY()

public: 
	UQuestObject();
	
	//UNIQUE ID	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	int32 QuestId;

	//the display text of the quest
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Quest")
	FString Name;

	////(pending/active/completed)
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	//EQuestState State;

	//internal description, detailled quest info for dev-team
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest", meta= (Multiline=true))
	FString Description;
	
};
