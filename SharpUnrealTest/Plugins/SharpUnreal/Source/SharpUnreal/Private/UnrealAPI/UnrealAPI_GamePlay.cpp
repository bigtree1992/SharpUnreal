#include "SharpUnrealPrivatePCH.h"
#include "LevelSequenceActor.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "AI/Navigation/NavigationSystem.h"

#include "UnrealAPI_GamePlay.h"
#include "MonoClassTable.h"
#include "MonoComponent.h"

#include <mono/jit/jit.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/image.h>
#include <mono/metadata/class.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/tokentype.h>
#include <mono/utils/mono-counters.h>
#include <mono/utils/mono-logger.h>
#include <mono/metadata/mono-debug.h>


static mono_bool UnrealEngine_Actor_HasTag(AActor* _this, MonoString* tag)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] HasTag But _this is NULL."));
		return false;
	}
	if (tag == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] HasTag But tag is NULL."));
		return false;
	}
	FName tag_name = FName((TCHAR*)mono_string_to_utf16(tag));
	return _this->ActorHasTag(tag_name);
}


static void UnrealEngine_Actor_AddTag(AActor* _this, MonoString* tag)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] AddTag But _this is NULL."));
		return;
	}
	if (tag == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] AddTag But tag is NULL."));
		return;
	}
	FName tag_name = FName((TCHAR*)mono_string_to_utf16(tag));
	_this->Tags.Add(tag_name);
}


static void UnrealEngine_Actor_RemoveTag(AActor* _this, MonoString* tag)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] RemoveTag But _this is NULL."));
		return;
	}
	if (tag == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] RemoveTag But tag is NULL."));
		return;
	}
	FName tag_name = FName((TCHAR*)mono_string_to_utf16(tag));
	_this->Tags.Remove(tag_name);
}

static mono_bool UnrealEngine_Actor_GetHiddenInGame(AActor* _this)
{
	if (_this == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetHiddenInGame But _this is NULL."));
		return false;
	}
	return _this->bHidden;
}

static void UnrealEngine_Actor_SetHiddenInGame(AActor* _this,mono_bool hidden)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] SetHiddenInGame But _this is NULL."));
		return;
	}
	return _this->SetActorHiddenInGame(hidden != 0);
}

static USceneComponent* UnrealEngine_Actor_GetSceneComponent(AActor* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetSceneComponent But _this is NULL."));
		return NULL;
	}
	return _this->GetRootComponent();
}

static void UnrealEngine_Actor_SetSceneComponent(AActor* _this, USceneComponent* root)
{
	if (_this == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] SetSceneComponent But _this is NULL."));
		return;
	}
	if (root == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] SetSceneComponent But root is NULL."));
		return;
	}
	_this->SetRootComponent(root);
}

static _MonoObject* UnrealEngine_Actor_GetMonoComponent(AActor* _this) 
{
	UMonoComponent* comp = (UMonoComponent*)_this->GetComponentByClass(UMonoComponent::StaticClass());
	if (comp != NULL) 
	{
		return comp->GetMonoObject();
	}
	return NULL;
}

static UActorComponent* UnrealEngine_Actor_GetComponent(AActor* _this, MonoString* type)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetComponent But _this is NULL."));
		return NULL;
	}

	FName type_name = FName((TCHAR*)mono_string_to_utf16(type));
	UClass* type_class = MonoClassTable::GetUClassFromName(type_name);
	if (type_class == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetComponent But No Class Found."));
		return NULL;
	}

	return _this->GetComponentByClass(type_class);
}

static UActorComponent* UnrealEngine_Actor_GetComponentByTag(AActor* _this, MonoString* type,MonoString* tag)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetComponentByTag But _this is NULL."));
		return NULL;
	}

	FName tag_name = FName((TCHAR*)mono_string_to_utf16(tag));
	FName type_name = FName((TCHAR*)mono_string_to_utf16(type));
	UClass* type_class = MonoClassTable::GetUClassFromName(type_name);
	
	auto components = _this->GetComponentsByTag(UActorComponent::StaticClass(), tag_name);
	for (int32 i = 0; i < components.Num(); i++)
	{
		auto component = components[i];
		if (component != NULL)
		{
			if (component->GetClass()->IsChildOf(type_class))
			{
				return component;
			}
		}
	}
	return NULL;
}

static void UnrealEngine_Actor_Destroy(AActor* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] Destroy But _this is NULL."));
		return;
	}
	_this->Destroy();
}

static MonoString* UnrealEngine_Actor_GetName(AActor* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetName But _this is NULL."));
		return NULL;
	}
	return mono_string_from_utf16((mono_unichar2*)*_this->GetName());
}

static ULevelSequencePlayer* UnrealEngine_Actor_GetSequencer(AActor* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetSequencer But _this is NULL."));
		return NULL;
	}

	if (!_this->IsA(ALevelSequenceActor::StaticClass()) )
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetSequencer _this Not is LevelSequenceActor."));
		return NULL;
	}

	ALevelSequenceActor* seq_actor = CastChecked<ALevelSequenceActor>(_this);
	if (seq_actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetSequencer _this Cast To LevelSequenceActor Failed."));
		return NULL;
	}

	return seq_actor->SequencePlayer;
}

static UIntProperty* UnrealEngine_Actor_FindIntProperty(AActor* _this, MonoString* name)
{	
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindIntProperty But _this is NULL."));
		return NULL;
	}

	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindIntProperty But name is NULL."));
		return NULL;
	}

	FName pname = FName((TCHAR*)mono_string_to_utf16(name));
	UProperty* property = _this->GetClass()->FindPropertyByName(pname);	
	UIntProperty* IntProperty = Cast<UIntProperty>(property);
	
	return IntProperty;
}

static UFloatProperty* UnrealEngine_Actor_FindFloatProperty(AActor* _this, MonoString* name)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindFloatProperty But _this is NULL."));
		return NULL;
	}

	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindFloatProperty But name is NULL."));
		return NULL;
	}

	FName pname = FName((TCHAR*)mono_string_to_utf16(name));
	UProperty* property = _this->GetClass()->FindPropertyByName(pname);
	UFloatProperty* FloatProperty = Cast<UFloatProperty>(property);

	return FloatProperty;
}

static UStrProperty* UnrealEngine_Actor_FindStringProperty(AActor* _this, MonoString* name)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindStringProperty But _this is NULL."));
		return NULL;
	}

	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindStringProperty But name is NULL."));
		return NULL;
	}

	FName pname = FName((TCHAR*)mono_string_to_utf16(name));
	UProperty* property = _this->GetClass()->FindPropertyByName(pname);
	UStrProperty* StringProperty = Cast<UStrProperty>(property);
	return StringProperty;
}

static UStructProperty* UnrealEngine_Actor_FindVectorProperty(AActor* _this, MonoString* name)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindVectorProperty But _this is NULL."));
		return NULL;
	}

	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindVectorProperty But name is NULL."));
		return NULL;
	}

	FName pname = FName((TCHAR*)mono_string_to_utf16(name));
	UProperty* property = _this->GetClass()->FindPropertyByName(pname);
	UStructProperty* VectorProperty = Cast<UStructProperty>(property);

	return VectorProperty;
}

static UStructProperty* UnrealEngine_Actor_FindRotatorProperty(AActor* _this, MonoString* name)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindRotatorProperty But _this is NULL."));
		return NULL;
	}

	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindRotatorProperty But name is NULL."));
		return NULL;
	}

	FName pname = FName((TCHAR*)mono_string_to_utf16(name));
	UProperty* property = _this->GetClass()->FindPropertyByName(pname);
	UStructProperty* RotatorProperty = Cast<UStructProperty>(property);

	return RotatorProperty;
}

static UStructProperty* UnrealEngine_Actor_FindQuatProperty(AActor* _this, MonoString* name)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindQuatProperty But _this is NULL."));
		return NULL;
	}

	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindQuatProperty But name is NULL."));
		return NULL;
	}

	FName pname = FName((TCHAR*)mono_string_to_utf16(name));
	UProperty* property = _this->GetClass()->FindPropertyByName(pname);
	UStructProperty* QuatProperty = Cast<UStructProperty>(property);

	return QuatProperty;
}

static UStructProperty* UnrealEngine_Actor_FindTransformProperty(AActor* _this, MonoString* name)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindTransformProperty But _this is NULL."));
		return NULL;
	}

	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] FindTransformProperty But name is NULL."));
		return NULL;
	}

	FName pname = FName((TCHAR*)mono_string_to_utf16(name));
	UProperty* property = _this->GetClass()->FindPropertyByName(pname);
	UStructProperty* TransformProperty = Cast<UStructProperty>(property);

	return TransformProperty;
}

static void UnrealEngine_Pawn_AddMovementInput(APawn* _this, FVector worldDir, float scaleValue, mono_bool force)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[APawn] AddMovementInput But _this is NULL."));
		return ;
	}
	_this->AddMovementInput(worldDir, scaleValue, force != 0);
}

static void UnrealEngine_Pawn_AddControllerPitchInput(APawn* _this, float Val)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[APawn] AddControllerPitchInput But _this is NULL."));
		return;
	}
	_this->AddControllerPitchInput(Val);
}

static void UnrealEngine_Pawn_AddControllerYawInput(APawn* _this, float Val)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[APawn] AddControllerYawInput But _this is NULL."));
		return;
	}
	_this->AddControllerYawInput(Val);
}

static void UnrealEngine_Pawn_AddControllerRollInput(APawn* _this, float Val)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[APawn] AddControllerRollInput But _this is NULL."));
		return;
	}
	_this->AddControllerRollInput(Val);
}

static UPawnMovementComponent* UnrealEngine_Pawn_GetMovementComponent(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[APawn] GetMovementComponent But _this is NULL."));
		return NULL;
	}

	return _this->GetMovementComponent();
}

static mono_bool UnrealEngine_Pawn_GetUseCtrlRotationPith(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[APawn] GetUseCtrlRotationPith But _this is NULL."));
		return 0;
	}

	return _this->bUseControllerRotationPitch;
}

static void UnrealEngine_Pawn_SetUseCtrlRotationPith(APawn* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[APawn] SetUseCtrlRotationPith But _this is NULL."));
		return;
	}
	_this->bUseControllerRotationPitch = value != 0;
}

static mono_bool UnrealEngine_Pawn_GetUseCtrlRotationYaw(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[APawn] GetUseCtrlRotationYaw But _this is NULL."));
		return 0;
	}
	return _this->bUseControllerRotationYaw;
}

static void UnrealEngine_Pawn_SetUseCtrlRotationYaw(APawn* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[APawn] SetUseCtrlRotationYaw But _this is NULL."));
		return;
	}
	_this->bUseControllerRotationYaw = value != 0;
}

static mono_bool UnrealEngine_Pawn_GetUseCtrlRotationRoll(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[APawn] GetUseCtrlRotationRoll But _this is NULL."));
		return 0;
	}
	return _this->bUseControllerRotationRoll;
}

static void UnrealEngine_Pawn_SetUseCtrlRotationRoll(APawn* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[APawn] SetUseCtrlRotationRoll But _this is NULL."));
		return;
	}

	_this->bUseControllerRotationRoll = value != 0;
}

static mono_bool UnrealEngine_Pawn_GetCanAffectNavigationGeneration(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetCanAffectNavigationGeneration But _this is NULL."));
		return 0;
	}
	return _this->bCanAffectNavigationGeneration;
}

static void UnrealEngine_Pawn_SetCanAffectNavigationGeneration(APawn* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] SetCanAffectNavigationGeneration But _this is NULL."));
		return;
	}
	_this->bCanAffectNavigationGeneration = value != 0;
}

static float UnrealEngine_Pawn_GetBaseEyeHeight(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetBaseEyeHeight But _this is NULL."));
		return 0.0f;
	}
	return _this->BaseEyeHeight;
}

static void UnrealEngine_Pawn_SetBaseEyeHeight(APawn* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] SetBaseEyeHeight But _this is NULL."));
		return;
	}
	_this->BaseEyeHeight = value;
}

static mono_bool UnrealEngine_Pawn_GetIsControlled(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetIsControlled But _this is NULL."));
		return 0;
	}
	return _this->IsControlled();
}

static AController* UnrealEngine_Pawn_GetController(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetController But _this is NULL."));
		return NULL;
	}
	return _this->GetController();
}

static AAIController* UnrealEngine_Pawn_GetAIController(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetController But _this is NULL."));
		return NULL;
	}

	return Cast<AAIController>(_this->GetController());
}

static FRotator UnrealEngine_Pawn_GetControllerRatator(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetControllerRatator But _this is NULL."));
		return FRotator::ZeroRotator;
	}

	return _this->GetControlRotation();
}

static FVector UnrealEngine_Pawn_GetNavAgentLocatioin(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetNavAgentLocatioin But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetNavAgentLocation();
}

static FRotator UnrealEngine_Pawn_GetBaseAimRotaion(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetBaseAimRotaion But _this is NULL."));
		return FRotator::ZeroRotator;
	}
	return _this->GetBaseAimRotation();
}

static FVector UnrealEngine_Pawn_GetPendingMovementInputVector(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetPendingMovementInputVector But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetPendingMovementInputVector();
}

static FVector UnrealEngine_Pawn_GetLastMovementInputVector(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetLastMovementInputVector But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetLastMovementInputVector();
}

static FVector UnrealEngine_Pawn_GetConsumeMovementInputVector(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetConsumeMovementInputVector But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->ConsumeMovementInputVector();
}

static mono_bool UnrealEngine_Pawn_GetIsMoveInputIgnored(APawn* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Pawn] GetIsMoveInputIgnored But _this is NULL."));
		return 0;
	}
	return _this->IsMoveInputIgnored();
}

static void UnrealEngine_Controller_SetInitialLocationAndRotation(AController* _this, FVector NewLocation, FRotator NewRotation)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] SetInitialLocationAndRotation But _this is NULL."));
		return;
	}
	_this->SetInitialLocationAndRotation(NewLocation, NewRotation);
}

static mono_bool UnrealEngine_Controller_LineOfSightTo(AController* _this, AActor* Other, FVector ViewPoint, mono_bool bAlternateChecks)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] LineOfSightTo But _this is NULL."));
		return 0;
	}
	
	if (Other == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] LineOfSightTo But Other is NULL."));
		return 0;
	}

	return _this->LineOfSightTo(Other, ViewPoint, bAlternateChecks != 0);
}

static void UnrealEngine_Controller_StopMovement(AController* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] StopMovement But _this is NULL."));
		return;
	}

	_this->StopMovement();
}

static FRotator UnrealEngine_Controller_GetControllerRotator(AController* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] GetControllerRotator But _this is NULL."));
		return FRotator::ZeroRotator;
	}

	return _this->GetControlRotation();
}

static void UnrealEngine_Controller_SetControllerRotator(AController* _this, FRotator value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] SetControllerRotator But _this is NULL."));
		return;
	}

	_this->SetControlRotation(value);
}


static mono_bool UnrealEngine_Controller_GetIgnoreMoveInput(AController* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] GetIgnoreMoveInput But _this is NULL."));
		return 0;
	}
	return _this->IsMoveInputIgnored();
}

static void UnrealEngine_Controller_SetIgnoreMoveInput(AController* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] SetIgnoreMoveInput But _this is NULL."));
		return;
	}
	_this->SetIgnoreMoveInput ( value != 0);
}

static mono_bool UnrealEngine_Controller_GetIgnoreLookInput(AController* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] GetIgnoreLookInput But _this is NULL."));
		return 0;
	}
	return _this->IsLookInputIgnored() != 0;
}

static void UnrealEngine_Controller_SetIgnoreLookInput(AController* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] SetIgnoreLookInput But _this is NULL."));
		return;
	}
	_this->SetIgnoreLookInput(value != 0);
}

static void UnrealEngine_Controller_SimpleMoveToActor(AController* _this, AActor* Goal)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] SimpleMoveToActor But _this is NULL."));
	}

	if (Goal == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] SimpleMoveToActor But Goal is NULL."));
	}
	UNavigationSystem::SimpleMoveToActor(_this, Goal);
}

static void UnrealEngine_Controller_SimpleMoveToLocation(AController* _this, FVector Goal)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Controller] SimpleMoveToLocation But _this is NULL."));
	}

	UNavigationSystem::SimpleMoveToLocation(_this, Goal);
}

static EPathFollowingRequestResult::Type UnrealEngine_AIController_MoveToActor(AAIController* _this, AActor* actor, float accepanceRadius, mono_bool stopOnOverlap, mono_bool usePathfinding, mono_bool bCanStrafe, mono_bool allowPartialPath)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] MoveToActor But _this is NULL."));
		return EPathFollowingRequestResult::Type::Failed;
	}

	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] MoveToActor But actor is NULL."));
		return EPathFollowingRequestResult::Type::Failed;
	}

	return _this->MoveToActor(actor, accepanceRadius, stopOnOverlap !=0, usePathfinding!=0, bCanStrafe!=0, NULL,allowPartialPath != 0);
}

static EPathFollowingRequestResult::Type UnrealEngine_AIController_MoveToLocation(
	AAIController* _this, FVector actor, float accepanceRadius, mono_bool stopOnOverlap, mono_bool usePathfinding, 
	bool bProjectDestinationToNavigation, mono_bool bCanStrafe, mono_bool allowPartialPath)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] MoveToLocation But _this is NULL."));
		return EPathFollowingRequestResult::Type::Failed;
	}
	return _this->MoveToLocation(actor, accepanceRadius, stopOnOverlap!=0, usePathfinding!=0,
		bProjectDestinationToNavigation!=0,bCanStrafe !=0,NULL,allowPartialPath != 0);
}

static FVector UnrealEngine_AIController_GetFocalPointOnActor(AAIController* _this, AActor* actor)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] GetFocalPointOnActor But _this is NULL."));
		return FVector::ZeroVector;
	}

	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] GetFocalPointOnActor But actor is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetFocalPointOnActor(actor);
}

static void UnrealEngine_AIController_SetMoveBlockDetection(AAIController* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] SetMoveBlockDetection But _this is NULL."));
		return;
	}
	_this->SetMoveBlockDetection(value != 0);
}

static EPathFollowingStatus::Type UnrealEngine_AIController_GetMoveStatus(AAIController* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] GetMoveStatus But _this is NULL."));
		return EPathFollowingStatus::Type::Idle;
	}
	return _this->GetMoveStatus();
}

static mono_bool UnrealEngine_AIController_GetHasPartialPath(AAIController* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] GetHasPartialPath But _this is NULL."));
		return 0;
	}
	return _this->HasPartialPath();
}

static FVector UnrealEngine_AIController_GetImmediateMoveDestination(AAIController* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] GetImmediateMoveDestination But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetImmediateMoveDestination();
}

static FVector UnrealEngine_AIController_GetFocalPoint(AAIController* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] GetFocalPoint But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetFocalPoint();
}

static void UnrealEngine_AIController_SetFocalPoint(AAIController* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] SetFocalPoint But _this is NULL."));
		return;
	}
	return _this->SetFocalPoint(value);
}

static AActor* UnrealEngine_AIController_GetFocusActor(AAIController* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] GetFocusActor But _this is NULL."));
		return NULL;
	}
	return _this->GetFocusActor();
}

static void UnrealEngine_AIController_SetFocusActor(AAIController* _this, AActor* value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] SetFocusActor But _this is NULL."));
		return;
	}
	if (value == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AIController] SetFocusActor But actor is NULL."));
		return;
	}
	_this->SetFocus(value);
}


void UnrealAPI_GamePlay::RegisterAPI()
{
	mono_add_internal_call("UnrealEngine.Actor::_HasTag",
		reinterpret_cast<void*>(UnrealEngine_Actor_HasTag));
	mono_add_internal_call("UnrealEngine.Actor::_AddTag",
		reinterpret_cast<void*>(UnrealEngine_Actor_AddTag));
	mono_add_internal_call("UnrealEngine.Actor::_RemoveTag",
		reinterpret_cast<void*>(UnrealEngine_Actor_RemoveTag));

	mono_add_internal_call("UnrealEngine.Actor::_GetHiddenInGame",
		reinterpret_cast<void*>(UnrealEngine_Actor_GetHiddenInGame));
	mono_add_internal_call("UnrealEngine.Actor::_SetHiddenInGame",
		reinterpret_cast<void*>(UnrealEngine_Actor_SetHiddenInGame));
	mono_add_internal_call("UnrealEngine.Actor::_GetSceneComponent",
		reinterpret_cast<void*>(UnrealEngine_Actor_GetSceneComponent));
	mono_add_internal_call("UnrealEngine.Actor::_SetSceneComponent",
		reinterpret_cast<void*>(UnrealEngine_Actor_SetSceneComponent)); 
	mono_add_internal_call("UnrealEngine.Actor::_GetMonoComponent",
			reinterpret_cast<void*>(UnrealEngine_Actor_GetMonoComponent));
	mono_add_internal_call("UnrealEngine.Actor::_GetComponent",
		reinterpret_cast<void*>(UnrealEngine_Actor_GetComponent));
	mono_add_internal_call("UnrealEngine.Actor::_GetComponentByTag",
		reinterpret_cast<void*>(UnrealEngine_Actor_GetComponentByTag));
	mono_add_internal_call("UnrealEngine.Actor::_Destroy",
		reinterpret_cast<void*>(UnrealEngine_Actor_Destroy));
	mono_add_internal_call("UnrealEngine.Actor::_GetName",
		reinterpret_cast<void*>(UnrealEngine_Actor_GetName));
	mono_add_internal_call("UnrealEngine.Actor::_GetSequencer",
		reinterpret_cast<void*>(UnrealEngine_Actor_GetSequencer)); 

	mono_add_internal_call("UnrealEngine.Actor::_FindIntProperty",
		reinterpret_cast<void*>(UnrealEngine_Actor_FindIntProperty));
	mono_add_internal_call("UnrealEngine.Actor::_FindFloatProperty",
		reinterpret_cast<void*>(UnrealEngine_Actor_FindFloatProperty));
	mono_add_internal_call("UnrealEngine.Actor::_FindStringProperty",
		reinterpret_cast<void*>(UnrealEngine_Actor_FindStringProperty));
	mono_add_internal_call("UnrealEngine.Actor::_FindVectorProperty",
		reinterpret_cast<void*>(UnrealEngine_Actor_FindVectorProperty));
	mono_add_internal_call("UnrealEngine.Actor::_FindRotatorProperty",
		reinterpret_cast<void*>(UnrealEngine_Actor_FindRotatorProperty));
	mono_add_internal_call("UnrealEngine.Actor::_FindQuatProperty",
		reinterpret_cast<void*>(UnrealEngine_Actor_FindQuatProperty));
	mono_add_internal_call("UnrealEngine.Actor::_FindTransformProperty",
		reinterpret_cast<void*>(UnrealEngine_Actor_FindTransformProperty));


	mono_add_internal_call("UnrealEngine.Pawn::_AddMovementInput",
		reinterpret_cast<void*>(UnrealEngine_Pawn_AddMovementInput));
	mono_add_internal_call("UnrealEngine.Pawn::_AddControllerPitchInput",
		reinterpret_cast<void*>(UnrealEngine_Pawn_AddControllerPitchInput));
	mono_add_internal_call("UnrealEngine.Pawn::_AddControllerYawInput",
		reinterpret_cast<void*>(UnrealEngine_Pawn_AddControllerYawInput));
	mono_add_internal_call("UnrealEngine.Pawn::_AddControllerRollInput",
		reinterpret_cast<void*>(UnrealEngine_Pawn_AddControllerRollInput));
	mono_add_internal_call("UnrealEngine.Pawn::_GetMovementComponent",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetMovementComponent));
	mono_add_internal_call("UnrealEngine.Pawn::_GetUseCtrlRotationPith",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetUseCtrlRotationPith));
	mono_add_internal_call("UnrealEngine.Pawn::_SetUseCtrlRotationPith",
		reinterpret_cast<void*>(UnrealEngine_Pawn_SetUseCtrlRotationPith));
	mono_add_internal_call("UnrealEngine.Pawn::_GetUseCtrlRotationYaw",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetUseCtrlRotationYaw));
	mono_add_internal_call("UnrealEngine.Pawn::_SetUseCtrlRotationYaw",
		reinterpret_cast<void*>(UnrealEngine_Pawn_SetUseCtrlRotationYaw));
	mono_add_internal_call("UnrealEngine.Pawn::_GetUseCtrlRotationRoll",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetUseCtrlRotationRoll));
	mono_add_internal_call("UnrealEngine.Pawn::_SetUseCtrlRotationRoll",
		reinterpret_cast<void*>(UnrealEngine_Pawn_SetUseCtrlRotationRoll));
	mono_add_internal_call("UnrealEngine.Pawn::_GetCanAffectNavigationGeneration",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetCanAffectNavigationGeneration));
	mono_add_internal_call("UnrealEngine.Pawn::_SetCanAffectNavigationGeneration",
		reinterpret_cast<void*>(UnrealEngine_Pawn_SetCanAffectNavigationGeneration));
	mono_add_internal_call("UnrealEngine.Pawn::_GetBaseEyeHeight",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetBaseEyeHeight));
	mono_add_internal_call("UnrealEngine.Pawn::_SetBaseEyeHeight",
		reinterpret_cast<void*>(UnrealEngine_Pawn_SetBaseEyeHeight));
	mono_add_internal_call("UnrealEngine.Pawn::_GetIsControlled",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetIsControlled));
	mono_add_internal_call("UnrealEngine.Pawn::_GetController",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetController));
	mono_add_internal_call("UnrealEngine.Pawn::_GetAIController",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetAIController));
	mono_add_internal_call("UnrealEngine.Pawn::_GetControllerRatator",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetControllerRatator));
	mono_add_internal_call("UnrealEngine.Pawn::_GetNavAgentLocatioin",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetNavAgentLocatioin));
	mono_add_internal_call("UnrealEngine.Pawn::_GetBaseAimRotaion",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetBaseAimRotaion));
	mono_add_internal_call("UnrealEngine.Pawn::_GetPendingMovementInputVector",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetPendingMovementInputVector));
	mono_add_internal_call("UnrealEngine.Pawn::_GetLastMovementInputVector",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetLastMovementInputVector));
	mono_add_internal_call("UnrealEngine.Pawn::_GetConsumeMovementInputVector",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetConsumeMovementInputVector));
	mono_add_internal_call("UnrealEngine.Pawn::_GetIsMoveInputIgnored",
		reinterpret_cast<void*>(UnrealEngine_Pawn_GetIsMoveInputIgnored));

	mono_add_internal_call("UnrealEngine.Controller::_SetInitialLocationAndRotation",
		reinterpret_cast<void*>(UnrealEngine_Controller_SetInitialLocationAndRotation));
	mono_add_internal_call("UnrealEngine.Controller::_LineOfSightTo",
		reinterpret_cast<void*>(UnrealEngine_Controller_LineOfSightTo));
	mono_add_internal_call("UnrealEngine.Controller::_StopMovement",
		reinterpret_cast<void*>(UnrealEngine_Controller_StopMovement));
	mono_add_internal_call("UnrealEngine.Controller::_GetControllerRotator",
		reinterpret_cast<void*>(UnrealEngine_Controller_GetControllerRotator));
	mono_add_internal_call("UnrealEngine.Controller::_SetControllerRotator",
		reinterpret_cast<void*>(UnrealEngine_Controller_SetControllerRotator));
	mono_add_internal_call("UnrealEngine.Controller::_GetIgnoreMoveInput",
		reinterpret_cast<void*>(UnrealEngine_Controller_GetIgnoreMoveInput));
	mono_add_internal_call("UnrealEngine.Controller::_SetIgnoreMoveInput",
		reinterpret_cast<void*>(UnrealEngine_Controller_SetIgnoreMoveInput));
	mono_add_internal_call("UnrealEngine.Controller::_GetIgnoreLookInput",
		reinterpret_cast<void*>(UnrealEngine_Controller_GetIgnoreLookInput));
	mono_add_internal_call("UnrealEngine.Controller::_SetIgnoreLookInput",
		reinterpret_cast<void*>(UnrealEngine_Controller_SetIgnoreLookInput));
	mono_add_internal_call("UnrealEngine.Controller::_SimpleMoveToActor",
		reinterpret_cast<void*>(UnrealEngine_Controller_SimpleMoveToActor));
	mono_add_internal_call("UnrealEngine.Controller::_SimpleMoveToLocation",
		reinterpret_cast<void*>(UnrealEngine_Controller_SimpleMoveToLocation)); 

	mono_add_internal_call("UnrealEngine.AIController::_MoveToActor",
		reinterpret_cast<void*>(UnrealEngine_AIController_MoveToActor));
	mono_add_internal_call("UnrealEngine.AIController::_MoveToLocation",
		reinterpret_cast<void*>(UnrealEngine_AIController_MoveToLocation));
	mono_add_internal_call("UnrealEngine.AIController::_GetFocalPointOnActor",
		reinterpret_cast<void*>(UnrealEngine_AIController_GetFocalPointOnActor));
	mono_add_internal_call("UnrealEngine.AIController::_SetMoveBlockDetection",
		reinterpret_cast<void*>(UnrealEngine_AIController_SetMoveBlockDetection));
	mono_add_internal_call("UnrealEngine.AIController::_GetMoveStatus",
		reinterpret_cast<void*>(UnrealEngine_AIController_GetMoveStatus));
	mono_add_internal_call("UnrealEngine.AIController::_GetHasPartialPath",
		reinterpret_cast<void*>(UnrealEngine_AIController_GetHasPartialPath));
	mono_add_internal_call("UnrealEngine.AIController::_GetImmediateMoveDestination",
		reinterpret_cast<void*>(UnrealEngine_AIController_GetImmediateMoveDestination));
	mono_add_internal_call("UnrealEngine.AIController::_GetFocalPoint",
		reinterpret_cast<void*>(UnrealEngine_AIController_GetFocalPoint));
	mono_add_internal_call("UnrealEngine.AIController::_SetFocalPoint",
		reinterpret_cast<void*>(UnrealEngine_AIController_SetFocalPoint));
	mono_add_internal_call("UnrealEngine.AIController::_GetFocusActor",
		reinterpret_cast<void*>(UnrealEngine_AIController_GetFocusActor));
	mono_add_internal_call("UnrealEngine.AIController::_SetFocusActor",
		reinterpret_cast<void*>(UnrealEngine_AIController_SetFocusActor));
}


