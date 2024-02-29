// Fill out your copyright notice in the Description page of Project Settings.


#include "Skogheim/NPC/NPC.h"
#include "Skogheim/NPC/DialogueWidgetBase.h"
#include "Kismet/GameplayStatics.h"

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;
	PersonalityComponent = CreateDefaultSubobject<UPersonalityComponent>(TEXT("Personality_Component"));
    PersonalityComponent->NPC = this;
   // PersonalityComponent->SetPrompt("You are a rat");


    if (!Player)
    {
        Player = Cast<ASkogheimCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    }
    else {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Player found."));
    }

	CanDialogue = true;
	DialogueActive = false;
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();
}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //ensure dialogue is active before checking the distance
    if (DialogueActive && bWidget)
    {
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0); //get player pawn, adjust index if necessary
        if (PlayerPawn)
        {
            float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());

            if (Distance > 400.0f) 
            {
                EndDialogue(); //close dialogue.
            }
        }
    }
}

void ANPC::SetNPCState(ENPCState NewState)
{
    MyNPCState = NewState;
}

void ANPC::Dialogue()
{
    if (!DialogueActive) 
    {
        DialogueActive = true;
        InitWBP();
    }
    else
    {
        EndDialogue();
    }
}

void ANPC::EndDialogue()
{
    if (bWidget)
    {
        DialogueActive = false;
        bWidget->RemoveFromParent();
        OnDialogueEnd();
    }
}


void ANPC::InitWBP()
{
    if (DialogueWidgetClass != nullptr)
    {
        UDialogueWidgetBase* DialogueWidget = CreateWidget<UDialogueWidgetBase>(GetWorld(), DialogueWidgetClass);
        if (DialogueWidget)
        {
            DialogueWidget->SetOwningNPC(this);         //set npc ref
            DialogueWidget->AddToViewport();
            bWidget = DialogueWidget;
        }
    }
}


