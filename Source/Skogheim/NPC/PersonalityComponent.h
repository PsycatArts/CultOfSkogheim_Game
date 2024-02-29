// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PersonalityData.h"
//#include "Skogheim/NPC/NPC.h"
#include "PersonalityComponent.generated.h"

class ANPC;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKOGHEIM_API UPersonalityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPersonalityComponent();

    ANPC* NPC;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC", meta = (AllowPrivateAccess = "true"))
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC", meta = (AllowPrivateAccess = "true"))
    FString Prompt;

    UFUNCTION(BlueprintCallable, Category = "NPC" , meta = (AllowPrivateAccess = "true"))
    void CheckKeywords(const FString& AIResponse);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC", meta = (AllowPrivateAccess = "true"))
    FString Emotion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC", meta = (AllowPrivateAccess = "true"))
    FString Response;

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void SetPrompt(FString NewPrompt);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void SetEmotion(const FString& NewEmotion);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void SetResponse(const FString& NewResponse);

    void SetStateFromEmotion(const FString& Emotion);

private:

protected:
    virtual void BeginPlay() override;

};
