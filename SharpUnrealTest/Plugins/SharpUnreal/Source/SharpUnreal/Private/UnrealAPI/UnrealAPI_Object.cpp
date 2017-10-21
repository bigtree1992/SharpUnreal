#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "UnrealAPI_Object.h"

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


static mono_bool UnrealEngine_UObject_GetIsRooted(UObject* object)
{
	if (object == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[UObject] GetIsRooted But object is NULL."));
		return false;
	}

	return object->IsRooted();
}

static void UnrealEngine_UObject_SetIsRooted(UObject* object, mono_bool value)
{
	if (object == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[UObject] SetIsRooted But object is NULL."));
		return;
	}

	if (value != 0)
	{
		object->AddToRoot();
	}
	else {
		object->RemoveFromRoot();
	}
}

static int UnrealEngine_IntProperty_GetValue(AActor* actor, UIntProperty* property) 
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[IntProperty] GetValue But actor is NULL."));
		return 0;
	}
	if (property == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[IntProperty] GetValue But property is NULL."));
		return 0;
	}

	int Value = property->GetSignedIntPropertyValue(property->ContainerPtrToValuePtr<uint8>(actor));
	return Value;
}

static void UnrealEngine_IntProperty_SetValue(AActor* actor, UIntProperty* property,int value) 
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[IntProperty] GetValue But actor is NULL."));
		return;
	}
	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[IntProperty] GetValue But property is NULL."));
		return;
	}

	property->SetPropertyValue(property->ContainerPtrToValuePtr<uint8>(actor), value);
}

static float UnrealEngine_FloatProperty_GetValue(AActor* actor, UFloatProperty* property)
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[FloatProperty] GetValue But actor is NULL."));
		return 0.0f;
	}
	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[FloatProperty] GetValue But property is NULL."));
		return 0.0f;
	}
	float Value = property->GetFloatingPointPropertyValue(property->ContainerPtrToValuePtr<uint8>(actor));
	return Value;
}

static void UnrealEngine_FloatProperty_SetValue(AActor* actor, UFloatProperty* property, float value)
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[FloatProperty] GetValue But actor is NULL."));
		return;
	}
	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[FloatProperty] GetValue But property is NULL."));
		return;
	}
	property->SetFloatingPointPropertyValue(property->ContainerPtrToValuePtr<uint8>(actor), value);
}

static MonoString* UnrealEngine_StringProperty_GetValue(AActor* actor, UStrProperty* property) 
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[StringProperty] GetValue But actor is NULL."));
		return NULL;
	}

	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[StringProperty] GetValue But property is NULL."));
		return NULL;
	}

	FString Value = property->GetPropertyValue(property->ContainerPtrToValuePtr<uint8>(actor));
	MonoString* result = mono_string_from_utf16((mono_unichar2*)*Value);
	return result;
}

static void UnrealEngine_StringProperty_SetValue(AActor* actor, UStrProperty* property, MonoString* value)
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[StringProperty] GetValue But actor is NULL."));
		return;
	}
	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[StringProperty] GetValue But property is NULL."));
		return;
	}

	FString Value = FString((TCHAR*)mono_string_to_utf16(value));
	property->InitializeValue_InContainer(actor);
	property->SetPropertyValue(property->ContainerPtrToValuePtr<uint8>(actor), Value);
}

static FVector UnrealEngine_VectorProperty_GetValue(AActor* actor, UStructProperty* property)
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[VectorProperty] GetValue But actor is NULL."));
		return FVector::ZeroVector;
	}

	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[VectorProperty] GetValue But property is NULL."));
		return FVector::ZeroVector;
	}

	return *property->ContainerPtrToValuePtr<FVector>(actor);
}

static void UnrealEngine_VectorProperty_SetValue(AActor* actor, UStructProperty* property, FVector value)
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[VectorProperty] GetValue But actor is NULL."));
		return;
	}
	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[VectorProperty] GetValue But property is NULL."));
		return;
	}

	*property->ContainerPtrToValuePtr<FVector>(actor) = value;
}

static FQuat UnrealEngine_QuatProperty_GetValue(AActor* actor, UStructProperty* property)
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[QuatProperty] GetValue But actor is NULL."));
		return FQuat::Identity;
	}

	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[QuatProperty] GetValue But property is NULL."));
		return FQuat::Identity;
	}

	return *property->ContainerPtrToValuePtr<FQuat>(actor);
}

static void UnrealEngine_QuatProperty_SetValue(AActor* actor, UStructProperty* property, FQuat value)
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[QuatProperty] GetValue But actor is NULL."));
		return;
	}

	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[QuatProperty] GetValue But property is NULL."));
		return;
	}
	FQuat& PropertyValue = *property->ContainerPtrToValuePtr<FQuat>(actor);	
	PropertyValue.X = value.X;
	PropertyValue.Y = value.Y;
	PropertyValue.Z = value.Z;
	PropertyValue.W = value.W;
	//below code will crash
	//*property->ContainerPtrToValuePtr<FQuat>(actor,0) = value;
}

static FRotator UnrealEngine_RotatorProperty_GetValue(AActor* actor, UStructProperty* property)
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[RotatorProperty] GetValue But actor is NULL."));
		return FRotator::ZeroRotator;
	}

	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[RotatorProperty] GetValue But property is NULL."));
		return FRotator::ZeroRotator;
	}

	return *property->ContainerPtrToValuePtr<FRotator>(actor);
}

static void UnrealEngine_RotatorProperty_SetValue(AActor* actor, UStructProperty* property, FRotator value)
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[RotatorProperty] GetValue But actor is NULL."));
		return;
	}

	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[RotatorProperty] GetValue But property is NULL."));
		return;
	}

	*property->ContainerPtrToValuePtr<FRotator>(actor) = value;
}

static FTransform UnrealEngine_TransformProperty_GetValue(AActor* actor, UStructProperty* property)
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TransformProperty] GetValue But actor is NULL."));
		return FTransform::Identity;
	}

	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TransformProperty] GetValue But property is NULL."));
		return FTransform::Identity;
	}

	return *property->ContainerPtrToValuePtr<FTransform>(actor);
}

static void UnrealEngine_TransformProperty_SetValue(AActor* actor, UStructProperty* property, FTransform value)
{
	if (actor == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TransformProperty] GetValue But actor is NULL."));
		return;
	}

	if (property == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TransformProperty] GetValue But property is NULL."));
		return;
	}

	*property->ContainerPtrToValuePtr<FTransform>(actor) = value;
}

void UnrealAPI_Object::RegisterAPI()
{
	mono_add_internal_call("UnrealEngine.UObject::_GetIsRooted",
		reinterpret_cast<void*>(UnrealEngine_UObject_GetIsRooted));
	mono_add_internal_call("UnrealEngine.UObject::_SetIsRooted",
		reinterpret_cast<void*>(UnrealEngine_UObject_SetIsRooted));

	mono_add_internal_call("UnrealEngine.IntProperty::_GetValue",
		reinterpret_cast<void*>(UnrealEngine_IntProperty_GetValue));
	mono_add_internal_call("UnrealEngine.IntProperty::_SetValue",
		reinterpret_cast<void*>(UnrealEngine_IntProperty_SetValue));

	mono_add_internal_call("UnrealEngine.FloatProperty::_GetValue",
		reinterpret_cast<void*>(UnrealEngine_FloatProperty_GetValue));
	mono_add_internal_call("UnrealEngine.FloatProperty::_SetValue",
		reinterpret_cast<void*>(UnrealEngine_FloatProperty_SetValue));

	mono_add_internal_call("UnrealEngine.StringProperty::_GetValue",
		reinterpret_cast<void*>(UnrealEngine_StringProperty_GetValue));
	mono_add_internal_call("UnrealEngine.StringProperty::_SetValue",
		reinterpret_cast<void*>(UnrealEngine_StringProperty_SetValue));

	mono_add_internal_call("UnrealEngine.VectorProperty::_GetValue",
		reinterpret_cast<void*>(UnrealEngine_VectorProperty_GetValue));
	mono_add_internal_call("UnrealEngine.VectorProperty::_SetValue",
		reinterpret_cast<void*>(UnrealEngine_VectorProperty_SetValue));

	mono_add_internal_call("UnrealEngine.QuatProperty::_GetValue",
		reinterpret_cast<void*>(UnrealEngine_QuatProperty_GetValue));
	mono_add_internal_call("UnrealEngine.QuatProperty::_SetValue",
		reinterpret_cast<void*>(UnrealEngine_QuatProperty_SetValue));

	mono_add_internal_call("UnrealEngine.RotatorProperty::_GetValue",
		reinterpret_cast<void*>(UnrealEngine_RotatorProperty_GetValue));
	mono_add_internal_call("UnrealEngine.RotatorProperty::_SetValue",
		reinterpret_cast<void*>(UnrealEngine_RotatorProperty_SetValue));
	
	mono_add_internal_call("UnrealEngine.TransformProperty::_GetValue",
		reinterpret_cast<void*>(UnrealEngine_TransformProperty_GetValue));
	mono_add_internal_call("UnrealEngine.TransformProperty::_SetValue",
		reinterpret_cast<void*>(UnrealEngine_TransformProperty_SetValue));

}


