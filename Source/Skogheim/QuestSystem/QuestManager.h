// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skogheim/QuestSystem/QuestObject.h"
#include "Skogheim/SkogheimCharacter.h"
//#include "Blueprint/UserWidget.h"
#include "QuestManager.generated.h"

UCLASS()
class SKOGHEIM_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(BlueprintReadOnly)
	//ASkogheimCharacter* Player;

	//UPROPERTY(EditDefaultsOnly, Category = "UI")
	//TSubclassOf<UUserWidget> QuestWBP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	//// Reference to the quest widget instance
	//UPROPERTY()
	//UUserWidget* QuestWBPInstance;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	//TArray<UQuestObject*> QuestList;

	////currently active quest
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	//UQuestObject* CurrentQuest;

	//UFUNCTION(BlueprintCallable, Category = "Quest")
	//UQuestObject* GetQuestById(int32 QuestID);

	//UFUNCTION(BlueprintCallable, Category = "Quest")
	//UQuestObject* GetCurrentQuest() const;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<FQuestStruct> QuestList;

	FQuestStruct* FindQuestByID(int32 QuestID);
	void AddQuest(const FQuestStruct& NewQuest);
	void RemoveQuest(int32 QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void StartQuest(int32 QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void FinishQuest(int32 QuestID);*/


};
