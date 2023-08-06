#include "GrabbableObject.h"
#include "GameFramework/Character.h"
 
AGrabbableObject::AGrabbableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  //Initialize Object Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
  RootComponent = StaticMesh;
	StaticMesh->SetSimulatePhysics(true);
	
 
}
 
// Called when the game starts or when spawned
void AGrabbableObject::BeginPlay()
{
	Super::BeginPlay();
	
}
 
// Called every frame
void AGrabbableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
 
}
