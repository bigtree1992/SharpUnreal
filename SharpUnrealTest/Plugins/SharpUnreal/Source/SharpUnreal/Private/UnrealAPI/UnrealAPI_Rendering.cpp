// Fill out your copyright notice in the Description page of Project Settings.

#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "UnrealAPI_Rendering.h"

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


static UMaterialInstanceDynamic* UnrealEngine_DynamicMaterial_Create(UMaterialInterface* mat, UObject* outer)
{
	if (mat == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _Create But mat is NULL."));
		return NULL;
	}

	if (outer == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _Create But outer is NULL."));
		return NULL;
	}

	return UMaterialInstanceDynamic::Create(mat, outer);
}

static float UnrealEngine_DynamicMaterial_GetScalarParameter(UMaterialInstanceDynamic* _this, MonoString* name)
{
	if (_this == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _GetScalarParameter But _this is NULL."));
		return 0.0f;
	}

	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _GetScalarParameter But name is NULL."));
		return 0.0f;
	}

	FName fname = FName((TCHAR*)mono_string_to_utf16(name));
	
	float fresult = 0.0f;
	if (!_this->GetScalarParameterValue(fname,fresult)) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] GetScalarParameterValue Failed."));
	}
	return fresult;
}

static void UnrealEngine_DynamicMaterial_SetScalarParameter(UMaterialInstanceDynamic* _this, MonoString* name, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _SetScalarParameter But _this is NULL."));
		return;
	}
	
	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _SetScalarParameter But name is NULL."));
	}

	FName fname = FName((TCHAR*)mono_string_to_utf16(name));
	_this->SetScalarParameterValue(fname, value);
}

static FLinearColor UnrealEngine_DynamicMaterial_GetVectorParameter(UMaterialInstanceDynamic* _this, MonoString* name)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _GetVectorParameter But _this is NULL."));
		return FLinearColor::Black;
	}

	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _GetVectorParameter But name is NULL."));
		return FLinearColor::Black;
	}

	FName fname = FName((TCHAR*)mono_string_to_utf16(name));
	FLinearColor result;
	if (!_this->GetVectorParameterValue(fname, result)) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] GetVectorParameterValue Failed."));
	}
	return result;
}

static void UnrealEngine_DynamicMaterial_SetVectorParameter(UMaterialInstanceDynamic* _this, MonoString* name, FLinearColor value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _SetVectorParameter But _this is NULL."));
		return;
	}
	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _SetVectorParameter But name is NULL."));
		return;
	}
	FName fname = FName((TCHAR*)mono_string_to_utf16(name));
	_this->SetVectorParameterValue(fname, value);
}

static UTexture* UnrealEngine_DynamicMaterial_GetTextureParameter(UMaterialInstanceDynamic* _this, MonoString* name)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _GetTextureParameter But _this is NULL."));
		return NULL;
	}

	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _GetTextureParameter But name is NULL."));
		return NULL;
	}

	FName fname = FName((TCHAR*)mono_string_to_utf16(name));
	UTexture* result;
	if (!_this->GetTextureParameterValue(fname, result)) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _GetTextureParameter Failed."));
	}
	return result;
}

static void UnrealEngine_DynamicMaterial_SetTextureParameter(UMaterialInstanceDynamic* _this, MonoString* name, UTexture* texture)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _SetTextureParameter But _this is NULL."));
		return;
	}

	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _SetTextureParameter But name is NULL."));
		return;
	}

	if (texture == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DynamicMaterial] _SetTextureParameter But texture is NULL."));
		return;
	}

	FName fname = FName((TCHAR*)mono_string_to_utf16(name));
	_this->SetTextureParameterValue(fname, texture);
}


void UnrealAPI_Rendering::RegisterAPI() 
{
	mono_add_internal_call("UnrealEngine.DynamicMaterial::_Create",
		reinterpret_cast<void*>(UnrealEngine_DynamicMaterial_Create));

	mono_add_internal_call("UnrealEngine.DynamicMaterial::_GetScalarParameter",
		reinterpret_cast<void*>(UnrealEngine_DynamicMaterial_GetScalarParameter));
	mono_add_internal_call("UnrealEngine.DynamicMaterial::_SetScalarParameter",
		reinterpret_cast<void*>(UnrealEngine_DynamicMaterial_SetScalarParameter));
	mono_add_internal_call("UnrealEngine.DynamicMaterial::_GetVectorParameter",
		reinterpret_cast<void*>(UnrealEngine_DynamicMaterial_GetVectorParameter));
	mono_add_internal_call("UnrealEngine.DynamicMaterial::_SetVectorParameter",
		reinterpret_cast<void*>(UnrealEngine_DynamicMaterial_SetVectorParameter));
	mono_add_internal_call("UnrealEngine.DynamicMaterial::_GetTextureParameter",
		reinterpret_cast<void*>(UnrealEngine_DynamicMaterial_GetTextureParameter));
	mono_add_internal_call("UnrealEngine.DynamicMaterial::_SetTextureParameter",
		reinterpret_cast<void*>(UnrealEngine_DynamicMaterial_SetTextureParameter));

}