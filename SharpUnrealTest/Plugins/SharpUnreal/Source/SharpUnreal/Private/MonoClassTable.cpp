#include "SharpUnrealPrivatePCH.h"
#include "MonoClassTable.h"

#include "Components/ApplicationLifecycleComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/DecalComponent.h"
#include "Components/MaterialBillboardComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/VectorFieldComponent.h"
#include "GameFrameWork/NavMovementComponent.h"
#include "GameFrameWork/PawnMovementComponent.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "GameFrameWork/RotatingMovementComponent.h"


#include "Camera/CameraComponent.h"

#include "MonoComponent.h"

static TMap<FName, UClass*> g_ClassTable;

void MonoClassTable::CreateTable()
{
	g_ClassTable.Add(FName(TEXT("MonoComponent")), UMonoComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("ActorComponent")), UActorComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("AudioComponent")), UAudioComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("AppLifecycleComponent")), UApplicationLifecycleComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("CameraComponent")), UCameraComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("PrimitiveComponent")), UPrimitiveComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("SceneComponent")), USceneComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("BoxComponent")), UBoxComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("CapsuleComponent")), UCapsuleComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("ShapeComponent")), UShapeComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("SphereComponent")), USphereComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("DirectionalLightComponent")), UDirectionalLightComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("LightComponent")), ULightComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("PointLightComponent")), UPointLightComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("SkyLightComponent")), USkyLightComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("SpotLightComponent")), USpotLightComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("DecalComponent")), UDecalComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("MaterialBillboardComponent")), UMaterialBillboardComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("MeshComponent")), UMeshComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("ParticleSystemComponent")), UParticleSystemComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("SkeletalMeshComponent")), USkeletalMeshComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("SkinnedMeshComponent")), USkinnedMeshComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("SplineMeshComponent")), USplineMeshComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("StaticMeshComponent")), UStaticMeshComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("TextRenderComponent")), UTextRenderComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("VectorFieldComponent")), UVectorFieldComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("InterpToMovementComponent")), UInterpToMovementComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("MovementComponent")), UMovementComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("NavMovementComponent")), UNavMovementComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("PawnMovementComponent")), UPawnMovementComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("ProjectileMovementComponent")), UProjectileMovementComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("RotatingMovementComponent")), URotatingMovementComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("SplineComponent")), USplineComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("SplineMeshMovementComponent")), USplineMeshComponent::StaticClass());
	g_ClassTable.Add(FName(TEXT("InputComponent")), UInputComponent::StaticClass());

}

void MonoClassTable::DestroyTable()
{
	g_ClassTable.Empty();
}

UClass* MonoClassTable::GetUClassFromName(const FName& name)
{
	if (g_ClassTable.Contains(name)) 
	{
		return g_ClassTable[name];
	}
	return NULL;
}