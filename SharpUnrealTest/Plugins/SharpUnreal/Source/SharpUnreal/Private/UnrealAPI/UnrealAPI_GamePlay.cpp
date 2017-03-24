#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "LevelSequenceActor.h"

#include "UnrealAPI_GamePlay.h"
#include "MonoClassTable.h"

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

static mono_bool Unrealengine_Actor_GetHiddenInGame(AActor* _this)
{
	if (_this == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetHiddenInGame But _this is NULL."));
		return false;
	}
	return _this->bHidden;
}

static void Unrealengine_Actor_SetHiddenInGame(AActor* _this,mono_bool hidden)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] SetHiddenInGame But _this is NULL."));
		return;
	}
	return _this->SetActorHiddenInGame(hidden != 0);
}

static USceneComponent* Unrealengine_Actor_GetSceneComponent(AActor* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetSceneComponent But _this is NULL."));
		return NULL;
	}
	return _this->GetRootComponent();
}

static void Unrealengine_Actor_SetSceneComponent(AActor* _this, USceneComponent* root)
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

static UActorComponent* Unrealengine_Actor_GetComponent(AActor* _this, MonoString* type)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetComponent But _this is NULL."));
		return NULL;
	}

	FString type_name = FString((TCHAR*)mono_string_to_utf16(type));
	auto components = _this->GetComponents();
	//ToDo:: 优化速度
	for (auto component : components)
	{
		if (component != NULL)
		{
			if (component->GetClass()->GetName().Contains(type_name))
			{
				return component;
			}
		}
	}

	return NULL;
}

static UActorComponent* Unrealengine_Actor_GetComponentByTag(AActor* _this, MonoString* type,MonoString* tag)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] GetComponentByTag But _this is NULL."));
		return NULL;
	}

	FName tag_name = FName((TCHAR*)mono_string_to_utf16(tag));
	FString type_name = FString((TCHAR*)mono_string_to_utf16(type));

	auto components = _this->GetComponentsByTag(UActorComponent::StaticClass(), tag_name);
	for (int32 i = 0; i < components.Num(); i++)
	{
		auto component = components[i];
		if (component != NULL)
		{
			if (component->GetClass()->GetName().Contains(type_name))
			{
				return component;
			}
		}
	}
	return NULL;
}

static void Unrealengine_Actor_Destroy(AActor* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Actor] Destroy But _this is NULL."));
		return;
	}
	_this->Destroy();
}

static ULevelSequencePlayer* Unrealengine_Actor_GetSequencer(AActor* _this)
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

void UnrealAPI_GamePlay::RegisterAPI()
{
	mono_add_internal_call("UnrealEngine.Actor::_GetHiddenInGame",
		reinterpret_cast<void*>(Unrealengine_Actor_GetHiddenInGame));
	mono_add_internal_call("UnrealEngine.Actor::_SetHiddenInGame",
		reinterpret_cast<void*>(Unrealengine_Actor_SetHiddenInGame));
	mono_add_internal_call("UnrealEngine.Actor::_GetSceneComponent",
		reinterpret_cast<void*>(Unrealengine_Actor_GetSceneComponent));
	mono_add_internal_call("UnrealEngine.Actor::_SetSceneComponent",
		reinterpret_cast<void*>(Unrealengine_Actor_SetSceneComponent));
	mono_add_internal_call("UnrealEngine.Actor::_GetComponent",
		reinterpret_cast<void*>(Unrealengine_Actor_GetComponent));
	mono_add_internal_call("UnrealEngine.Actor::_GetComponentByTag",
		reinterpret_cast<void*>(Unrealengine_Actor_GetComponentByTag));
	mono_add_internal_call("UnrealEngine.Actor::_Destroy",
		reinterpret_cast<void*>(Unrealengine_Actor_Destroy));
	mono_add_internal_call("UnrealEngine.Actor::_GetSequencer",
		reinterpret_cast<void*>(Unrealengine_Actor_GetSequencer));
}