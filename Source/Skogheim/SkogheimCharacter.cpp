// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkogheimCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SkogheimProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// ASkogheimCharacter

ASkogheimCharacter::ASkogheimCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	bIsSprinting = false;
	bHasTrap = false;
	bUsingTrap = false;
	bTabOpen = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

}

void ASkogheimCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	

}

//////////////////////////////////////////////////////////////////////////// Input

void ASkogheimCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASkogheimCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASkogheimCharacter::Look);

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ASkogheimCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASkogheimCharacter::StopSprint);

		//Interaction
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ASkogheimCharacter::Interact);

		//Trapezohedron
		EnhancedInputComponent->BindAction(TrapAction, ETriggerEvent::Started, this, &ASkogheimCharacter::UseTrap);
		//EnhancedInputComponent->BindAction(TrapAction, ETriggerEvent::Completed, this, &ASkogheimCharacter::StopTrap);

		//Tab Menu
		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Started, this, &ASkogheimCharacter::TabUI);
	}
}

void ASkogheimCharacter::Interact()
{
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + FirstPersonCameraComponent->GetComponentRotation().Vector() * 500.f;

	FHitResult Hitresult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hitresult, Start, End, ECC_Visibility, Params ))			//linetrace
	{
		AActor* HitActor = Hitresult.GetActor();														//save actor that was hit
		UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), HitActor);										//log output of hit actor (to check if object is recognized by line trace)

		if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))	//if any actor was hit and it implements the INTERACT interface..
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, TEXT("Hit actor that implements interface"));
			IInteractInterface::Execute_OnInteract(HitActor);											//execute the OnInteract function on the respecting object which implements this fct
		}
	}
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3.0f, 0, 2.0f);
}

void ASkogheimCharacter::UseTrap()
{
	if (bHasTrap ) 
	{
		if (!bUsingTrap)
		{
			bUsingTrap = true;
			TrapEffect();
		}
		else 
		{
			bUsingTrap = false;
			TrapEffect();
		}
		
	}
}

//void ASkogheimCharacter::TabUI()
//{
//
//}

//void ASkogheimCharacter::OnInteract_Implementation()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, TEXT("OnInteract_Implementation"));
//}
//
//void ASkogheimCharacter::OnInteractPure()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, TEXT("OnInteractPure"));
//}


void ASkogheimCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ASkogheimCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASkogheimCharacter::Sprint()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, TEXT("Sprinting start"));
	if (GetCharacterMovement()) 
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void ASkogheimCharacter::StopSprint()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, TEXT("Sprinting STOP"));
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASkogheimCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ASkogheimCharacter::GetHasRifle()
{
	return bHasRifle;
}