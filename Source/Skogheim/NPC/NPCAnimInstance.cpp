// Fill out your copyright notice in the Description page of Project Settings.


#include "Skogheim/NPC/NPCAnimInstance.h"
#include "Skogheim/NPC/NPC.h"
#include "Kismet/KismetMathLibrary.h"

void UNPCAnimInstance::UpadeAnimationProperties(float DeltaTime)
{
	if (NPC == nullptr)
	{
		NPC = Cast<ANPC>(TryGetPawnOwner());
	}

	if (NPC)
	{
		//lateral speed of NPC from velocity
		FVector Velocity{ NPC->GetVelocity() };		//getting velocity of char (like in blueprint)
		Velocity.Z = 0;									//zero out the Z velocity
		Speed = Velocity.Size();						//assign speed to char's velocity

		
		const FRotator AimRotation = NPC->GetBaseAimRotation();													//get offset yaw used in blendSpace
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(NPC->GetVelocity());					//getting the rotation direction of aim

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		//StateRef = NPC->MyNPCState;																			//
	}
}
