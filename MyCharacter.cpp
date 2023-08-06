#include "MyCharacter.h"
#include "Animation/AnimInstance.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GrabbableObject.h"


AMyCharacter::AMyCharacter()
{	
	//Initialize collision
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Initialize CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

  // Initialize PhysicsHandle	
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
 
	PrimaryActorTick.bCanEverTick = true;
 
}
 
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
 
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
  
	bIsGrabbingObject = false; 
}
 
void AMyCharacter::Tick(float DeltaTime)
{
	if(bIsGrabbingObject == true)
	{
		PhysicsHandle->SetTargetLocationAndRotation(FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector() * TraceLength, FirstPersonCameraComponent->GetComponentRotation());
	}
}

//Initialize Input Component
void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
 
		//Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
 
		//Look
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
 
		//Grab
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Triggered, this, &AMyCharacter::Grab);
	}
}
 
 
void AMyCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
 
	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}
 
void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
 
void AMyCharacter::Grab(const FInputActionValue& Value)
{
	
	FHitResult Hit;
	FVector TraceStart = FirstPersonCameraComponent->GetComponentLocation();
	FVector TraceEnd = FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector() * TraceLength;
 
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
 
	// LineTrace
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);
	bool bHitSomething = Hit.bBlockingHit;
 
	if (Hit.bBlockingHit && !bIsGrabbingObject)
	{
		AActor* HitActor = Hit.GetActor();
		bool bIsValidActor = IsValid(HitActor);
		bool bGrabbableable =  HitActor->GetClass()->IsChildOf<AGrabbableObject>();
		
		if(bIsValidActor == true && bGrabbable == true)
		{
			UPrimitiveComponent* HitComponent = Hit.GetComponent();
			FVector HitComponentLocation = HitComponent->GetComponentLocation();
			FRotator HitComponentRotation = HitComponent->GetComponentRotation();
			PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitComponentLocation, HitComponentRotation);
 
			bIsGrabbingObject = true;
		}
	}
	
	else if(bIsGrabbingObject)
	{
		PhysicsHandle->ReleaseComponent();
		bIsGrabbingObject = false;
	}
}
