// Fill out your copyright notice in the Description page of Project Settings.


#include "Skogheim/QuestSystem/QuestManager.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AQuestManager::AQuestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    //if (QuestWBP != nullptr)
    //{
    //    QuestWBPInstance = CreateWidget<UUserWidget>(GetWorld(), QuestWBP);
    //    if (QuestWBPInstance != nullptr)
    //    {
    //        QuestWBPInstance->AddToViewport();
    //    }
    //}

}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();


    //if (!Player)
    //{
    //    Player = Cast<ASkogheimCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    //}
	
}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//FQuestStruct* AQuestManager::FindQuestID(int32 QuestID)
//{
//    for (FQuestStruct& Quest : QuestList)
//    {
//        if (Quest.QuestID == QuestID)
//        {
//            return &Quest;
//        }
//    }
//    return nullptr;
//}
//void AQuestManager::StartQuest(int32 QuestID)
//{
//    FQuestStruct* Quest = FindQuestByID(QuestID);
//    if (Quest)
//    {
//        Quest->State = EQuestState::Active;
//        
//}
//
//void AQuestManager::CompleteQuest(int32 QuestID)
//{
//    FQuestStruct* Quest = FindQuestByID(QuestID);
//    if (Quest)
//    {
//        Quest->State = EQuestState::Completed;
//       
//    }
//}
//
//FQuestStruct* AQuestManager::GetQuestByID(int32 QuestID)
//{
//    for (FQuestStruct& Quest : QuestList)
//    {
//        if (Quest.QuestID == QuestID)
//        {
//            return &Quest;
//        }
//    }
//
//    return nullptr;
//}
//
//void AQuestManager::AddQuest(const FQuestStruct& NewQuest)
//{
//    QuestList.Add(NewQuest);
//}
//
//void AQuestManager::RemoveQuest(int32 QuestID)
//{
//    QuestList.RemoveAll([QuestID](const FQuestStruct& Quest)
//        {
//            return Quest.QuestID == QuestID;
//        });
//}
//
