#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrabbableObject.generated.h"
 
UCLASS()
class GRABOBJECT_API AGrabbableObject : public AActor
{
	GENERATED_BODY()
	 
public:
	//Object Mesh
	UPROPERTY(EditAnywhere, Category = "Object Properties")
	UStaticMeshComponent* StaticMesh;
 
public:	

	AGrabbableObject();
 
public:	

	virtual void Tick(float DeltaTime) override;

  virtual void BeginPlay() override;
};
