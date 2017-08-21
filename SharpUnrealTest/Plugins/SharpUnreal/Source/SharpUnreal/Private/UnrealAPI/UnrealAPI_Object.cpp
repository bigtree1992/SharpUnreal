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

}


