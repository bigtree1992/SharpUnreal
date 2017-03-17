#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "UnrealAPI_Math.h"
#include "CoreUObject.h"

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

template<typename T>
static void CopyStruct(T* Dest, T* Source)
{
	FMemory::Memcpy(Dest, Source, sizeof(T));
}

//-----------------------------
static FVector UnrealEngine_Vector_RotateAngleAxis(FVector* _this, float AngleDeg, FVector Axis)
{
	return _this->RotateAngleAxis(AngleDeg, Axis);
}
//-----------------------------
static FVector UnrealEngine_Rotator_Vector(FRotator* _this)
{
	return _this->Vector();
}

static FQuat UnrealEngine_Rotator_Quaternion(FRotator* _this)
{
	return _this->Quaternion();
}

static FVector UnrealEngine_Rotator_RotateVector(FRotator* _this, FVector V)
{
	return _this->RotateVector(V);
}

static FVector UnrealEngine_Rotator_UnrotateVector(FRotator* _this, FVector V)
{
	return _this->UnrotateVector(V);
}

//-----------------------------
static FQuat UnrealEngine_Quat_Multiply(FQuat* _this, FQuat* Other)
{
	return (*_this)*(*Other);
}

static FQuat UnrealEngine_Quat_MakeFromMatrix(FMatrix* Matrix)
{
	return FQuat(*Matrix);
}

static FRotator UnrealEngine_Quat_Rotator(FQuat* _this)
{
	return _this->Rotator();
}
//-----------------------------
static FMatrix UnrealEngine_Transform_ToMatrixWithScale(FTransform* This)
{
	return This->ToMatrixWithScale();
}

static FMatrix UnrealEngine_Transform_ToMatrixNoScale(FTransform* This)
{
	return This->ToMatrixNoScale();
}

static void UnrealEngine_Transform_Blend(FTransform* This, FTransform* Atom1, FTransform* Atom2, float Alpha)
{
	This->Blend(*Atom1, *Atom2, Alpha);
}

static void UnrealEngine_Transform_BlendWith(FTransform* This, FTransform* OtherAtom, float Alpha)
{
	This->BlendWith(*OtherAtom, Alpha);
}

static FTransform UnrealEngine_Transform_GetRelativeTransform(FTransform* This, FTransform* Other)
{
	return This->GetRelativeTransform(*Other);
}

static FTransform UnrealEngine_Transform_GetRelativeTransformReverse(FTransform* This, FTransform* Other)
{
	return This->GetRelativeTransformReverse(*Other);
}

static void UnrealEngine_Transform_SetToRelativeTransform(FTransform* This, FTransform* ParentTransform)
{
	This->SetToRelativeTransform(*ParentTransform);
}

static FVector4 UnrealEngine_Transform_TransformFVector4(FTransform* This, FVector4* V)
{
	FVector4 TempV;
	CopyStruct(&TempV, V);
	return This->TransformFVector4(TempV);
}

static FVector4 UnrealEngine_Transform_TransformFVector4NoScale(FTransform* This, FVector4* V)
{
	FVector4 TempV;
	CopyStruct(&TempV, V);
	return This->TransformFVector4NoScale(TempV);
}

static void UnrealEngine_Transform_Multiply(FTransform* OutTransform, FTransform* A, FTransform* B)
{
	FTransform::Multiply(OutTransform, A, B);
}
//-----------------------------
static FMatrix UnrealEngine_Matrix_Multiply(FMatrix* This, FMatrix* Other)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	FMatrix TempOther;
	CopyStruct(&TempOther, Other);
	return TempThis * TempOther;
}

static FVector4 UnrealEngine_Matrix_TransformFVector4(FMatrix* This, FVector4* V)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	FVector4 TempV;
	CopyStruct(&TempV, V);
	return TempThis.TransformFVector4(TempV);
}

static FMatrix UnrealEngine_Matrix_InverseFast(FMatrix* This)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	return TempThis.InverseFast();
}

static FMatrix UnrealEngine_Matrix_Inverse(FMatrix* This)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	return TempThis.Inverse();
}

static FMatrix UnrealEngine_Matrix_TransposeAdjoint(FMatrix* This)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	return TempThis.TransposeAdjoint();
}

static void UnrealEngine_Matrix_RemoveScaling(FMatrix* This, float Tolerance)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	TempThis.RemoveScaling(Tolerance);
	CopyStruct(This, &TempThis);
}

static FVector UnrealEngine_Matrix_ExtractScaling(FMatrix* This, float Tolerance)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	return TempThis.ExtractScaling(Tolerance);
}

static FMatrix UnrealEngine_Matrix_ConcatTranslation(FMatrix* This, FVector* Translation)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	return TempThis.ConcatTranslation(*Translation);
}

static  FMatrix UnrealEngine_Matrix_ApplyScale(FMatrix* This, float Scale)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	return TempThis.ApplyScale(Scale);
}

static  FRotator UnrealEngine_Matrix_Rotator(FMatrix* This)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	return TempThis.Rotator();
}

static  bool UnrealEngine_Matrix_GetFrustumNearPlane(FMatrix* This, FPlane* OutPlane)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	FPlane TempPlane;
	bool ___ret = TempThis.GetFrustumNearPlane(TempPlane);
	CopyStruct(OutPlane, &TempPlane);
	return ___ret;
}

static  bool UnrealEngine_Matrix_GetFrustumFarPlane(FMatrix* This, FPlane* OutPlane)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	FPlane TempPlane;
	bool ___ret = TempThis.GetFrustumFarPlane(TempPlane);
	CopyStruct(OutPlane, &TempPlane);
	return ___ret;
}

static  bool UnrealEngine_Matrix_GetFrustumLeftPlane(FMatrix* This, FPlane* OutPlane)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	FPlane TempPlane;
	bool ___ret = TempThis.GetFrustumLeftPlane(TempPlane);
	CopyStruct(OutPlane, &TempPlane);
	return ___ret;
}

static  bool UnrealEngine_Matrix_GetFrustumRightPlane(FMatrix* This, FPlane* OutPlane)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	FPlane TempPlane;
	bool ___ret = TempThis.GetFrustumRightPlane(TempPlane);
	CopyStruct(OutPlane, &TempPlane);
	return ___ret;
}

static  bool UnrealEngine_Matrix_GetFrustumTopPlane(FMatrix* This, FPlane* OutPlane)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	FPlane TempPlane;
	bool ___ret = TempThis.GetFrustumTopPlane(TempPlane);
	CopyStruct(OutPlane, &TempPlane);
	return ___ret;
}

static  bool UnrealEngine_Matrix_GetFrustumBottomPlane(FMatrix* This, FPlane* OutPlane)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	FPlane TempPlane;
	bool ___ret = TempThis.GetFrustumBottomPlane(TempPlane);
	CopyStruct(OutPlane, &TempPlane);
	return ___ret;
}

static  void UnrealEngine_Matrix_Mirror(FMatrix* This, int32 MirrorAxis, int32 FlipAxis)
{
	FMatrix TempThis;
	CopyStruct(&TempThis, This);
	TempThis.Mirror((EAxis::Type)MirrorAxis, (EAxis::Type)FlipAxis);
	CopyStruct(This, &TempThis);
}

void UnrealAPI_Math::RegisterAPI() 
{
	//×¢²áFVector
	mono_add_internal_call("UnrealEngine.Vector::RotateAngleAxis", 
		(const void*)UnrealEngine_Vector_RotateAngleAxis);
	//×¢²áFRotator
	mono_add_internal_call("UnrealEngine.Rotator::Vector", 
		(const void*)UnrealEngine_Rotator_Vector);
	mono_add_internal_call("UnrealEngine.Rotator::Quaternion", 
		(const void*)UnrealEngine_Rotator_Quaternion);
	mono_add_internal_call("UnrealEngine.Rotator::RotateVector", 
		(const void*)UnrealEngine_Rotator_RotateVector);
	mono_add_internal_call("UnrealEngine.Rotator::UnrotateVector", 
		(const void*)UnrealEngine_Rotator_UnrotateVector);
	//×¢²áFQuat
	mono_add_internal_call("UnrealEngine.Quat::Multiply", 
		(const void*)UnrealEngine_Quat_Multiply);
	mono_add_internal_call("UnrealEngine.Quat::MakeFromMatrix", 
		(const void*)UnrealEngine_Quat_MakeFromMatrix);
	mono_add_internal_call("UnrealEngine.Quat::Rotator", 
		(const void*)UnrealEngine_Quat_Rotator);
	//×¢²áFTransform
	mono_add_internal_call("UnrealEngine.Transform::ToMatrixWithScale", 
		(const void*)UnrealEngine_Transform_ToMatrixWithScale);
	mono_add_internal_call("UnrealEngine.Transform::ToMatrixNoScale", 
		(const void*)UnrealEngine_Transform_ToMatrixNoScale);
	mono_add_internal_call("UnrealEngine.Transform::Blend", 
		(const void*)UnrealEngine_Transform_Blend);
	mono_add_internal_call("UnrealEngine.Transform::BlendWith", 
		(const void*)UnrealEngine_Transform_BlendWith);
	mono_add_internal_call("UnrealEngine.Transform::GetRelativeTransform",
		(const void*)UnrealEngine_Transform_GetRelativeTransform);
	mono_add_internal_call("UnrealEngine.Transform::GetRelativeTransformReverse", 
		(const void*)UnrealEngine_Transform_GetRelativeTransformReverse);
	mono_add_internal_call("UnrealEngine.Transform::SetToRelativeTransform", 
		(const void*)UnrealEngine_Transform_SetToRelativeTransform);
	mono_add_internal_call("UnrealEngine.Transform::TransformFVector4", 
		(const void*)UnrealEngine_Transform_TransformFVector4);
	mono_add_internal_call("UnrealEngine.Transform::TransformFVector4NoScale", 
		(const void*)UnrealEngine_Transform_TransformFVector4NoScale);
	mono_add_internal_call("UnrealEngine.Transform::Multiply",
		(const void*)UnrealEngine_Transform_Multiply);
	//×¢²áFMatrix
	mono_add_internal_call("UnrealEngine.Matrix::Multiply", 
		(const void*)UnrealEngine_Matrix_Multiply);
	mono_add_internal_call("UnrealEngine.Matrix::TransformFVector4", 
		(const void*)UnrealEngine_Matrix_TransformFVector4);
	mono_add_internal_call("UnrealEngine.Matrix::InverseFast", 
		(const void*)UnrealEngine_Matrix_InverseFast);
	mono_add_internal_call("UnrealEngine.Matrix::Inverse", 
		(const void*)UnrealEngine_Matrix_Inverse);
	mono_add_internal_call("UnrealEngine.Matrix::TransposeAdjoint", 
		(const void*)UnrealEngine_Matrix_TransposeAdjoint);
	mono_add_internal_call("UnrealEngine.Matrix::RemoveScaling", 
		(const void*)UnrealEngine_Matrix_RemoveScaling);
	mono_add_internal_call("UnrealEngine.Matrix::ExtractScaling", 
		(const void*)UnrealEngine_Matrix_ExtractScaling);
	mono_add_internal_call("UnrealEngine.Matrix::ConcatTranslation", 
		(const void*)UnrealEngine_Matrix_ConcatTranslation);
	mono_add_internal_call("UnrealEngine.Matrix::ApplyScale", 
		(const void*)UnrealEngine_Matrix_ApplyScale);
	mono_add_internal_call("UnrealEngine.Matrix::Rotator", 
		(const void*)UnrealEngine_Matrix_Rotator);
	mono_add_internal_call("UnrealEngine.Matrix::GetFrustumNearPlane", 
		(const void*)UnrealEngine_Matrix_GetFrustumNearPlane);
	mono_add_internal_call("UnrealEngine.Matrix::GetFrustumFarPlane", 
		(const void*)UnrealEngine_Matrix_GetFrustumFarPlane);
	mono_add_internal_call("UnrealEngine.Matrix::GetFrustumLeftPlane", 
		(const void*)UnrealEngine_Matrix_GetFrustumLeftPlane);
	mono_add_internal_call("UnrealEngine.Matrix::GetFrustumRightPlane", 
		(const void*)UnrealEngine_Matrix_GetFrustumRightPlane);
	mono_add_internal_call("UnrealEngine.Matrix::GetFrustumTopPlane", 
		(const void*)UnrealEngine_Matrix_GetFrustumTopPlane);
	mono_add_internal_call("UnrealEngine.Matrix::GetFrustumBottomPlane", 
		(const void*)UnrealEngine_Matrix_GetFrustumBottomPlane);
	mono_add_internal_call("UnrealEngine.Matrix::Mirror", 
		(const void*)UnrealEngine_Matrix_Mirror);
}

