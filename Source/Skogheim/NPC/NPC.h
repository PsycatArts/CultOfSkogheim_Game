// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Skogheim/NPC/PersonalityComponent.h"
#include "Skogheim/SkogheimCharacter.h"
#include "Skogheim/QuestSystem/QuestInterface.h"
//#include "Skogheim/QuestSystem/QuestManager.h"
//#include "Skogheim/NPC/DialogueWidgetBase.h"
#include "NPC.generated.h"

//UENUM(BlueprintType)
//enum Emotion
//{
//	happy, 
//	sad, 
//	angry, 
//	anxious, 
//	surprised, 
//	confused
//};


UENUM(BlueprintType)
enum class ENPCState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Walk UMETA(DisplayName = "Walk"),
	Pray UMETA(DisplayName = "Pray"),
	PrayKneeling UMETA(DisplayName = "PrayKneeling"),
	Talk UMETA(DisplayName = "Talk"),
	Sit UMETA(DisplayName = "Sit"),
	Insane UMETA(DisplayName = "Insane"),

	//emotions
	Happy UMETA(DisplayName = "Happy"),
	Sad UMETA(DisplayName = "Sad"),
	Angry UMETA(DisplayName = "Angry"),
	Anxious UMETA(DisplayName = "Anxious"),
	Surprised UMETA(DisplayName = "Surprised"),
	Confused UMETA(DisplayName = "Confused")

};

class UDialogueWidgetBase;
//class AQuestManager;
UCLASS()
class SKOGHEIM_API ANPC : public ACharacter, public IQuestInterface
{
	GENERATED_BODY()

public:
	ANPC();

	UPROPERTY(BlueprintReadOnly)
	ASkogheimCharacter* Player;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NPC")
	UPersonalityComponent* PersonalityComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	TMap<FString, bool> KeywordList;

	//this enum can be accessed and changed in blueprints to set emotion
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	ENPCState MyNPCState;

	UFUNCTION(BlueprintCallable)
	void SetNPCState(ENPCState NewState);

	//assign in EDITOR
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC")
	TSubclassOf<UDialogueWidgetBase> DialogueWidgetClass;

	UFUNCTION(BlueprintCallable)
	void Dialogue();

	UFUNCTION(BlueprintCallable)
	void EndDialogue();

	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue")
	void OnDialogueEnd();

	UFUNCTION(BlueprintCallable)
	void InitWBP();

	//temperature: creativity & randomness of AI dialogue generation. High value = very random
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	float temperature = 0.65;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	bool CanDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	bool DialogueActive;


	UDialogueWidgetBase* bWidget;
};
