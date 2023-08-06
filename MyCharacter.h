#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "MyCharacter.generated.h"


UCLASS()
class AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;
 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* GrabAction;

	UPROPERTY(EditAnywhere, Category = "Grab")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;
 
	UPROPERTY(EditAnywhere, Category = "Grab")
	float TraceLenght = 200.f;
 
	UPROPERTY(EditDefaultsOnly, Category = "Grab")
	UPhysicsHandleComponent* PhysicsHandle;
 
	UPROPERTY(VisibleAnywhere, Category = "Grab")
	bool bIsGrabbingObject;
 
public:
	AMyCharacter();

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Move(const FInputActionValue& Value);
 
	void Look(const FInputActionValue& Value);
 
	void Grab(const FInputActionValue& Value);

 
};
