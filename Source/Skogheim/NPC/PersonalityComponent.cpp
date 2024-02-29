// Fill out your copyright notice in the Description page of Project Settings.


#include "Skogheim/NPC/PersonalityComponent.h"
#include "Skogheim/NPC/NPC.h"

UPersonalityComponent::UPersonalityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPersonalityComponent::BeginPlay()
{
    Super::BeginPlay();
}

//moved this function over to BP logic 
void UPersonalityComponent::CheckKeywords(const FString& AIResponse)
{
   // GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, TEXT("Checking for keywords and triggering other events"));
}


void UPersonalityComponent::SetPrompt(FString NewPrompt)
{
	Prompt = NewPrompt;
}

void UPersonalityComponent::SetEmotion(const FString& NewEmotion)
{
	Emotion = NewEmotion;
}

void UPersonalityComponent::SetResponse(const FString& NewResponse)
{
	Response = NewResponse;
}

void UPersonalityComponent::SetStateFromEmotion(const FString& NewEmotion)
{
    if (NPC)
    {
        ENPCState NewState = ENPCState::Idle;   //create default state & compare string without case 

        
        if (Emotion.Equals("Happy", ESearchCase::IgnoreCase)) NewState = ENPCState::Happy;
        else if (Emotion.Equals("Sad", ESearchCase::IgnoreCase)) NewState = ENPCState::Sad;
        else if (Emotion.Equals("Angry", ESearchCase::IgnoreCase)) NewState = ENPCState::Angry;
        else if (Emotion.Equals("Anxious", ESearchCase::IgnoreCase)) NewState = ENPCState::Anxious;
        else if (Emotion.Equals("Surprised", ESearchCase::IgnoreCase)) NewState = ENPCState::Surprised;
        else if (Emotion.Equals("Confused", ESearchCase::IgnoreCase)) NewState = ENPCState::Confused;


        //update npc state
        NPC->SetNPCState(NewState);
    }
}




