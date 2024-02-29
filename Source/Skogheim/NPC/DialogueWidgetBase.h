// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"		
#include "Skogheim/NPC/PersonalityComponent.h"
#include "Skogheim/NPC/NPC.h"
#include "Interfaces/IHttpRequest.h"
#include "DialogueWidgetBase.generated.h"

/**
 *
 */
UCLASS()
class SKOGHEIM_API UDialogueWidgetBase : public UUserWidget
{
    GENERATED_BODY()
public:


    //set the owning NPC ref
    UFUNCTION(BlueprintCallable)
    void SetOwningNPC(ANPC* InOwningNPC);

    //handle API request
    UFUNCTION(BlueprintCallable, Category = "AI")
    void SendApiRequest(const FString& PlayerInput);

    //handle AI response
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UScrollBox* ScrollBox;    
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> DialogueTextWidgetClass;

    //Blueprint function to show response on screen
    UFUNCTION(BlueprintImplementableEvent)
    void CreateText();

    //used in Blueprint..
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")         
    FString CurrentResponse;

    //will be set and passed on
    FString Emotion;
    FString DialogueContent;


protected:
    //reference to owning NPC
    ANPC* OwningNPC;

    //reference to personality component of current NPC
    UPROPERTY()
    UPersonalityComponent* PersonalityComponent;

};
