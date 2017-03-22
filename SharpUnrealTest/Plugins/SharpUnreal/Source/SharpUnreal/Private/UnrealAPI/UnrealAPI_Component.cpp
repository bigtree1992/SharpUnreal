#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "UnrealAPI_Component.h"
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

#if 1
static mono_bool UnrealEngine_ActorComponent_GetActivited(UMonoComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] GetActivited But _this is NULL."));
		return false;
	}
	return _this->bIsActive;
}

static void UnrealEngine_ActorComponent_SetActivited(UMonoComponent* _this, bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SetActivited But _this is NULL."));
		return;
	}
	_this->SetActive(value);
}

static mono_bool UnrealEngine_ActorComponent_GetCanEverTick(UMonoComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] GetCanEverTick But _this is NULL."));
		return false;
	}
	return _this->PrimaryComponentTick.bCanEverTick;
}

static void UnrealEngine_ActorComponent_SetCanEverTick(UMonoComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SetCanEverTick But _this is NULL."));
		return;
	}
	_this->PrimaryComponentTick.bCanEverTick = value;
}

static AActor* UnrealEngine_ActorComponent_GetOwner(UMonoComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] GetOwner But _this is NULL."));
		return NULL;
	}
	return _this->GetOwner();
}

static void UnrealEngine_ActorComponent_SetTickableWhenPaused(UMonoComponent* _this, mono_bool bTickableWhenPaused)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SetTickableWhenPaused But _this is NULL."));
		return;
	}
	_this->SetTickableWhenPaused(bTickableWhenPaused != 0);
}

static mono_bool UnrealEngine_ActorComponent_HasTag(UMonoComponent* _this, MonoString* tag)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] HasTag But _this is NULL."));
		return false;
	}
	if (tag == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] HasTag But tag is NULL."));
		return false;
	}
	FName tag_name = FName((TCHAR*)mono_string_to_utf16(tag));
	return _this->ComponentHasTag(tag_name);
}

static void UnrealEngine_ActorComponent_SendEvent(UMonoComponent* _this, MonoString* evt)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SendEvent But _this is NULL."));
		return ;
	}
	if (evt == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SendEvent But evt is NULL."));
		return ;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(evt));
	_this->OnMonoEvent.Broadcast(evt_name);
}

static void UnrealEngine_ActorComponent_SendEventWithString(UMonoComponent* _this, MonoString* evt, MonoString* data)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SendEventWithString But _this is NULL."));
		return ;
	}
	if (evt == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SendEventWithString But evt is NULL."));
		return ;
	}
	if (data == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SendEventWithString But data is NULL."));
		return;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(evt));
	FString data_string = FString((TCHAR*)mono_string_to_utf16(data));
	_this->OnMonoEventWithString.Broadcast(evt_name, data_string);
}

static void UnrealEngine_ActorComponent_SendEventWithInt(UMonoComponent* _this, MonoString* evt, int data)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SendEventWithInt But _this is NULL."));
		return ;
	}
	if (evt == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SendEventWithInt But evt is NULL."));
		return ;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(evt));
	_this->OnMonoEventWithInt.Broadcast(evt_name, data);
}
#endif

#if 1
static FTransform UnrealEngine_SceneComponent_GetTransform(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetTransform But _this is NULL."));
		return FTransform::Identity;
	}
	return _this->GetComponentTransform();
}

static void UnrealEngine_SceneComponent_SetTransform(USceneComponent* _this, FTransform trans)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SetTransform But _this is NULL."));
		return;
	}
	_this->SetWorldTransform(trans);
}

static FVector UnrealEngine_SceneComponent_GetPosition(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetPosition But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetComponentLocation();
}

static void UnrealEngine_SceneComponent_SetPosition(USceneComponent* _this, FVector pos)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SetPosition But _this is NULL."));
		return;
	}
	_this->SetWorldLocation(pos);
}

static FQuat UnrealEngine_SceneComponent_GetRotation(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetRotation But _this is NULL."));
		return FQuat::Identity;
	}
	return _this->GetComponentQuat();
}

static void UnrealEngine_SceneComponent_SetRotation(USceneComponent* _this, FQuat rot)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SetRotation But _this is NULL."));
		return ;
	}
	_this->SetWorldRotation(rot);
}

static FVector UnrealEngine_SceneComponent_GetScale(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetScale But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetComponentScale();
}

static void UnrealEngine_SceneComponent_SetScale(USceneComponent* _this, FVector trans)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SetScale But _this is NULL."));
		return ;
	}
}

static FVector UnrealEngine_SceneComponent_GetForward(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] HasTag But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetForwardVector();
}

static FVector UnrealEngine_SceneComponent_GetRight(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetRight But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetRightVector();
}

static FVector UnrealEngine_SceneComponent_GetUp(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetUp But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetUpVector();
}

static FTransform UnrealEngine_SceneComponent_GetLocalTransform(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetLocalTransform But _this is NULL."));
		return FTransform::Identity;
	}
	return _this->GetRelativeTransform();
}

static void UnrealEngine_SceneComponent_SetLocalTransform(USceneComponent* _this, FTransform trans)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SetLocalTransform But _this is NULL."));
		return ;
	}
	_this->SetRelativeTransform(trans);
}

static FVector UnrealEngine_SceneComponent_GetLocalPosition(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetLocalPosition But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->RelativeLocation;
}

static void UnrealEngine_SceneComponent_SetLocalPosition(USceneComponent* _this, FVector pos)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SetLocalPosition But _this is NULL."));
		return ;
	}
	_this->SetRelativeLocation(pos);
}

static FQuat UnrealEngine_SceneComponent_GetLocalRotation(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetLocalRotation But _this is NULL."));
		return FQuat::Identity;
	}
	return FQuat(_this->RelativeRotation);
}

static void UnrealEngine_SceneComponent_SetLocalRotation(USceneComponent* _this, FQuat rot)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SetLocalRotation But _this is NULL."));
		return ;
	}
	_this->SetRelativeRotation(rot);
}

static FVector UnrealEngine_SceneComponent_GetLocalScale(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetLocalScale But _this is NULL."));
		return FVector(1,1,1);
	}
	return _this->RelativeScale3D;
}

static void UnrealEngine_SceneComponent_SetLocalScale(USceneComponent* _this, FVector scale)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SetLocalScale But _this is NULL."));
		return ;
	}
	_this->SetRelativeScale3D(scale);
}

static mono_bool UnrealEngine_SceneComponent_GetSimulatingPhysics(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetSimulatingPhysics But _this is NULL."));
		return false;
	}
	return _this->IsSimulatingPhysics();
}

static void UnrealEngine_SceneComponent_AttachTo(USceneComponent* _this, USceneComponent* parent, MonoString* socket)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] AttachTo But _this is NULL."));
		return ;
	}
	if (parent == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] AttachTo But parent is NULL."));
		return;
	}
	if (socket == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] AttachTo But socket is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(socket));
	_this->AttachToComponent(parent, FAttachmentTransformRules::KeepRelativeTransform,name);
}

static void UnrealEngine_SceneComponent_SnapTo(USceneComponent* _this, USceneComponent* parent, MonoString* socket)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SnapTo But _this is NULL."));
		return;
	}
	if (parent == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SnapTo But parent is NULL."));
		return;
	}
	if (socket == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SnapTo But socket is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(socket));
	_this->SnapTo(parent, name);
}

static void UnrealEngine_SceneComponent_Detach(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] Detach But _this is NULL."));
		return ;
	}
	_this->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

static MonoString* UnrealEngine_SceneComponent_GetAttachedSocket(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetAttachedSocket But _this is NULL."));
		return NULL;
	}
	auto name = _this->GetAttachSocketName().GetPlainWIDEString();
	return mono_string_from_utf16((mono_unichar2*)name);
}

static FTransform UnrealEngine_SceneComponent_GetSocketTransform(USceneComponent* _this, MonoString* socket)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetSocketTransform But _this is NULL."));
		return FTransform::Identity;
	}
	if (socket == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetSocketTransform But socket is NULL."));
		return FTransform::Identity;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(socket));
	return _this->GetSocketTransform(name);
}

static FVector UnrealEngine_SceneComponent_GetSocketLocation(USceneComponent* _this, MonoString* socket)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetSocketLocation But _this is NULL."));
		return FVector::ZeroVector;
	}
	if (socket == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetSocketLocation But socket is NULL."));
		return FVector::ZeroVector;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(socket));
	return _this->GetSocketLocation(name);
}

static FQuat UnrealEngine_SceneComponent_GetSocketRotation(USceneComponent* _this, MonoString* socket)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetSocketRotation But _this is NULL."));
		return FQuat::Identity;
	}
	if (socket == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetSocketRotation But socket is NULL."));
		return FQuat::Identity;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(socket));
	return FQuat(_this->GetSocketRotation(name));
}

static mono_bool UnrealEngine_SceneComponent_DoesSocketExist(USceneComponent* _this, MonoString* socket)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] DoesSocketExist But _this is NULL."));
		return false;
	}
	if (socket == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetSocketTransform But socket is NULL."));
		return false;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(socket));
	return _this->DoesSocketExist(name);
}

static mono_bool UnrealEngine_SceneComponent_GetVisible(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetVisible But _this is NULL."));
		return false;
	}
	return _this->bVisible;
}

static void UnrealEngine_SceneComponent_SetVisible(USceneComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SetVisible But _this is NULL."));
		return;
	}
	_this->SetVisibility(value != 0);
}

static mono_bool UnrealEngine_SceneComponent_GetHiddenInGame(USceneComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] GetHiddenInGame But _this is NULL."));
		return false;
	}
	return _this->bHiddenInGame;
}

static void UnrealEngine_SceneComponent_SetHiddenInGame(USceneComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SceneComponent] SetHiddenInGame But _this is NULL."));
		return ;
	}
	_this->SetHiddenInGame(value != 0);
}
#endif


void UnrealAPI_Component::RegisterAPI() 
{
	#if 1
	//注册ActorComponent的函数
	mono_add_internal_call("UnrealEngine.ActorComponent::_GetActivited",
		reinterpret_cast<void*>(UnrealEngine_ActorComponent_GetActivited));
	mono_add_internal_call("UnrealEngine.ActorComponent::_SetActivited",
		reinterpret_cast<void*>(UnrealEngine_ActorComponent_SetActivited));
	mono_add_internal_call("UnrealEngine.ActorComponent::_GetCanEverTick",
		reinterpret_cast<void*>(UnrealEngine_ActorComponent_GetCanEverTick));
	mono_add_internal_call("UnrealEngine.ActorComponent::_SetCanEverTick",
		reinterpret_cast<void*>(UnrealEngine_ActorComponent_SetCanEverTick));
	mono_add_internal_call("UnrealEngine.ActorComponent::_GetOwner",
		reinterpret_cast<void*>(UnrealEngine_ActorComponent_GetOwner));
	mono_add_internal_call("UnrealEngine.ActorComponent::_SetTickableWhenPaused",
		reinterpret_cast<void*>(UnrealEngine_ActorComponent_SetTickableWhenPaused));
	mono_add_internal_call("UnrealEngine.ActorComponent::_HasTag",
		reinterpret_cast<void*>(UnrealEngine_ActorComponent_HasTag));
	mono_add_internal_call("UnrealEngine.ActorComponent::_SendEvent",
		reinterpret_cast<void*>(UnrealEngine_ActorComponent_SendEvent));
	mono_add_internal_call("UnrealEngine.ActorComponent::_SendEventWithString",
		reinterpret_cast<void*>(UnrealEngine_ActorComponent_SendEventWithString));
	mono_add_internal_call("UnrealEngine.ActorComponent::_SendEventWithInt",
		reinterpret_cast<void*>(UnrealEngine_ActorComponent_SendEventWithInt));
	#endif
	
	#if 1
	//注册SceneComponent的函数
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetTransform",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetTransform));
	mono_add_internal_call("UnrealEngine.SceneComponent::_SetTransform",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_SetTransform));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetPosition",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetPosition));
	mono_add_internal_call("UnrealEngine.SceneComponent::_SetPosition",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_SetPosition));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetRotation",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetRotation));
	mono_add_internal_call("UnrealEngine.SceneComponent::_SetRotation",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_SetRotation));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetScale",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetScale));
	mono_add_internal_call("UnrealEngine.SceneComponent::_SetScale",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_SetScale));
	
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetForward",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetForward));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetRight",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetRight));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetUp",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetUp));

	mono_add_internal_call("UnrealEngine.SceneComponent::_GetLocalTransform",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetLocalTransform));
	mono_add_internal_call("UnrealEngine.SceneComponent::_SetLocalTransform",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_SetLocalTransform));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetLocalPosition",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetLocalPosition));
	mono_add_internal_call("UnrealEngine.SceneComponent::_SetLocalPosition",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_SetLocalPosition));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetLocalRotation",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetLocalRotation));
	mono_add_internal_call("UnrealEngine.SceneComponent::_SetLocalRotation",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_SetLocalRotation));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetLocalScale",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetLocalScale));
	mono_add_internal_call("UnrealEngine.SceneComponent::_SetLocalScale",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_SetLocalScale));

	mono_add_internal_call("UnrealEngine.SceneComponent::_AttachTo",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_AttachTo));
	mono_add_internal_call("UnrealEngine.SceneComponent::_SnapTo",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_SnapTo));
	mono_add_internal_call("UnrealEngine.SceneComponent::_Detach",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_Detach));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetAttachedSocket",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetAttachedSocket));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetSocketTransform",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetSocketTransform));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetSocketLocation",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetSocketLocation));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetSocketRotation",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetSocketRotation));
	mono_add_internal_call("UnrealEngine.SceneComponent::_DoesSocketExist",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_DoesSocketExist));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetVisible",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetVisible));
	mono_add_internal_call("UnrealEngine.SceneComponent::_SetVisible",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_SetVisible));
	mono_add_internal_call("UnrealEngine.SceneComponent::_GetHiddenInGame",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_GetHiddenInGame));
	mono_add_internal_call("UnrealEngine.SceneComponent::_SetHiddenInGame",
		reinterpret_cast<void*>(UnrealEngine_SceneComponent_SetHiddenInGame));
	#endif


}
