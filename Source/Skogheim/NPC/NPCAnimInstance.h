// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NPC.h"
#include "NPCAnimInstance.generated.h"

//forward declare NPC so that class can use
class ANPC;

/**
 * 
 */
UCLASS()
class SKOGHEIM_API UNPCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public: 

	//tick function
	UFUNCTION(BlueprintCallable)
	void UpadeAnimationProperties(float DeltaTime);

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC")
	//ENPCState StateRef;
		//get NPC
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ANPC* NPC;


private:

	
	//speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed;

	//offset used for strafing (not sure if will be used)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementOffsetYaw;

	//hold state reference to NPC state
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	//TEnumAsByte<NPC_State> StateRef;

};
