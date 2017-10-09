// Fill out your copyright notice in the Description page of Project Settings.
#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "UnrealAPI_Movement.h"
#include "GameFramework/MovementComponent.h"
#include "Components/InterpToMovementComponent.h"

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

#if 1 // Movement
static void UnrealEngine_MovementComponent_StopMovement(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] StopMovement But _this is NULL."));
		return;
	}
	_this->StopMovementImmediately();
}

static mono_bool UnrealEngine_MovementComponent_IsExceedingMaxSpeed(UMovementComponent* _this, float MaxSpeed)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] IsExceedingMaxSpeed But _this is NULL."));
		return 0;
	}
	return _this->IsExceedingMaxSpeed(MaxSpeed);
}

static void UnrealEngine_MovementComponent_SetPlaneConstraintFromVectors(UMovementComponent* _this, FVector Forward, FVector Up)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] SetPlaneConstraintFromVectors But _this is NULL."));
		return;
	}
	_this->SetPlaneConstraintFromVectors(Forward, Up);
}

static FVector UnrealEngine_MovementComponent_ConstrainDirectionToPlane(UMovementComponent* _this, FVector Direction)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] ConstrainDirectionToPlane But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->ConstrainDirectionToPlane(Direction);
}

static FVector UnrealEngine_MovementComponent_ConstrainLocationToPlane(UMovementComponent* _this, FVector Location)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] ConstrainLocationToPlane But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->ConstrainLocationToPlane(Location);
}

static FVector UnrealEngine_MovementComponent_ConstrainNormalToPlane(UMovementComponent* _this, FVector Normal)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] ConstrainNormalToPlane But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->ConstrainNormalToPlane(Normal);
}

static FVector UnrealEngine_MovementComponent_GetVelocity(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] GetVelocity But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->Velocity;
}

static void UnrealEngine_MovementComponent_SetVelocity(UMovementComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] SetVelocity But _this is NULL."));
		return;
	}
	_this->Velocity = value;
}

static mono_bool UnrealEngine_MovementComponent_GetConstrainToPlane(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] GetConstrainToPlane But _this is NULL."));
		return 0;
	}
	return _this->bConstrainToPlane;
}

static void UnrealEngine_MovementComponent_SetConstrainToPlane(UMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] SetConstrainToPlane But _this is NULL."));
		return;
	}
	_this->bConstrainToPlane = value != 0;
}

static mono_bool UnrealEngine_MovementComponent_GetSnapToPlaneAtStart(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] GetSnapToPlaneAtStart But _this is NULL."));
		return 0;
	}
	return _this->bSnapToPlaneAtStart;
}

static EPlaneConstraintAxisSetting UnrealEngine_MovementComponent_GetPlaneConstraint(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] GetPlaneConstraint But _this is NULL."));
		return EPlaneConstraintAxisSetting::UseGlobalPhysicsSetting;
	}
	return _this->GetPlaneConstraintAxisSetting();
}

static void UnrealEngine_MovementComponent_SetPlaneConstraint(UMovementComponent* _this, EPlaneConstraintAxisSetting value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] SetPlaneConstraint But _this is NULL."));
		return;
	}
	_this->SetPlaneConstraintAxisSetting(value);
}

static FVector UnrealEngine_MovementComponent_GetPlaneConstraintNormal(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] GetPlaneConstraintNormal But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetPlaneConstraintNormal();
}

static void UnrealEngine_MovementComponent_SetPlaneConstraintNormal(UMovementComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] SetPlaneConstraintNormal But _this is NULL."));
		return;
	}
	_this->SetPlaneConstraintNormal(value);
}

static FVector UnrealEngine_MovementComponent_GetPlaneConstraintOrigin(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] GetPlaneConstraintOrigin But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetPlaneConstraintOrigin();
}

static void UnrealEngine_MovementComponent_SetPlaneConstraintOrigin(UMovementComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] SetPlaneConstraintOrigin But _this is NULL."));
		return;
	}
	_this->SetPlaneConstraintOrigin(value);
}

static mono_bool UnrealEngine_MovementComponent_GetUpdateOnlyIfRendered(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] GetUpdateOnlyIfRendered But _this is NULL."));
		return 0;
	}
	return _this->bUpdateOnlyIfRendered;
}

static void UnrealEngine_MovementComponent_SetUpdateOnlyIfRendered(UMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] SetUpdateOnlyIfRendered But _this is NULL."));
		return;
	}
	_this->bUpdateOnlyIfRendered = value != 0;
}

static float UnrealEngine_MovementComponent_GetGravityZ(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] GetGravityZ But _this is NULL."));
		return 0.0f;
	}
	return _this->GetGravityZ();
}

static float UnrealEngine_MovementComponent_GetMaxSpeed(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] GetMaxSpeed But _this is NULL."));
		return 0.0f;
	}
	return _this->GetMaxSpeed();
}

static float UnrealEngine_MovementComponent_GetMaxSpeedModifier(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] GetMaxSpeedModifier But _this is NULL."));
		return 0.0f;
	}
	return _this->GetMaxSpeedModifier();
}

static float UnrealEngine_MovementComponent_GetModifiedMaxSpeed(UMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MovementComponent] GetModifiedMaxSpeed But _this is NULL."));
		return 0.0f;
	}
	return _this->GetMaxSpeedModifier();
}
#endif

#if 1 //NavMovementComponent
static void UnrealEngine_NavMovementComponent_StopActiveMovement(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] StopActiveMovement But _this is NULL."));
		return;
	}
	_this->StopActiveMovement();
}

static void UnrealEngine_NavMovementComponent_StopMovementKeepPathing(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] StopMovementKeepPathing But _this is NULL."));
		return;
	}
	_this->StopMovementKeepPathing();
}

static mono_bool UnrealEngine_NavMovementComponent_GetCanCrouch(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetCanCrouch But _this is NULL."));
		return 0;
	}
	return _this->CanEverCrouch();
}

static void UnrealEngine_NavMovementComponent_SetCanCrouch(UNavMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] SetCanCrouch But _this is NULL."));
		return;
	}
	_this->NavAgentProps.bCanCrouch = value != 0;
}

static mono_bool UnrealEngine_NavMovementComponent_GetCanJump(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetCanJump But _this is NULL."));
		return 0;
	}
	return _this->CanEverJump();
}

static void UnrealEngine_NavMovementComponent_SetCanJump(UNavMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] SetCanJump But _this is NULL."));
		return;
	}
	_this->NavAgentProps.bCanJump = value != 0;
}

static mono_bool UnrealEngine_NavMovementComponent_GetCanWalk(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetCanWalk But _this is NULL."));
		return 0;
	}
	return _this->NavAgentProps.bCanWalk;
}

static void UnrealEngine_NavMovementComponent_SetCanWalk(UNavMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] SetCanWalk But _this is NULL."));
		return;
	}
	_this->NavAgentProps.bCanWalk = value != 0;
}

static mono_bool UnrealEngine_NavMovementComponent_GetCanSwim(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetCanSwim But _this is NULL."));
		return 0;
	}
	return _this->CanEverSwim();
}

static void UnrealEngine_NavMovementComponent_SetCanSwim(UNavMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] SetCanSwim But _this is NULL."));
		return;
	}
	_this->NavAgentProps.bCanSwim = value != 0;
}

static mono_bool UnrealEngine_NavMovementComponent_GetCanFly(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetCanFly But _this is NULL."));
		return 0;
	}
	return _this->CanEverFly();
}

static void UnrealEngine_NavMovementComponent_SetCanFly(UNavMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] SetCanFly But _this is NULL."));
		return;
	}
	_this->NavAgentProps.bCanFly = value;
}

static float UnrealEngine_NavMovementComponent_GetAgentRadius(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetAgentRadius But _this is NULL."));
		return 0.0f;
	}
	return _this->NavAgentProps.AgentRadius;
}

static void UnrealEngine_NavMovementComponent_SetAgentRadius(UNavMovementComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] SetAgentRadius But _this is NULL."));
		return;
	}
	_this->NavAgentProps.AgentRadius = value;
}

static float UnrealEngine_NavMovementComponent_GetAgentHeight(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetAgentHeight But _this is NULL."));
		return 0.0f;
	}
	return _this->NavAgentProps.AgentHeight;
}

static void UnrealEngine_NavMovementComponent_SetAgentHeight(UNavMovementComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] SetAgentHeight But _this is NULL."));
		return;
	}
	_this->NavAgentProps.AgentHeight = value;
}

static float UnrealEngine_NavMovementComponent_GetAgentStepHeight(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetAgentStepHeight But _this is NULL."));
		return 0.0f;
	}
	return _this->NavAgentProps.AgentStepHeight;
}

static void UnrealEngine_NavMovementComponent_SetAgentStepHeight(UNavMovementComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] SetAgentStepHeight But _this is NULL."));
		return;
	}
	_this->NavAgentProps.AgentStepHeight = value;
}

static float UnrealEngine_NavMovementComponent_GetNavWalkingSearchHeightScale(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetNavWalkingSearchHeightScale But _this is NULL."));
		return 0.0f;
	}
	return _this->NavAgentProps.NavWalkingSearchHeightScale;
}

static void UnrealEngine_NavMovementComponent_SetNavWalkingSearchHeightScale(UNavMovementComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] SetNavWalkingSearchHeightScale But _this is NULL."));
		return;
	}
	_this->NavAgentProps.NavWalkingSearchHeightScale = value;
}

static mono_bool UnrealEngine_NavMovementComponent_GetIsCrouching(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetIsCrouching But _this is NULL."));
		return 0;
	}
	return _this->IsCrouching();
}

static mono_bool UnrealEngine_NavMovementComponent_GetIsFalling(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetIsFalling But _this is NULL."));
		return 0;
	}
	return _this->IsFalling();
}

static mono_bool UnrealEngine_NavMovementComponent_GetIsMovingOnGround(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetIsMovingOnGround But _this is NULL."));
		return 0;
	}
	return _this->IsMovingOnGround();
}

static mono_bool UnrealEngine_NavMovementComponent_GetIsSwimming(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetIsSwimming But _this is NULL."));
		return 0;
	}
	return _this->IsSwimming();
}

static mono_bool UnrealEngine_NavMovementComponent_GetIsFlying(UNavMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] GetIsFlying But _this is NULL."));
		return 0;
	}
	
	return _this->IsFlying();
}

static void UnrealEngine_NavMovementComponent_SetFixedBrakingDistance(UNavMovementComponent* _this, float distance) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[NavMovementComponent] SetFixedBrakingDistance But _this is NULL."));
		return;
	}
	_this->SetFixedBrakingDistance(distance);
}

#endif

#if 1 //PawnMovement
static void UnrealEngine_PawnMovementComponent_AddInputVector(UPawnMovementComponent* _this, FVector WorldVector, mono_bool bForce)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PawnMovementComponent] AddInputVector But _this is NULL."));
		return;
	}
	_this->AddInputVector(WorldVector, bForce != 0);
}

static FVector UnrealEngine_PawnMovementComponent_GetPendingInputVector(UPawnMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PawnMovementComponent] GetPendingInputVector But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetPendingInputVector();
}

static FVector UnrealEngine_PawnMovementComponent_GetLastInputVector(UPawnMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PawnMovementComponent] GetLastInputVector But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetLastInputVector();
}

static FVector UnrealEngine_PawnMovementComponent_GetConsumeInputVector(UPawnMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PawnMovementComponent] GetConsumeInputVector But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->ConsumeInputVector();
}

static mono_bool UnrealEngine_PawnMovementComponent_GetIsMoveInputIgnored(UPawnMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PawnMovementComponent] GetIsMoveInputIgnored But _this is NULL."));
		return 0;
	}
	return _this->IsMoveInputIgnored();
}
#endif

#if 1 //ProjectileMovement
static float UnrealEngine_ProjectileMovementComponent_GetInitialSpeed(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetInitialSpeed But _this is NULL."));
		return 0.0f;
	}
	return _this->InitialSpeed;
}

static void UnrealEngine_ProjectileMovementComponent_SetInitialSpeed(UProjectileMovementComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetInitialSpeed But _this is NULL."));
		return;
	}
	_this->InitialSpeed = value;
}

static mono_bool UnrealEngine_ProjectileMovementComponent_GetRotationFollowsVelocity(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetRotationFollowsVelocity But _this is NULL."));
		return 0;
	}
	return _this->bRotationFollowsVelocity != 0;
}

static void UnrealEngine_ProjectileMovementComponent_SetRotationFollowsVelocity(UProjectileMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetRotationFollowsVelocity But _this is NULL."));
		return;
	}
	_this->bRotationFollowsVelocity = value;
}

static mono_bool UnrealEngine_ProjectileMovementComponent_GetShouldBounce(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetShouldBounce But _this is NULL."));
		return 0;
	}
	return _this->bShouldBounce != 0;
}

static void UnrealEngine_ProjectileMovementComponent_SetShouldBounce(UProjectileMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetShouldBounce But _this is NULL."));
		return;
	}
	_this->bShouldBounce = value;
}

static mono_bool UnrealEngine_ProjectileMovementComponent_GetInitialVelocityInLocalSpace(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetInitialVelocityInLocalSpace But _this is NULL."));
		return 0;
	}
	return _this->bInitialVelocityInLocalSpace != 0;
}

static void UnrealEngine_ProjectileMovementComponent_SetInitialVelocityInLocalSpace(UProjectileMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetInitialVelocityInLocalSpace But _this is NULL."));
		return;
	}
	_this->bInitialVelocityInLocalSpace = value;
}

static mono_bool UnrealEngine_ProjectileMovementComponent_GetForceSubStepping(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetForceSubStepping But _this is NULL."));
		return 0;
	}
	return _this->bForceSubStepping;
}

static void UnrealEngine_ProjectileMovementComponent_SetForceSubStepping(UProjectileMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetForceSubStepping But _this is NULL."));
		return;
	}
	_this->bForceSubStepping = value;
}

static mono_bool UnrealEngine_ProjectileMovementComponent_GetIsHomingProjectile(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetIsHomingProjectile But _this is NULL."));
		return 0;
	}
	return _this->bIsHomingProjectile != 0;
}

static void UnrealEngine_ProjectileMovementComponent_SetIsHomingProjectile(UProjectileMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetIsHomingProjectile But _this is NULL."));
		return;
	}
	_this->bIsHomingProjectile = value;
}

static mono_bool UnrealEngine_ProjectileMovementComponent_GetBounceAngleAffectsFriction(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetBounceAngleAffectsFriction But _this is NULL."));
		return 0;
	}
	return _this->bBounceAngleAffectsFriction != 0;
}

static void UnrealEngine_ProjectileMovementComponent_SetBounceAngleAffectsFriction(UProjectileMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetBounceAngleAffectsFriction But _this is NULL."));
		return;
	}
	_this->bBounceAngleAffectsFriction = value;
}

static mono_bool UnrealEngine_ProjectileMovementComponent_GetIsSliding(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetIsSliding But _this is NULL."));
		return 0;
	}
	return _this->bIsSliding;
}

static void UnrealEngine_ProjectileMovementComponent_SetIsSliding(UProjectileMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetIsSliding But _this is NULL."));
		return;
	}
	_this->bIsSliding = value;
}

static float UnrealEngine_ProjectileMovementComponent_GetPreviousHitTime(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetPreviousHitTime But _this is NULL."));
		return 0.0f;
	}
	return _this->PreviousHitTime;
}

static void UnrealEngine_ProjectileMovementComponent_SetPreviousHitTime(UProjectileMovementComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetPreviousHitTime But _this is NULL."));
		return;
	}
	_this->PreviousHitTime = value;
}

static FVector UnrealEngine_ProjectileMovementComponent_GetPreviousHitNormal(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetPreviousHitNormal But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->PreviousHitNormal;
}

static void UnrealEngine_ProjectileMovementComponent_SetPreviousHitNormal(UProjectileMovementComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetPreviousHitNormal But _this is NULL."));
		return;
	}
	_this->PreviousHitNormal = value;
}

static float UnrealEngine_ProjectileMovementComponent_GetProjectileGravityScale(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetProjectileGravityScale But _this is NULL."));
		return 0.0f;
	}
	return _this->ProjectileGravityScale;
}

static void UnrealEngine_ProjectileMovementComponent_SetProjectileGravityScale(UProjectileMovementComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetProjectileGravityScale But _this is NULL."));
		return;
	}
	_this->ProjectileGravityScale = value;
}

static float UnrealEngine_ProjectileMovementComponent_GetBuoyancy(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetBuoyancy But _this is NULL."));
		return 0.0f;
	}
	return _this->Buoyancy;
}

static void UnrealEngine_ProjectileMovementComponent_SetBuoyancy(UProjectileMovementComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetBuoyancy But _this is NULL."));
		return;
	}
	_this->Buoyancy = value;
}

static float UnrealEngine_ProjectileMovementComponent_GetBounciness(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetBounciness But _this is NULL."));
		return 0.0f;
	}
	return _this->Bounciness;
}

static void UnrealEngine_ProjectileMovementComponent_SetBounciness(UProjectileMovementComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetBounciness But _this is NULL."));
		return;
	}
	_this->Bounciness = value;
}

static float UnrealEngine_ProjectileMovementComponent_GetFriction(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetFriction But _this is NULL."));
		return 0.0f;
	}
	return _this->Friction;
}

static void UnrealEngine_ProjectileMovementComponent_SetFriction(UProjectileMovementComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetFriction But _this is NULL."));
		return;
	}
	_this->Friction = value;
}

static float UnrealEngine_ProjectileMovementComponent_GetBounceVelocityStopSimulatingThreshold(UProjectileMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] GetBounceVelocityStopSimulatingThreshold But _this is NULL."));
		return 0.0f;
	}
	return _this->BounceVelocityStopSimulatingThreshold;
}

static void UnrealEngine_ProjectileMovementComponent_SetBounceVelocityStopSimulatingThreshold(UProjectileMovementComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ProjectileMovementComponent] SetBounceVelocityStopSimulatingThreshold But _this is NULL."));
		return;
	}
	_this->BounceVelocityStopSimulatingThreshold = value;

}
#endif

#if 1 //RotatingMovement
static FRotator UnrealEngine_RotatingMovementComponent_GetRotationRate(URotatingMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[RotatingMovementComponent] GetRotationRate But _this is NULL."));
		return FRotator::ZeroRotator;
	}
	return _this->RotationRate;
}

static void UnrealEngine_RotatingMovementComponent_SetRotationRate(URotatingMovementComponent* _this, FRotator value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[RotatingMovementComponent] SetRotationRate But _this is NULL."));
		return;
	}
	_this->RotationRate = value;
}

static FVector UnrealEngine_RotatingMovementComponent_GetPivotTranslation(URotatingMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[RotatingMovementComponent] GetPivotTranslation But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->PivotTranslation;
}

static void UnrealEngine_RotatingMovementComponent_SetPivotTranslation(URotatingMovementComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[RotatingMovementComponent] SetPivotTranslation But _this is NULL."));
		return;
	}
	_this->PivotTranslation = value;
}

static mono_bool UnrealEngine_RotatingMovementComponent_GetRotationInLocalSpace(URotatingMovementComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[RotatingMovementComponent] GetRotationInLocalSpace But _this is NULL."));
		return 0;
	}
	return _this->bRotationInLocalSpace;
}

static void UnrealEngine_RotatingMovementComponent_SetRotationInLocalSpace(URotatingMovementComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[RotatingMovementComponent] SetRotationInLocalSpace But _this is NULL."));
		return;
	}
	_this->bRotationInLocalSpace = value != 0;
}

#endif


static void UnrealEngine_InterpToMovementComponent_RestartMovement(UInterpToMovementComponent* _this, float InitialDirection)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[InterpToMovementComponent] RestartMovement But _this is NULL."));
		return;
	}
	_this->RestartMovement(InitialDirection);
}


void UnrealAPI_Movement::RegisterAPI() 
{
	mono_add_internal_call("UnrealEngine.MovementComponent::_StopMovement",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_StopMovement));
	mono_add_internal_call("UnrealEngine.MovementComponent::_IsExceedingMaxSpeed",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_IsExceedingMaxSpeed));
	mono_add_internal_call("UnrealEngine.MovementComponent::_SetPlaneConstraintFromVectors",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_SetPlaneConstraintFromVectors));
	mono_add_internal_call("UnrealEngine.MovementComponent::_ConstrainDirectionToPlane",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_ConstrainDirectionToPlane));
	mono_add_internal_call("UnrealEngine.MovementComponent::_ConstrainLocationToPlane",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_ConstrainLocationToPlane));
	mono_add_internal_call("UnrealEngine.MovementComponent::_ConstrainNormalToPlane",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_ConstrainNormalToPlane));
	mono_add_internal_call("UnrealEngine.MovementComponent::_GetVelocity",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_GetVelocity));
	mono_add_internal_call("UnrealEngine.MovementComponent::_SetVelocity",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_SetVelocity));
	mono_add_internal_call("UnrealEngine.MovementComponent::_GetConstrainToPlane",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_GetConstrainToPlane));
	mono_add_internal_call("UnrealEngine.MovementComponent::_SetConstrainToPlane",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_SetConstrainToPlane));
	mono_add_internal_call("UnrealEngine.MovementComponent::_GetSnapToPlaneAtStart",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_GetSnapToPlaneAtStart));
	mono_add_internal_call("UnrealEngine.MovementComponent::_GetPlaneConstraint",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_GetPlaneConstraint));
	mono_add_internal_call("UnrealEngine.MovementComponent::_SetPlaneConstraint",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_SetPlaneConstraint));
	mono_add_internal_call("UnrealEngine.MovementComponent::_GetPlaneConstraintNormal",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_GetPlaneConstraintNormal));
	mono_add_internal_call("UnrealEngine.MovementComponent::_SetPlaneConstraintNormal",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_SetPlaneConstraintNormal));
	mono_add_internal_call("UnrealEngine.MovementComponent::_GetPlaneConstraintOrigin",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_GetPlaneConstraintOrigin));
	mono_add_internal_call("UnrealEngine.MovementComponent::_SetPlaneConstraintOrigin",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_SetPlaneConstraintOrigin));
	mono_add_internal_call("UnrealEngine.MovementComponent::_GetUpdateOnlyIfRendered",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_GetUpdateOnlyIfRendered));
	mono_add_internal_call("UnrealEngine.MovementComponent::_SetUpdateOnlyIfRendered",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_SetUpdateOnlyIfRendered));
	mono_add_internal_call("UnrealEngine.MovementComponent::_GetGravityZ",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_GetGravityZ));
	mono_add_internal_call("UnrealEngine.MovementComponent::_GetMaxSpeed",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_GetMaxSpeed));
	mono_add_internal_call("UnrealEngine.MovementComponent::_GetMaxSpeedModifier",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_GetMaxSpeedModifier));
	mono_add_internal_call("UnrealEngine.MovementComponent::_GetModifiedMaxSpeed",
		reinterpret_cast<void*>(UnrealEngine_MovementComponent_GetModifiedMaxSpeed));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_StopActiveMovement",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_StopActiveMovement));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_StopMovementKeepPathing",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_StopMovementKeepPathing));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetCanCrouch",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetCanCrouch));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_SetCanCrouch",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_SetCanCrouch));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetCanJump",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetCanJump));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_SetCanJump",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_SetCanJump));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetCanWalk",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetCanWalk));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_SetCanWalk",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_SetCanWalk));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetCanSwim",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetCanSwim));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_SetCanSwim",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_SetCanSwim));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetCanFly",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetCanFly));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_SetCanFly",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_SetCanFly));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetAgentRadius",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetAgentRadius));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_SetAgentRadius",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_SetAgentRadius));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetAgentHeight",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetAgentHeight));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_SetAgentHeight",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_SetAgentHeight));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetAgentStepHeight",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetAgentStepHeight));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_SetAgentStepHeight",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_SetAgentStepHeight));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetNavWalkingSearchHeightScale",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetNavWalkingSearchHeightScale));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_SetNavWalkingSearchHeightScale",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_SetNavWalkingSearchHeightScale));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetIsCrouching",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetIsCrouching));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetIsFalling",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetIsFalling));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetIsMovingOnGround",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetIsMovingOnGround));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetIsSwimming",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetIsSwimming));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_GetIsFlying",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_GetIsFlying));
	mono_add_internal_call("UnrealEngine.NavMovementComponent::_SetFixedBrakingDistance",
		reinterpret_cast<void*>(UnrealEngine_NavMovementComponent_SetFixedBrakingDistance));
	mono_add_internal_call("UnrealEngine.PawnMovementComponent::_AddInputVector",
		reinterpret_cast<void*>(UnrealEngine_PawnMovementComponent_AddInputVector));
	mono_add_internal_call("UnrealEngine.PawnMovementComponent::_GetPendingInputVector",
		reinterpret_cast<void*>(UnrealEngine_PawnMovementComponent_GetPendingInputVector));
	mono_add_internal_call("UnrealEngine.PawnMovementComponent::_GetLastInputVector",
		reinterpret_cast<void*>(UnrealEngine_PawnMovementComponent_GetLastInputVector));
	mono_add_internal_call("UnrealEngine.PawnMovementComponent::_GetConsumeInputVector",
		reinterpret_cast<void*>(UnrealEngine_PawnMovementComponent_GetConsumeInputVector));
	mono_add_internal_call("UnrealEngine.PawnMovementComponent::_GetIsMoveInputIgnored",
		reinterpret_cast<void*>(UnrealEngine_PawnMovementComponent_GetIsMoveInputIgnored));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetInitialSpeed",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetInitialSpeed));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetInitialSpeed",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetInitialSpeed));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetRotationFollowsVelocity",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetRotationFollowsVelocity));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetRotationFollowsVelocity",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetRotationFollowsVelocity));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetShouldBounce",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetShouldBounce));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetShouldBounce",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetShouldBounce));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetInitialVelocityInLocalSpace",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetInitialVelocityInLocalSpace));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetInitialVelocityInLocalSpace",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetInitialVelocityInLocalSpace));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetForceSubStepping",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetForceSubStepping));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetForceSubStepping",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetForceSubStepping));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetIsHomingProjectile",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetIsHomingProjectile));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetIsHomingProjectile",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetIsHomingProjectile));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetBounceAngleAffectsFriction",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetBounceAngleAffectsFriction));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetBounceAngleAffectsFriction",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetBounceAngleAffectsFriction));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetIsSliding",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetIsSliding));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetIsSliding",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetIsSliding));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetPreviousHitTime",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetPreviousHitTime));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetPreviousHitTime",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetPreviousHitTime));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetPreviousHitNormal",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetPreviousHitNormal));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetPreviousHitNormal",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetPreviousHitNormal));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetProjectileGravityScale",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetProjectileGravityScale));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetProjectileGravityScale",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetProjectileGravityScale));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetBuoyancy",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetBuoyancy));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetBuoyancy",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetBuoyancy));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetBounciness",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetBounciness));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetBounciness",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetBounciness));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetFriction",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetFriction));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetFriction",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetFriction));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_GetBounceVelocityStopSimulatingThreshold",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_GetBounceVelocityStopSimulatingThreshold));
	mono_add_internal_call("UnrealEngine.ProjectileMovementComponent::_SetBounceVelocityStopSimulatingThreshold",
		reinterpret_cast<void*>(UnrealEngine_ProjectileMovementComponent_SetBounceVelocityStopSimulatingThreshold));
	mono_add_internal_call("UnrealEngine.RotatingMovementComponent::_GetRotationRate",
		reinterpret_cast<void*>(UnrealEngine_RotatingMovementComponent_GetRotationRate));
	mono_add_internal_call("UnrealEngine.RotatingMovementComponent::_SetRotationRate",
		reinterpret_cast<void*>(UnrealEngine_RotatingMovementComponent_SetRotationRate));
	mono_add_internal_call("UnrealEngine.RotatingMovementComponent::_GetPivotTranslation",
		reinterpret_cast<void*>(UnrealEngine_RotatingMovementComponent_GetPivotTranslation));
	mono_add_internal_call("UnrealEngine.RotatingMovementComponent::_SetPivotTranslation",
		reinterpret_cast<void*>(UnrealEngine_RotatingMovementComponent_SetPivotTranslation));
	mono_add_internal_call("UnrealEngine.RotatingMovementComponent::_GetRotationInLocalSpace",
		reinterpret_cast<void*>(UnrealEngine_RotatingMovementComponent_GetRotationInLocalSpace));
	mono_add_internal_call("UnrealEngine.RotatingMovementComponent::_SetRotationInLocalSpace",
		reinterpret_cast<void*>(UnrealEngine_RotatingMovementComponent_SetRotationInLocalSpace));
	mono_add_internal_call("UnrealEngine.InterpToMovementComponent::_RestartMovement",
		reinterpret_cast<void*>(UnrealEngine_InterpToMovementComponent_RestartMovement));

}



