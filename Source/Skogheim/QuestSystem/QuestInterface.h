// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Skogheim/QuestSystem/QuestObject.h"
#include "QuestInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQuestInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
//INTERFACE FOR OBJECTS THAT CAN INTERACT WITH QUESTS.
class SKOGHEIM_API IQuestInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest")
	void OnQuestTrigger();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest")
	void OnQuestEnd();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest")
	void OnNoteTrigger(const FString& NewNote);


	//virtual void OnQuestStarted(int32 QuestID) = 0;
	//virtual void OnQuestCompleted(int32 QuestID) = 0;


	//UFUNCTION(BlueprintNativeEvent, Blueprintcallable, Category = "Interact")
	//void OnQuestStarted(int32 QuestID);

	//UFUNCTION(BlueprintNativeEvent, Blueprintcallable, Category = "Interact")
	//void OnQuestCompleted(int32 QuestID);
};
