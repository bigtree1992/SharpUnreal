// Fill out your copyright notice in the Description page of Project Settings.

#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "UnrealAPI_Spline.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

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


static void UnrealEngine_SplineComponent_UpdateSpline(USplineComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] UpdateSpline But _this is NULL."));
		return;
	}
	_this->UpdateSpline();
}

static void UnrealEngine_SplineComponent_SetLocationAtSplinePoint(USplineComponent* _this, int PointIndex, FVector InLocation, ESplineCoordinateSpace::Type CoordinateSpace, mono_bool bUpdateSpline)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] SetLocationAtSplinePoint But _this is NULL."));
		return;
	}
	_this->SetLocationAtSplinePoint(PointIndex, InLocation, CoordinateSpace, bUpdateSpline!=0);	
}

static FTransform UnrealEngine_SplineComponent_GetTransformAtSplinePoint(USplineComponent* _this, int PointIndex, ESplineCoordinateSpace::Type CoordinateSpace, mono_bool bUseScale)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] GetTransformAtSplinePoint But _this is NULL."));
		return FTransform::Identity;
	}
	return _this->GetTransformAtSplinePoint(PointIndex, CoordinateSpace,bUseScale !=0 );
}

static float UnrealEngine_SplineComponent_GetDistanceAlongSplineAtSplinePoint(USplineComponent* _this, int PointIndex)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] GetDistanceAlongSplineAtSplinePoint But _this is NULL."));
		return 0.0f;
	}
	return _this->GetDistanceAlongSplineAtSplinePoint(PointIndex);
}

static FTransform UnrealEngine_SplineComponent_GetTransformAtDistanceAlongSpline(USplineComponent* _this, float Distance, ESplineCoordinateSpace::Type CoordinateSpace, mono_bool bUseScale)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] GetTransformAtDistanceAlongSpline But _this is NULL."));
		return FTransform::Identity;
	}
	return _this->GetTransformAtDistanceAlongSpline(Distance, CoordinateSpace, bUseScale != 0);
}

static FTransform UnrealEngine_SplineComponent_GetTransformAtTime(USplineComponent* _this, float Time, ESplineCoordinateSpace::Type CoordinateSpace, mono_bool bUseConstantVelocity, mono_bool bUseScale)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] GetTransformAtTime But _this is NULL."));
		return FTransform::Identity;
	}
	return _this->GetTransformAtTime(Time, CoordinateSpace,bUseConstantVelocity != 0, bUseScale != 0);
}

static FTransform UnrealEngine_SplineComponent_FindTransformClosestToWorldLocation(USplineComponent* _this, FVector WorldLocation, ESplineCoordinateSpace::Type CoordinateSpace, mono_bool bUseScale)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] FindTransformClosestToWorldLocation But _this is NULL."));
		return FTransform::Identity;
	}
	return _this->FindTransformClosestToWorldLocation(WorldLocation, CoordinateSpace,bUseScale != 0);
}

static float UnrealEngine_SplineComponent_GetDuration(USplineComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] GetDuration But _this is NULL."));
		return 0.0f;
	}
	return _this->Duration;
}

static void UnrealEngine_SplineComponent_SetDuration(USplineComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] SetDuration But _this is NULL."));
		return;
	}
	_this->Duration = value;
}

static mono_bool UnrealEngine_SplineComponent_GetDrawDebug(USplineComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] GetDrawDebug But _this is NULL."));
		return 0;
	}
	return _this->bDrawDebug;
}

static void UnrealEngine_SplineComponent_SetDrawDebug(USplineComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] SetDrawDebug But _this is NULL."));
		return;
	}
	_this->SetDrawDebug(value != 0);
}

static FVector UnrealEngine_SplineComponent_GetDefaultUpVector(USplineComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] GetDefaultUpVector But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->DefaultUpVector;
}

static void UnrealEngine_SplineComponent_SetDefaultUpVector(USplineComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] SetDefaultUpVector But _this is NULL."));
		return;
	}
	_this->DefaultUpVector = value;
}


static void UnrealEngine_SplineComponent_SetUnselectedSplineSegmentColor(USplineComponent* _this, FLinearColor value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] SetUnselectedSplineSegmentColor But _this is NULL."));
		return;
	}
	_this->SetUnselectedSplineSegmentColor(value);
}

static void UnrealEngine_SplineComponent_SetSelectedSplineSegmentColor(USplineComponent* _this, FLinearColor value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] SetSelectedSplineSegmentColor But _this is NULL."));
		return;
	}
	_this->SetSelectedSplineSegmentColor(value);
}

static mono_bool UnrealEngine_SplineComponent_GetClosedLoop(USplineComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] GetClosedLoop But _this is NULL."));
		return 0;
	}
	return _this->IsClosedLoop();
}

static void UnrealEngine_SplineComponent_SetClosedLoop(USplineComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] SetClosedLoop But _this is NULL."));
		return;
	}
	_this->SetClosedLoop(value != 0);
}

static int UnrealEngine_SplineComponent_GetNumberOfSplinePoints(USplineComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] GetNumberOfSplinePoints But _this is NULL."));
		return 0;
	}
	return _this->GetNumberOfSplinePoints();
}

static float UnrealEngine_SplineComponent_GetSplineLength(USplineComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineComponent] GetSplineLength But _this is NULL."));
		return 0.0f;
	}
	return _this->GetSplineLength();
}



static void UnrealEngine_SplineMeshComponent_UpdateMesh(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] UpdateMesh But _this is NULL."));
		return;
	}
	_this->UpdateMesh();
}

static FVector UnrealEngine_SplineMeshComponent_GetStartPosition(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetStartPosition But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetStartPosition();
}

static void UnrealEngine_SplineMeshComponent_SetStartPosition(USplineMeshComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetStartPosition But _this is NULL."));
		return;
	}
	_this->SetStartPosition(value,false);
}

static FVector UnrealEngine_SplineMeshComponent_GetStartTangent(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetStartTangent But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetStartTangent();
}

static void UnrealEngine_SplineMeshComponent_SetStartTangent(USplineMeshComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetStartTangent But _this is NULL."));
		return;
	}
	_this->SetStartTangent(value,false);
}

static FVector UnrealEngine_SplineMeshComponent_GetEndPosition(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetEndPosition But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetEndPosition();
}

static void UnrealEngine_SplineMeshComponent_SetEndPosition(USplineMeshComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetEndPosition But _this is NULL."));
		return;
	}
	_this->SetEndPosition(value,false);
}

static FVector UnrealEngine_SplineMeshComponent_GetEndTangent(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetGetEndTangent But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetEndTangent();
}

static void UnrealEngine_SplineMeshComponent_SetEndTangent(USplineMeshComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetGetEndTangent But _this is NULL."));
		return;
	}
	_this->SetEndTangent(value,false);
}

static FVector2D UnrealEngine_SplineMeshComponent_GetStartScale(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetStartScale But _this is NULL."));
		return FVector2D::ZeroVector;
	}
	return _this->GetStartScale();
}

static void UnrealEngine_SplineMeshComponent_SetStartScale(USplineMeshComponent* _this, FVector2D value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetStartScale But _this is NULL."));
		return;
	}
	_this->SetStartScale(value,false);
}

static float UnrealEngine_SplineMeshComponent_GetStartRoll(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetStartRoll But _this is NULL."));
		return 0.0f;
	}
	return _this->GetStartRoll();
}

static void UnrealEngine_SplineMeshComponent_SetStartRoll(USplineMeshComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetStartRoll But _this is NULL."));
		return;
	}
	_this->SetStartRoll(value,false);
}

static FVector2D UnrealEngine_SplineMeshComponent_GetStartOffset(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetStartOffset But _this is NULL."));
		return FVector2D::ZeroVector;
	}
	return _this->GetStartOffset();
}

static void UnrealEngine_SplineMeshComponent_SetStartOffset(USplineMeshComponent* _this, FVector2D value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetStartOffset But _this is NULL."));
		return;
	}
	_this->SetStartOffset(value,false);
}

static FVector2D UnrealEngine_SplineMeshComponent_GetEndScale(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetEndScale But _this is NULL."));
		return FVector2D::ZeroVector;
	}
	return _this->GetEndScale();
}

static void UnrealEngine_SplineMeshComponent_SetEndScale(USplineMeshComponent* _this, FVector2D value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetEndScale But _this is NULL."));
		return;
	}
	_this->SetEndOffset(value, false);
}

static float UnrealEngine_SplineMeshComponent_GetEndRoll(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetGetEndRoll But _this is NULL."));
		return 0.0f;
	}
	return _this->GetEndRoll();
}

static void UnrealEngine_SplineMeshComponent_SetEndRoll(USplineMeshComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetGetEndRoll But _this is NULL."));
		return;
	}
	_this->SetEndRoll(value, false);
}

static FVector2D UnrealEngine_SplineMeshComponent_GetEndOffset(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetEndOffset But _this is NULL."));
		return FVector2D::ZeroVector;
	}
	return _this->GetEndOffset();
}

static void UnrealEngine_SplineMeshComponent_SetEndOffset(USplineMeshComponent* _this, FVector2D value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetEndOffset But _this is NULL."));
		return;
	}
	_this->SetEndOffset(value, false);
}

static ESplineMeshAxis::Type UnrealEngine_SplineMeshComponent_GetForwardAxis(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetForwardAxis But _this is NULL."));
		return ESplineMeshAxis::Type::X;
	}
	return _this->GetForwardAxis();
}

static void UnrealEngine_SplineMeshComponent_SetForwardAxis(USplineMeshComponent* _this, ESplineMeshAxis::Type value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetForwardAxis But _this is NULL."));
		return;
	}
	_this->SetForwardAxis(value, false);
}

static FVector UnrealEngine_SplineMeshComponent_GetSplineUpDir(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetSplineUpDir But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetSplineUpDir();
}

static void UnrealEngine_SplineMeshComponent_SetSplineUpDir(USplineMeshComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetSplineUpDir But _this is NULL."));
		return;
	}
	_this->SetSplineUpDir(value, false);
}

static float UnrealEngine_SplineMeshComponent_GetBoundaryMin(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetBoundaryMin But _this is NULL."));
		return 0.0f;
	}
	return _this->GetBoundaryMin();
}

static void UnrealEngine_SplineMeshComponent_SetBoundaryMin(USplineMeshComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetBoundaryMin But _this is NULL."));
		return;
	}
	_this->SetBoundaryMin(value,false);
}

static float UnrealEngine_SplineMeshComponent_GetBoundaryMax(USplineMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] GetBoundaryMax But _this is NULL."));
		return 0.0f;
	}
	return _this->GetBoundaryMax();
}

static void UnrealEngine_SplineMeshComponent_SetBoundaryMax(USplineMeshComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SplineMeshComponent] SetBoundaryMax But _this is NULL."));
		return;
	}
	_this->SetBoundaryMax(value, false);
}


void UnrealAPI_Spline::RegisterAPI()
{
	mono_add_internal_call("UnrealEngine.SplineComponent::_UpdateSpline",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_UpdateSpline));
	mono_add_internal_call("UnrealEngine.SplineComponent::_SetLocationAtSplinePoint",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_SetLocationAtSplinePoint));
	mono_add_internal_call("UnrealEngine.SplineComponent::_GetTransformAtSplinePoint",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_GetTransformAtSplinePoint));
	mono_add_internal_call("UnrealEngine.SplineComponent::_GetDistanceAlongSplineAtSplinePoint",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_GetDistanceAlongSplineAtSplinePoint));
	mono_add_internal_call("UnrealEngine.SplineComponent::_GetTransformAtDistanceAlongSpline",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_GetTransformAtDistanceAlongSpline));
	mono_add_internal_call("UnrealEngine.SplineComponent::_GetTransformAtTime",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_GetTransformAtTime));
	mono_add_internal_call("UnrealEngine.SplineComponent::_FindTransformClosestToWorldLocation",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_FindTransformClosestToWorldLocation));
	mono_add_internal_call("UnrealEngine.SplineComponent::_GetDuration",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_GetDuration));
	mono_add_internal_call("UnrealEngine.SplineComponent::_SetDuration",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_SetDuration));
	mono_add_internal_call("UnrealEngine.SplineComponent::_GetDrawDebug",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_GetDrawDebug));
	mono_add_internal_call("UnrealEngine.SplineComponent::_SetDrawDebug",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_SetDrawDebug));
	mono_add_internal_call("UnrealEngine.SplineComponent::_GetDefaultUpVector",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_GetDefaultUpVector));
	mono_add_internal_call("UnrealEngine.SplineComponent::_SetDefaultUpVector",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_SetDefaultUpVector));
	mono_add_internal_call("UnrealEngine.SplineComponent::_SetUnselectedSplineSegmentColor",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_SetUnselectedSplineSegmentColor));
	mono_add_internal_call("UnrealEngine.SplineComponent::_SetSelectedSplineSegmentColor",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_SetSelectedSplineSegmentColor));
	mono_add_internal_call("UnrealEngine.SplineComponent::_GetClosedLoop",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_GetClosedLoop));
	mono_add_internal_call("UnrealEngine.SplineComponent::_SetClosedLoop",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_SetClosedLoop));
	mono_add_internal_call("UnrealEngine.SplineComponent::_GetNumberOfSplinePoints",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_GetNumberOfSplinePoints));
	mono_add_internal_call("UnrealEngine.SplineComponent::_GetSplineLength",
		reinterpret_cast<void*>(UnrealEngine_SplineComponent_GetSplineLength));

	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_UpdateMesh",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_UpdateMesh));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetStartPosition",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetStartPosition));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetStartPosition",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetStartPosition));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetStartTangent",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetStartTangent));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetStartTangent",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetStartTangent));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetEndPosition",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetEndPosition));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetEndPosition",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetEndPosition));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetEndTangent",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetEndTangent));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetEndTangent",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetEndTangent));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetStartScale",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetStartScale));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetStartScale",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetStartScale));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetStartRoll",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetStartRoll));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetStartRoll",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetStartRoll));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetStartOffset",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetStartOffset));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetStartOffset",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetStartOffset));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetEndScale",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetEndScale));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetEndScale",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetEndScale));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetGetEndRoll",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetEndRoll));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetGetEndRoll",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetEndRoll));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetEndOffset",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetEndOffset));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetEndOffset",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetEndOffset));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetForwardAxis",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetForwardAxis));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetForwardAxis",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetForwardAxis));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetSplineUpDir",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetSplineUpDir));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetSplineUpDir",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetSplineUpDir));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetBoundaryMin",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetBoundaryMin));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetBoundaryMin",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetBoundaryMin));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_GetBoundaryMax",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_GetBoundaryMax));
	mono_add_internal_call("UnrealEngine.SplineMeshComponent::_SetBoundaryMax",
		reinterpret_cast<void*>(UnrealEngine_SplineMeshComponent_SetBoundaryMax));
}
