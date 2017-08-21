#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "UnrealAPI_Component.h"
#include "MonoComponent.h"
#include "Components/ApplicationLifecycleComponent.h"
#include "Camera/CameraComponent.h"

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
static mono_bool UnrealEngine_ActorComponent_GetActivited(UActorComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] GetActivited But _this is NULL."));
		return false;
	}
	return _this->bIsActive;
}

static void UnrealEngine_ActorComponent_SetActivited(UActorComponent* _this, bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SetActivited But _this is NULL."));
		return;
	}
	_this->SetActive(value);
}

static mono_bool UnrealEngine_ActorComponent_GetCanEverTick(UActorComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] GetCanEverTick But _this is NULL."));
		return false;
	}
	return _this->PrimaryComponentTick.bCanEverTick;
}

static void UnrealEngine_ActorComponent_SetCanEverTick(UActorComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SetCanEverTick But _this is NULL."));
		return;
	}
	_this->PrimaryComponentTick.bCanEverTick = value;
}

static AActor* UnrealEngine_ActorComponent_GetOwner(UActorComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] GetOwner But _this is NULL."));
		return NULL;
	}
	return _this->GetOwner();
}

static void UnrealEngine_ActorComponent_SetTickableWhenPaused(UActorComponent* _this, mono_bool bTickableWhenPaused)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SetTickableWhenPaused But _this is NULL."));
		return;
	}
	_this->SetTickableWhenPaused(bTickableWhenPaused != 0);
}

static mono_bool UnrealEngine_ActorComponent_HasTag(UActorComponent* _this, MonoString* tag)
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

static MonoString* UnrealEngine_ActorComponent_GetName(UActorComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] GetName But _this is NULL."));
		return NULL;
	}
	
	MonoString* name = mono_string_from_utf16((mono_unichar2*)*_this->GetName());
	return name;
}

static void UnrealEngine_MonoComponent_SendEvent(UMonoComponent* _this, MonoString* evt)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEvent But _this is NULL."));
		return;
	}
	if (evt == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEvent But evt is NULL."));
		return;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(evt));
	_this->OnMonoEvent.Broadcast(evt_name);
}

static void UnrealEngine_MonoComponent_SendEventWithString(UMonoComponent* _this, MonoString* evt, MonoString* data)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithString But _this is NULL."));
		return;
	}
	if (evt == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithString But evt is NULL."));
		return;
	}
	if (data == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithString But data is NULL."));
		return;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(evt));
	FString data_string = FString((TCHAR*)mono_string_to_utf16(data));
	_this->OnMonoEventWithString.Broadcast(evt_name, data_string);
}

static void UnrealEngine_MonoComponent_SendEventWithInt(UMonoComponent* _this, MonoString* evt, int data)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SendEventWithInt But _this is NULL."));
		return;
	}
	if (evt == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ActorComponent] SendEventWithInt But evt is NULL."));
		return;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(evt));
	_this->OnMonoEventWithInt.Broadcast(evt_name, data);
}

static void UnrealEngine_MonoComponent_CallOnServer(UMonoComponent* _this, MonoString* func)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEvent But _this is NULL."));
		return;
	}
	if (func == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEvent But func is NULL."));
		return;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(func));
	
}

static void UnrealEngine_MonoComponent_CallOnServerWithString(UMonoComponent* _this, MonoString* func, MonoString* data)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithString But _this is NULL."));
		return;
	}
	if (func == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithString But func is NULL."));
		return;
	}
	if (data == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithString But data is NULL."));
		return;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(func));
	FString data_string = FString((TCHAR*)mono_string_to_utf16(data));
	
}

static void UnrealEngine_MonoComponent_CallOnServerWithInt(UMonoComponent* _this, MonoString* func, int data)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithInt But _this is NULL."));
		return;
	}
	if (func == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithInt But func is NULL."));
		return;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(func));
	
}

static void UnrealEngine_MonoComponent_CallOnAll(UMonoComponent* _this, MonoString* func)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEvent But _this is NULL."));
		return;
	}
	if (func == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEvent But func is NULL."));
		return;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(func));

}

static void UnrealEngine_MonoComponent_CallOnAllWithString(UMonoComponent* _this, MonoString* func, MonoString* data)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithString But _this is NULL."));
		return;
	}
	if (func == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithString But func is NULL."));
		return;
	}
	if (data == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithString But data is NULL."));
		return;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(func));
	FString data_string = FString((TCHAR*)mono_string_to_utf16(data));

}

static void UnrealEngine_MonoComponent_CallOnAllWithInt(UMonoComponent* _this, MonoString* func, int data)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithInt But _this is NULL."));
		return;
	}
	if (func == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] SendEventWithInt But func is NULL."));
		return;
	}
	FString evt_name = FString((TCHAR*)mono_string_to_utf16(func));

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

#if 1
//
static void UnrealEngine_AppLifecycleComponent_RegAppDeactivate(UApplicationLifecycleComponent* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AppLifecycleComponent] RegAppDeactivate But _this is NULL."));
		return ;
	}

	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnAppDeactivate")));
	_this->ApplicationWillDeactivateDelegate.Add(del);
}
static void UnrealEngine_AppLifecycleComponent_RegAppHasReactivated(UApplicationLifecycleComponent* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AppLifecycleComponent] RegAppHasReactivated But _this is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnAppHasReactivated")));
	_this->ApplicationWillDeactivateDelegate.Add(del);
}

static void UnrealEngine_AppLifecycleComponent_RegAppWillEnterBackground(UApplicationLifecycleComponent* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AppLifecycleComponent] RegAppWillEnterBackground But _this is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnAppWillEnterBackground")));
	_this->ApplicationWillDeactivateDelegate.Add(del);
}

static void UnrealEngine_AppLifecycleComponent_RegAppHasEnteredForeground(UApplicationLifecycleComponent* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AppLifecycleComponent] RegAppHasEnteredForeground But _this is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnAppHasEnteredForeground")));
	_this->ApplicationWillDeactivateDelegate.Add(del);
}

static void UnrealEngine_AppLifecycleComponent_RegAppWillTerminate(UApplicationLifecycleComponent* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[AppLifecycleComponent] RegAppWillTerminate But _this is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnAppWillTerminate")));
	_this->ApplicationWillDeactivateDelegate.Add(del);
}
#endif

#if 1

static float UnrealEngine_CameraComponent_GetFieldOfView(UCameraComponent* _this) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] GetFieldOfView But _this is NULL."));
		return 0.0f;
	}
	return _this->FieldOfView;
}

static void UnrealEngine_CameraComponent_SetFieldOfView(UCameraComponent* _this, float FieldOfView)
{
	_this->SetFieldOfView(FieldOfView);
}

static float UnrealEngine_CameraComponent_GetOrthoWidth(UCameraComponent* _this) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] GetOrthoWidth But _this is NULL."));
		return 0.0f;
	}
	return _this->OrthoWidth;
}

static void UnrealEngine_CameraComponent_SetOrthoWidth(UCameraComponent* _this, float value) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] SetOrthoWidth But _this is NULL."));
		return ;
	}
	_this->SetOrthoWidth(value);
}

static float UnrealEngine_CameraComponent_GetOrthoNearClipPlane(UCameraComponent* _this) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] GetOrthoNearClipPlane But _this is NULL."));
		return 0.0f;
	}
	return _this->OrthoNearClipPlane;
}

static void UnrealEngine_CameraComponent_SetOrthoNearClipPlane(UCameraComponent* _this, float value) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] SetOrthoNearClipPlane But _this is NULL."));
		return;
	}
	_this->SetOrthoNearClipPlane(value);
}

static float UnrealEngine_CameraComponent_GetOrthoFarClipPlane(UCameraComponent* _this) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] GetOrthoFarClipPlane But _this is NULL."));
		return 0.0f;
	}
	return _this->OrthoFarClipPlane;
}

static void UnrealEngine_CameraComponent_SetOrthoFarClipPlane(UCameraComponent* _this, float value) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] SetOrthoFarClipPlane But _this is NULL."));
		return;
	}
	_this->SetOrthoFarClipPlane(value);
}

static float UnrealEngine_CameraComponent_GetAspectRatio(UCameraComponent* _this) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] GetAspectRatio But _this is NULL."));
		return false;
	}
	return _this->AspectRatio;
}

static void UnrealEngine_CameraComponent_SetAspectRatio(UCameraComponent* _this, float value) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] SetAspectRatio But _this is NULL."));
		return;
	}
	_this->SetAspectRatio(value);
}

static bool UnrealEngine_CameraComponent_GetConstrainAspectRatio(UCameraComponent* _this) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] GetConstrainAspectRatio But _this is NULL."));
		return false;
	}
	return _this->bConstrainAspectRatio;
}

static void UnrealEngine_CameraComponent_SetConstrainAspectRatio(UCameraComponent* _this, bool value) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] SetConstrainAspectRatio But _this is NULL."));
		return;
	}
	_this->SetConstraintAspectRatio(value);
}

static bool UnrealEngine_CameraComponent_GetUseFieldOfViewForLOD(UCameraComponent* _this) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] GetUseFieldOfViewForLOD But _this is NULL."));
		return false;
	}
	return _this->bUseFieldOfViewForLOD;
}

static void UnrealEngine_CameraComponent_SetUseFieldOfViewForLOD(UCameraComponent* _this, bool value) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] SetUseFieldOfViewForLOD But _this is NULL."));
		return;
	}
	_this->SetUseFieldOfViewForLOD(value);
}

static bool UnrealEngine_CameraComponent_GetLockToHmd(UCameraComponent* _this) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] GetLockToHmd But _this is NULL."));
		return false;
	}
	return _this->bLockToHmd;
}

static void UnrealEngine_CameraComponent_SetLockToHmd(UCameraComponent* _this, bool value) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] SetLockToHmd But _this is NULL."));
		return;
	}
	_this->bLockToHmd = value;
}

static bool UnrealEngine_CameraComponent_GetUsePawnControlRotation(UCameraComponent* _this) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] GetUsePawnControlRotation But _this is NULL."));
		return false;
	}
	return _this->bUsePawnControlRotation;
}

static void UnrealEngine_CameraComponent_SetUsePawnControlRotation(UCameraComponent* _this, bool value) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CameraComponent] SetUsePawnControlRotation But _this is NULL."));
		return;
	}
	_this->bUsePawnControlRotation = value;
}
#endif

#if 1

static UMaterialInterface* UnrealEngine_PrimitiveComponent_GetMaterial(UPrimitiveComponent* _this, int elementIndex)
{ 
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetMaterial But _this is NULL."));
		return NULL;
	}
	
	return _this->GetMaterial(elementIndex);
}

static void UnrealEngine_PrimitiveComponent_SetMaterial(UPrimitiveComponent* _this, int elementIndex, UMaterialInterface* material)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetMaterial But _this is NULL."));
		return;
	}
	if (material == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetMaterial But material is NULL."));
		return;
	}
	_this->SetMaterial(elementIndex, material);
}

static void UnrealEngine_PrimitiveComponent_SetMaterialByName(UPrimitiveComponent* _this, MonoString* slotName, UMaterialInterface* material)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetMaterialByName But _this is NULL."));
		return;
	}
	if (slotName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetMaterialByName But slotName is NULL."));
		return;
	}
	if (material == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetMaterialByName But material is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(slotName));
	_this->SetMaterialByName(name,material);
}

//ToDo: 还没有实现 应该换到MeshComponent
static int UnrealEngine_PrimitiveComponent_GetMaterialIndex(UPrimitiveComponent* _this, MonoString* slotName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetMaterialIndex But _this is NULL."));
		return 0;
	}
	if (slotName == 0)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetMaterialIndex But slotName is NULL."));
		return 0;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(slotName));
	
	return 0;
}
//ToDo: 还没有实现 应该换到MeshComponent
static mono_bool UnrealEngine_PrimitiveComponent_IsMaterialSlotNameValid(UPrimitiveComponent* _this, MonoString* slotName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] IsMaterialSlotNameValid But _this is NULL."));
		return false;
	}
	if (slotName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] IsMaterialSlotNameValid But slotName is NULL."));
		return false;
	}
	return 0;
}

static UMaterialInstanceDynamic* UnrealEngine_PrimitiveComponent_CreateDynamicMaterial(UPrimitiveComponent* _this, int elementIndex, UMaterialInterface* source)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] CreateDynamicMaterial But _this is NULL."));
		return NULL;
	}
	if (source == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] CreateDynamicMaterial But source is NULL."));
		return NULL;
	}
	
	return _this->CreateDynamicMaterialInstance(elementIndex, source);
}

static void UnrealEngine_PrimitiveComponent_RegComponentHit(UPrimitiveComponent* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] RegComponentHit But _this is NULL."));
		return;
	}
	if (listener == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] RegComponentHit But listener is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnComponentHit")));
	_this->OnComponentHit.AddUnique(del);

}

static void UnrealEngine_PrimitiveComponent_RegComponentBeginOverlap(UPrimitiveComponent* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] RegComponentBeginOverlap But _this is NULL."));
		return;
	}
	if (listener == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] RegComponentBeginOverlap But listener is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnComponentBeginOverlap")));
	_this->OnComponentBeginOverlap.AddUnique(del);
}

static void UnrealEngine_PrimitiveComponent_RegComponentEndOverlap(UPrimitiveComponent* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] RegComponentEndOverlap But _this is NULL."));
		return;
	}
	if (listener == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] RegComponentEndOverlap But listener is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnComponentEndOverlap")));
	_this->OnComponentEndOverlap.AddUnique(del);
}

static void UnrealEngine_PrimitiveComponent_RegComponentWake(UPrimitiveComponent* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] RegComponentWake But _this is NULL."));
		return;
	}
	if (listener == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] RegComponentWake But listener is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnComponentWake")));
	_this->OnComponentWake.AddUnique(del);
}

static void UnrealEngine_PrimitiveComponent_RegComponentSleep(UPrimitiveComponent* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] RegComponentSleep But _this is NULL."));
		return;
	}
	if (listener == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] RegComponentSleep But listener is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnComponentSleep")));
	_this->OnComponentSleep.AddUnique(del);
}

static mono_bool UnrealEngine_PrimitiveComponent_GetGenerateOverlapEvents(UPrimitiveComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetGenerateOverlapEvents But _this is NULL."));
		return false;
	}
	
	return _this->bGenerateOverlapEvents;
}

static void UnrealEngine_PrimitiveComponent_SetGenerateOverlapEvents(UPrimitiveComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetGenerateOverlapEvents But _this is NULL."));
		return;
	}
	_this->bGenerateOverlapEvents = value;
}

static void UnrealEngine_PrimitiveComponent_SetSimulatePhysics(UPrimitiveComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetSimulatePhysics But _this is NULL."));
		return;
	}
	_this->SetSimulatePhysics(value != 0);
}

static void UnrealEngine_PrimitiveComponent_SetGeneratesHitEvents(UPrimitiveComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetGeneratesHitEvents But _this is NULL."));
		return;
	}
	_this->SetNotifyRigidBodyCollision(value != 0);
}

static void UnrealEngine_PrimitiveComponent_SetCollisionEnabled(UPrimitiveComponent* _this, ECollisionEnabled::Type value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetCollisionEnabled But _this is NULL."));
		return;
	}
	if (value == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetCollisionEnabled But value is NULL."));
		return;
	}
	_this->SetCollisionEnabled(value);
}

static void UnrealEngine_PrimitiveComponent_IgnoreComponentWhenMoving(UPrimitiveComponent* _this, UPrimitiveComponent* component, mono_bool shouldIgnore)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] IgnoreComponentWhenMoving But _this is NULL."));
		return;
	}
	if (component == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] IgnoreComponentWhenMoving But component is NULL."));
		return;
	}
	_this->IgnoreComponentWhenMoving(component, shouldIgnore != 0);
}

static mono_bool UnrealEngine_PrimitiveComponent_IsOverlappingComponent(UPrimitiveComponent* _this, UPrimitiveComponent* other)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] IsOverlappingComponent But _this is NULL."));
		return false;
	}
	if (other == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] IsOverlappingComponent But other is NULL."));
		return false;
	}
	return _this->IsOverlappingComponent(other);
}

static void UnrealEngine_PrimitiveComponent_SetBoundsScale(UPrimitiveComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetBoundsScale But _this is NULL."));
		return;
	}
	_this->SetBoundsScale(value);
}

static void UnrealEngine_PrimitiveComponent_SetConstraintMode(UPrimitiveComponent* _this, EDOFMode::Type value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetConstraintMode But _this is NULL."));
		return;
	}
	_this->SetConstraintMode(value);
}

static void UnrealEngine_PrimitiveComponent_AddImpulse(UPrimitiveComponent* _this, FVector Impulse, MonoString* BoneName, mono_bool bVelChange)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] AddImpulse But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] AddImpulse But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->AddImpulse(Impulse,name,bVelChange != 0);
}

static void UnrealEngine_PrimitiveComponent_AddImpulseAtLocation(UPrimitiveComponent* _this, FVector Impulse, FVector Location, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] AddImpulseAtLocation But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] AddImpulseAtLocation But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->AddImpulseAtLocation(Impulse, Location, name);
}

static void UnrealEngine_PrimitiveComponent_AddRadialImpulse(UPrimitiveComponent* _this, FVector Origin, float Radius, float Strength, ERadialImpulseFalloff Falloff, mono_bool bVelChange)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] AddRadialImpulse But _this is NULL."));
		return;
	}
	_this->AddRadialImpulse(Origin, Radius, Strength, Falloff, bVelChange != 0);
}

static void UnrealEngine_PrimitiveComponent_AddForceAtLocation(UPrimitiveComponent* _this, FVector Force, FVector Location, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] AddForceAtLocation But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] AddForceAtLocation But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->AddForceAtLocation(Force, Location, name);
}

static void UnrealEngine_PrimitiveComponent_AddRadialForce(UPrimitiveComponent* _this, FVector Origin, float Radius, float Strength, ERadialImpulseFalloff Falloff, mono_bool bAccelChange)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] AddRadialForce But _this is NULL."));
		return;
	}
	_this->AddRadialForce(Origin, Radius, Strength, Falloff, bAccelChange != 0);
}

static void UnrealEngine_PrimitiveComponent_AddTorque(UPrimitiveComponent* _this, FVector Torque, MonoString* BoneName, mono_bool bAccelChange)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] AddTorque But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] AddTorque But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->AddTorque(Torque, name, bAccelChange != 0);
}

static void UnrealEngine_PrimitiveComponent_SetPhysicsLinearVelocity(UPrimitiveComponent* _this, FVector NewVel, mono_bool bAddToCurrent, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetPhysicsLinearVelocity But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetPhysicsLinearVelocity But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->SetPhysicsAngularVelocity(NewVel, bAddToCurrent != 0, name);
}

static FVector UnrealEngine_PrimitiveComponent_GetPhysicsLinearVelocity(UPrimitiveComponent* _this, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetPhysicsLinearVelocity But _this is NULL."));
		return FVector::ZeroVector;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetPhysicsLinearVelocity But BoneName is NULL."));
		return FVector::ZeroVector;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));

	return _this->GetPhysicsLinearVelocity(name);
}

static FVector UnrealEngine_PrimitiveComponent_GetPhysicsLinearVelocityAtPoint(UPrimitiveComponent* _this, FVector Point, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetPhysicsLinearVelocityAtPoint But _this is NULL."));
		return FVector::ZeroVector;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetPhysicsLinearVelocityAtPoint But BoneName is NULL."));
		return FVector::ZeroVector;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	return _this->GetPhysicsLinearVelocityAtPoint(Point,name);
}

static void UnrealEngine_PrimitiveComponent_SetAllPhysicsLinearVelocity(UPrimitiveComponent* _this, FVector NewVel, mono_bool bAddToCurrent)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetAllPhysicsLinearVelocity But _this is NULL."));
		return;
	}
	_this->SetAllPhysicsLinearVelocity(NewVel, bAddToCurrent != 0);
}

static void UnrealEngine_PrimitiveComponent_SetPhysicsAngularVelocity(UPrimitiveComponent* _this, FVector NewAngVel, mono_bool bAddToCurrent, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetPhysicsAngularVelocity But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetPhysicsAngularVelocity But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->SetAllPhysicsAngularVelocity(NewAngVel, bAddToCurrent != 0);
}

static void UnrealEngine_PrimitiveComponent_SetPhysicsMaxAngularVelocity(UPrimitiveComponent* _this, float NewMaxAngVel, mono_bool bAddToCurrent, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetPhysicsMaxAngularVelocity But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetPhysicsMaxAngularVelocity But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->SetPhysicsMaxAngularVelocity(NewMaxAngVel, bAddToCurrent != 0);
}

static FVector UnrealEngine_PrimitiveComponent_GetPhysicsAngularVelocity(UPrimitiveComponent* _this, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetPhysicsAngularVelocity But _this is NULL."));
		return FVector::ZeroVector;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetPhysicsAngularVelocity But BoneName is NULL."));
		return FVector::ZeroVector;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));

	return _this->GetPhysicsAngularVelocity(name);
}

static FVector UnrealEngine_PrimitiveComponent_GetCenterOfMass(UPrimitiveComponent* _this, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetCenterOfMass But _this is NULL."));
		return FVector::ZeroVector;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetCenterOfMass But BoneName is NULL."));
		return FVector::ZeroVector;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	return _this->GetCenterOfMass(name);
}

static void UnrealEngine_PrimitiveComponent_SetCenterOfMass(UPrimitiveComponent* _this, FVector CenterOfMassOffset, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetCenterOfMass But _this is NULL."));
		return ;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetCenterOfMass But BoneName is NULL."));
		return ;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->SetCenterOfMass(CenterOfMassOffset, name);
}

static float UnrealEngine_PrimitiveComponent_GetClosestPointOnCollision(UPrimitiveComponent* _this, FVector Point, FVector* OutPointOnBody, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetClosestPointOnCollision But _this is NULL."));
		return 0.0f;
	}
	if (OutPointOnBody == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetClosestPointOnCollision But OutPointOnBody is NULL."));
		return 0.0f;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetClosestPointOnCollision But BoneName is NULL."));
		return 0.0f;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	FVector p;
	float ret = _this->GetClosestPointOnCollision(Point, p, name);
	OutPointOnBody->X = p.X;
	OutPointOnBody->Y = p.Y;
	OutPointOnBody->Z = p.Z;
	return ret;
}

static void UnrealEngine_PrimitiveComponent_WakeAllRigidBodies(UPrimitiveComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] WakeAllRigidBodies But _this is NULL."));
		return;
	}
	_this->WakeAllRigidBodies();
}

static mono_bool UnrealEngine_PrimitiveComponent_GetIsGravityEnabled(UPrimitiveComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetIsGravityEnabled But _this is NULL."));
		return false;
	}
	return _this->IsGravityEnabled();
}

static void UnrealEngine_PrimitiveComponent_SetIsGravityEnabled(UPrimitiveComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetIsGravityEnabled But _this is NULL."));
		return;
	}
	_this->SetEnableGravity(value != 0);
}

static float UnrealEngine_PrimitiveComponent_GetLinearDamping(UPrimitiveComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetLinearDamping But _this is NULL."));
		return 0.0f;
	}
	return _this->GetLinearDamping();
}

static void UnrealEngine_PrimitiveComponent_SetLinearDamping(UPrimitiveComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetLinearDamping But _this is NULL."));
		return;
	}
	_this->SetLinearDamping(value);
}

static float UnrealEngine_PrimitiveComponent_GetAngularDamping(UPrimitiveComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetAngularDamping But _this is NULL."));
		return 0.0f;
	}
	return _this->GetAngularDamping();
}

static void UnrealEngine_PrimitiveComponent_SetAngularDamping0(UPrimitiveComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetAngularDamping0 But _this is NULL."));
		return;
	}
	_this->SetAngularDamping(value);
}

static void UnrealEngine_PrimitiveComponent_SetMassScale(UPrimitiveComponent* _this, MonoString* BoneName, float InMassScale)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetMassScale But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetMassScale But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->SetMassScale(name,InMassScale);
}

static float UnrealEngine_PrimitiveComponent_GetMassScale(UPrimitiveComponent* _this, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetMassScale But _this is NULL."));
		return 0.0f;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetMassScale But BoneName is NULL."));
		return 0.0f;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	return _this->GetMassScale(name);
}

static void UnrealEngine_PrimitiveComponent_SetAllMassScale(UPrimitiveComponent* _this, float InMassScale)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetAllMassScale But _this is NULL."));
		return;
	}
	_this->SetAllMassScale(InMassScale);
}

static void UnrealEngine_PrimitiveComponent_SetMassOverrideInKg(UPrimitiveComponent* _this, MonoString* BoneName, float MassInKg, mono_bool bOverrideMass)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetMassOverrideInKg But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetMassOverrideInKg But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->SetMassOverrideInKg(name, MassInKg, bOverrideMass != 0);
}

static float UnrealEngine_PrimitiveComponent_GetMass(UPrimitiveComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetMass But _this is NULL."));
		return 0.0f;
	}
	return _this->GetMass();
}

static FVector UnrealEngine_PrimitiveComponent_GetInertiaTensor(UPrimitiveComponent* _this, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetInertiaTensor But _this is NULL."));
		return FVector::ZeroVector;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] GetInertiaTensor But BoneName is NULL."));
		return FVector::ZeroVector;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	return _this->GetInertiaTensor(name);
}

static FVector UnrealEngine_PrimitiveComponent_SetScaleByMomentOfInertia(UPrimitiveComponent* _this, FVector InputVector, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetScaleByMomentOfInertia But _this is NULL."));
		return FVector::ZeroVector;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetScaleByMomentOfInertia But BoneName is NULL."));
		return FVector::ZeroVector;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	return _this->ScaleByMomentOfInertia(InputVector,name);
}

static void UnrealEngine_PrimitiveComponent_SetCollisionResponseToChannel(UPrimitiveComponent* _this, ECollisionChannel Channel, ECollisionResponse NewResponse)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetCollisionResponseToChannel But _this is NULL."));
		return;
	}
	_this->SetCollisionResponseToChannel(Channel, NewResponse);
}

static void UnrealEngine_PrimitiveComponent_SetAngularDamping1(UPrimitiveComponent* _this, ECollisionResponse NewResponse)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PrimitiveComponent] SetAngularDamping1 But _this is NULL."));
		return;
	}
	_this->SetAngularDamping(NewResponse);
}

#endif

#if 1

static FVector UnrealEngine_BoxComponent_GetBoxExtent(UBoxComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[BoxComponent] GetBoxExtent But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->GetUnscaledBoxExtent();
}

static void UnrealEngine_BoxComponent_SetBoxExtent(UBoxComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[BoxComponent] SetBoxExtent But _this is NULL."));
		return;
	}
	_this->SetBoxExtent(value);
}

static FVector UnrealEngine_BoxComponent_GetShapeScale(UBoxComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[BoxComponent] GetShapeScale But _this is NULL."));
		return FVector(1,1,1);
	}
	return _this->ComponentToWorld.GetScale3D();
}

#endif

#if 1

static float UnrealEngune_CapsuleComponent_GetCapsuleHalfHeight(UCapsuleComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CapsuleComponent] GetCapsuleHalfHeight But _this is NULL."));
		return 0.0f;
	}
	return _this->GetUnscaledCapsuleHalfHeight();
}

static void UnrealEngune_CapsuleComponent_SetCapsuleHalfHeight(UCapsuleComponent* _this, float value)
{

	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CapsuleComponent] SetCapsuleHalfHeight But _this is NULL."));
		return;
	}
	_this->SetCapsuleHalfHeight(value);
}

static float UnrealEngune_CapsuleComponent_GetCapsuleRadius(UCapsuleComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CapsuleComponent] GetCapsuleRadius But _this is NULL."));
		return 0.0f;
	}
	return _this->GetUnscaledCapsuleRadius();
}

static void UnrealEngune_CapsuleComponent_SetCapsuleRadius(UCapsuleComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CapsuleComponent] SetCapsuleRadius But _this is NULL."));
		return;
	}
	_this->SetCapsuleRadius(value);
}

static float UnrealEngine_CapsuleComponent_GetShapeScale(UCapsuleComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[CapsuleComponent] GetGetShapeScale But _this is NULL."));
		return 0.0f;
	}
	return _this->GetShapeScale();
}

#endif

#if 1

static FColor UnrealEngine_ShapeComponent_GetShapeColor(UShapeComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ShapeComponent] GetShapeColor But _this is NULL."));
		return FColor::White;
	}
	return _this->ShapeColor;
}

static void UnrealEngine_ShapeComponent_SetShapeColor(UShapeComponent* _this, FColor value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ShapeComponent] SetShapeColor But _this is NULL."));
		return;
	}
	_this->ShapeColor = value;
}

#endif

#if 1

static float UnrealEngine_SphereComponent_GetSphereRadius(USphereComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SphereComponent] GetSphereRadius But _this is NULL."));
		return 0.0f;
	}
	return _this->GetUnscaledSphereRadius();
}

static void UnrealEngine_SphereComponent_SetSphereRadius(USphereComponent* _this, float value)
{

	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SphereComponent] SetSphereRadius But _this is NULL."));
		return;
	}
	_this->SetSphereRadius(value);
}

static float UnrealEngine_SphereComponent_GetShapeScale(USphereComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SphereComponent] GetShapeScale But _this is NULL."));
		return 0.0f;
	}
	return _this->GetShapeScale();
}
#endif

#if 1

static float UnrealEngine_DirectionalLightComponent_GetDynamicShadowDistanceMovableLight(UDirectionalLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] GetDynamicShadowDistanceMovableLight But _this is NULL."));
		return 0.0f;
	}
	return _this->DynamicShadowDistanceMovableLight;
}

static void UnrealEngine_DirectionalLightComponent_SetDynamicShadowDistanceMovableLight(UDirectionalLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] SetDynamicShadowDistanceMovableLight But _this is NULL."));
		return;
	}
	_this->SetDynamicShadowDistanceMovableLight(value);
}

static float UnrealEngine_DirectionalLightComponent_GetDynamicShadowDistanceStationaryLight(UDirectionalLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] GetDynamicShadowDistanceStationaryLight But _this is NULL."));
		return 0.0f;
	}
	return _this->DynamicShadowDistanceStationaryLight;
}

static void UnrealEngine_DirectionalLightComponent_SetDynamicShadowDistanceStationaryLight(UDirectionalLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] SetDynamicShadowDistanceStationaryLight But _this is NULL."));
		return;
	}
	_this->SetDynamicShadowDistanceStationaryLight(value);
}

static float UnrealEngine_DirectionalLightComponent_GetDynamicShadowCascades(UDirectionalLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] GetDynamicShadowCascades But _this is NULL."));
		return 0.0f;
	}
	return _this->DynamicShadowCascades;
}

static void UnrealEngine_DirectionalLightComponent_SetDynamicShadowCascades(UDirectionalLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] SetDynamicShadowCascades But _this is NULL."));
		return;
	}
	_this->SetDynamicShadowCascades(value);
}

static float UnrealEngine_DirectionalLightComponent_GetCascadeDistributionExponent(UDirectionalLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] GetCascadeDistributionExponent But _this is NULL."));
		return 0.0f;
	}
	return _this->CascadeDistributionExponent;
}

static void UnrealEngine_DirectionalLightComponent_SetCascadeDistributionExponent(UDirectionalLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] SetCascadeDistributionExponent But _this is NULL."));
		return;
	}
	_this->SetCascadeDistributionExponent(value);
}

static float UnrealEngine_DirectionalLightComponent_GetCascadeTransitionFraction(UDirectionalLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] GetCascadeTransitionFraction But _this is NULL."));
		return 0.0f;
	}
	return _this->CascadeTransitionFraction;
}

static void UnrealEngine_DirectionalLightComponent_SetCascadeTransitionFraction(UDirectionalLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] SetCascadeTransitionFraction But _this is NULL."));
		return;
	}
	_this->SetCascadeTransitionFraction(value);
}

static float UnrealEngine_DirectionalLightComponent_GetShadowDistanceFadeoutFraction(UDirectionalLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] GetShadowDistanceFadeoutFraction But _this is NULL."));
		return 0.0f;
	}
	return _this->ShadowDistanceFadeoutFraction;
}

static void UnrealEngine_DirectionalLightComponent_SetShadowDistanceFadeoutFraction(UDirectionalLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] SetSShadowDistanceFadeoutFraction But _this is NULL."));
		return;
	}
	_this->SetShadowDistanceFadeoutFraction(value);
}

static mono_bool UnrealEngine_DirectionalLightComponent_GetEnableLightShaftOcclusion(UDirectionalLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] GetEnableLightShaftOcclusion But _this is NULL."));
		return false;
	}
	return _this->bEnableLightShaftOcclusion;
}

static void UnrealEngine_DirectionalLightComponent_SetEnableLightShaftOcclusion(UDirectionalLightComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] SetEnableLightShaftOcclusion But _this is NULL."));
		return;
	}
	_this->SetEnableLightShaftOcclusion(value != 0);
}

static float UnrealEngine_DirectionalLightComponent_GetOcclusionMaskDarkness(UDirectionalLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] GetOcclusionMaskDarkness But _this is NULL."));
		return 0.0f;
	}
	return _this->OcclusionMaskDarkness;
}

static void UnrealEngine_DirectionalLightComponent_SetOcclusionMaskDarkness(UDirectionalLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] SetOcclusionMaskDarkness But _this is NULL."));
		return;
	}
	_this->SetOcclusionMaskDarkness(value);
}

static FVector UnrealEngine_DirectionalLightComponent_GetLightShaftOverrideDirection(UDirectionalLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] GetLightShaftOverrideDirection But _this is NULL."));
		return FVector::ZeroVector;
	}
	return _this->LightShaftOverrideDirection;
}

static void UnrealEngine_DirectionalLightComponent_SetLightShaftOverrideDirection(UDirectionalLightComponent* _this, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[DirectionalLightComponent] SetLightShaftOverrideDirection But _this is NULL."));
		return;
	}
	_this->SetLightShaftOverrideDirection(value);
}

#endif

#if 1

static float UnrealEngine_LightComponent_GetIntensity(ULightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] GetIntensity But _this is NULL."));
		return 0.0f;
	}
	return _this->Intensity;
}

static void UnrealEngine_LightComponent_SetIntensity(ULightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] SetIntensity But _this is NULL."));
		return;
	}
	return _this->SetIntensity(value);
}

static FColor UnrealEngine_LightComponent_GetLightColor(ULightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] GetLightColor But _this is NULL."));
		return FColor::White;
	}
	return _this->LightColor;
}

static void UnrealEngine_LightComponent_SetLightColor(ULightComponent* _this, FColor value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] SetLightColor But _this is NULL."));
		return;
	}
	_this->SetLightColor(value);
}

static float UnrealEngine_LightComponent_GetIndirectLightingIntensity(ULightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] GetIndirectLightingIntensity But _this is NULL."));
		return 0.0f;
	}
	return _this->IndirectLightingIntensity;
}

static void UnrealEngine_LightComponent_SetIndirectLightingIntensity(ULightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] SetIndirectLightingIntensity But _this is NULL."));
		return;
	}
	_this->SetIndirectLightingIntensity(value);
}

static float UnrealEngine_LightComponent_GetTemperature(ULightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] GetTemperature But _this is NULL."));
		return 0.0f;
	}
	return _this->Temperature;
}

static void UnrealEngine_LightComponent_SetTemperature(ULightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] SetTemperature But _this is NULL."));
		return;
	}
	_this->SetTemperature(value);
}

static mono_bool UnrealEngine_LightComponent_GetAffectIndirectLighting(ULightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] GetAffectIndirectLighting But _this is NULL."));
		return false;
	}
	return _this->bAffectDynamicIndirectLighting;
}

static void UnrealEngine_LightComponent_SetAffectIndirectLighting(ULightComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] SetAffectIndirectLighting But _this is NULL."));
		return;
	}
	_this->SetAffectDynamicIndirectLighting(value != 0);
}

static mono_bool UnrealEngine_LightComponent_GetAffectTranslucentLighting(ULightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] GetAffectTranslucentLighting But _this is NULL."));
		return false;
	}
	return _this->bAffectTranslucentLighting;
}

static void UnrealEngine_LightComponent_SetAffectTranslucentLighting(ULightComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] SetAffectTranslucentLighting But _this is NULL."));
		return;
	}
	_this->SetAffectTranslucentLighting(value != 0);
}

static mono_bool UnrealEngine_LightComponent_GetEnableLightShaftBloom(ULightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] GetEnableLightShaftBloom But _this is NULL."));
		return false;
	}
	return _this->bEnableLightShaftBloom;
}

static void UnrealEngine_LightComponent_SetEnableLightShaftBloom(ULightComponent* _this, mono_bool value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] SetEnableLightShaftBloom But _this is NULL."));
		return;
	}
	_this->SetEnableLightShaftBloom(value != 0);
}

static float UnrealEngine_LightComponent_GetBloomScale(ULightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] GetBloomScale But _this is NULL."));
		return 0.0f;
	}
	return _this->BloomScale;
}

static void UnrealEngine_LightComponent_SetBloomScale(ULightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] SetBloomScale But _this is NULL."));
		return;
	}
	_this->SetBloomScale(value);
}

static float UnrealEngine_LightComponent_GetBloomThreshold(ULightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] GetBloomThreshold But _this is NULL."));
		return 0.0f;
	}
	return _this->BloomThreshold;
}

static void UnrealEngine_LightComponent_SetBloomThreshold(ULightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] SetBloomThreshold But _this is NULL."));
		return;
	}
	_this->SetBloomThreshold(value);
}

static FColor UnrealEngine_LightComponent_GetBloomTint(ULightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] GetBloomTint But _this is NULL."));
		return FColor::White;
	}
	return _this->BloomTint;
}

static void UnrealEngine_LightComponent_SetBloomTint(ULightComponent* _this, FColor value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[LightComponent] SetBloomTint But _this is NULL."));
		return;
	}
	_this->SetBloomTint(value);
}

#endif

#if 1

static float UnrealEngine_PointLightComponent_GetAttenuationRadius(UPointLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PointLightComponent] GetAttenuationRadius But _this is NULL."));
		return 0.0f;
	}
	return _this->AttenuationRadius;
}

static void UnrealEngine_PointLightComponent_SetAttenuationRadius(UPointLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PointLightComponent] SetAttenuationRadius But _this is NULL."));
		return;
	}
	_this->SetAttenuationRadius(value);
}

static float UnrealEngine_PointLightComponent_GetLightFalloffExponent(UPointLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PointLightComponent] GetLightFalloffExponent But _this is NULL."));
		return 0.0f;
	}
	return _this->LightFalloffExponent;
}

static void UnrealEngine_PointLightComponent_SetLightFalloffExponent(UPointLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PointLightComponent] SetLightFalloffExponent But _this is NULL."));
		return;
	}
	_this->SetLightFalloffExponent(value);
}

static float UnrealEngine_PointLightComponent_GetSourceRadius(UPointLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PointLightComponent] GetSourceRadius But _this is NULL."));
		return 0.0f;
	}
	return _this->SourceRadius;
}

static void UnrealEngine_PointLightComponent_SetSourceRadius(UPointLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PointLightComponent] SetSourceRadius But _this is NULL."));
		return;
	}
	_this->SetSourceRadius(value);
}

static float UnrealEngine_PointLightComponent_GetSourceLength(UPointLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PointLightComponent] GetSourceLength But _this is NULL."));
		return 0.0f;
	}
	return _this->SourceLength;
}

static void UnrealEngine_PointLightComponent_SetSourceLength(UPointLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[PointLightComponent] SetSourceLength But _this is NULL."));
		return;
	}
	_this->SetSourceLength(value);
}

#endif

#if 1

static float UnrealEngine_SpotLightComponent_GetInnerConeAngle(USpotLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SpotLightComponent] GetInnerConeAngle But _this is NULL."));
		return 0.0f;
	}
	return _this->InnerConeAngle;
}

static void UnrealEngine_SpotLightComponent_SetInnerConeAngle(USpotLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SpotLightComponent] SetInnerConeAngle But _this is NULL."));
		return;
	}
	_this->SetInnerConeAngle(value);
}

static float UnrealEngine_SpotLightComponent_GetOuterConeAngle(USpotLightComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SpotLightComponent] GetOuterConeAngle But _this is NULL."));
		return 0.0f;
	}
	return _this->OuterConeAngle;
}

static void UnrealEngine_SpotLightComponent_SetOuterConeAngle(USpotLightComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SpotLightComponent] SetOuterConeAngle But _this is NULL."));
		return;
	}
	_this->SetOuterConeAngle(value);
}

#endif

#if 1
static void UnrealEngine_MeshComponent_SetScalarParameter(UMeshComponent* _this, MonoString* name, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MeshComponent] SetScalarParameter But _this is NULL."));
		return;
	}
	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MeshComponent] SetScalarParameter But name is NULL."));
		return;
	}
	FName n = FName((TCHAR*)mono_string_to_utf16(name));
	_this->SetScalarParameterValueOnMaterials(n,value);
}

static void UnrealEngine_MeshComponent_SetVectorParameter(UMeshComponent* _this, MonoString* name, FVector value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MeshComponent] SetVectorParameter But _this is NULL."));
		return;
	}
	if (name == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MeshComponent] SetVectorParameter But name is NULL."));
		return;
	}
	FName n = FName((TCHAR*)mono_string_to_utf16(name));
	_this->SetVectorParameterValueOnMaterials(n, value);
}

#endif

#if 1
static void UnrealEngine_ParticleSystemComponent_ActivateSystem(UParticleSystemComponent* _this, mono_bool reset)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] ActivateSystem But _this is NULL."));
		return;
	}
	_this->Activate(reset != 0);
}

static void UnrealEngine_ParticleSystemComponent_DeactivateSystem(UParticleSystemComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] DeactivateSystem But _this is NULL."));
		return;
	}
	_this->Deactivate();
}

static void UnrealEngine_ParticleSystemComponent_ResetToDefaults(UParticleSystemComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] ResetToDefaults But _this is NULL."));
		return;
	}
	_this->ResetToDefaults();
}

static void UnrealEngine_ParticleSystemComponent_SetFloatParameter(UParticleSystemComponent* _this, MonoString* ParameterName, float Param)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] SetFloatParameter But _this is NULL."));
		return;
	}
	if (ParameterName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] SetFloatParameter But ParameterName is NULL."));
		return;
	}
	FName n = FName((TCHAR*)mono_string_to_utf16(ParameterName));
	_this->SetFloatParameter(n, Param);
}

static void UnrealEngine_ParticleSystemComponent_SetVectorParameter(UParticleSystemComponent* _this, MonoString* ParameterName, FVector Param)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] SetVectorParameter But _this is NULL."));
		return;
	}
	if (ParameterName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] SetVectorParameter But ParameterName is NULL."));
		return;
	}
	FName n = FName((TCHAR*)mono_string_to_utf16(ParameterName));
	_this->SetVectorParameter(n, Param);
}

static void UnrealEngine_ParticleSystemComponent_SetColorParameter(UParticleSystemComponent* _this, MonoString* ParameterName, FLinearColor Param)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] SetColorParameter But _this is NULL."));
		return;
	}
	if (ParameterName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] SetColorParameter But ParameterName is NULL."));
		return;
	}
	FName n = FName((TCHAR*)mono_string_to_utf16(ParameterName));
	_this->SetColorParameter(n, Param);
}

static float UnrealEngine_ParticleSystemComponent_GetFloatParameter(UParticleSystemComponent* _this, MonoString* ParameterName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] GetFloatParameter But _this is NULL."));
		return 0.0f;
	}
	if (ParameterName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] GetFloatParameter But ParameterName is NULL."));
		return 0.0f;
	}
	FName n = FName((TCHAR*)mono_string_to_utf16(ParameterName));
	float ret;
	_this->GetFloatParameter(n, ret);
	return ret;
}

static FVector UnrealEngine_ParticleSystemComponent_GetVectorParameter(UParticleSystemComponent* _this, MonoString* ParameterName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] GetVectorParameter But _this is NULL."));
		return FVector::ZeroVector;
	}
	if (ParameterName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] GetVectorParameter But ParameterName is NULL."));
		return FVector::ZeroVector;
	}
	FName n = FName((TCHAR*)mono_string_to_utf16(ParameterName));
	FVector ret;
	_this->GetVectorParameter(n, ret);
	return ret;
}

static FLinearColor UnrealEngine_ParticleSystemComponent_GetColorParameter(UParticleSystemComponent* _this, MonoString* ParameterName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] GetColorParameter But _this is NULL."));
		return FLinearColor::White;
	}
	if (ParameterName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] GetColorParameter But ParameterName is NULL."));
		return FLinearColor::White;
	}
	FName n = FName((TCHAR*)mono_string_to_utf16(ParameterName));
	FLinearColor ret;
	_this->GetColorParameter(n, ret);
	return ret;
}

static void UnrealEngine_ParticleSystemComponent_RegParticleSpawn(UParticleSystemComponent* _this, UActorComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] RegParticleSpawn But _this is NULL."));
		return;
	}
	if (listener == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] RegParticleSpawn But listener is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnParticleSpawn")));
	_this->OnParticleSpawn.Add(del);

}

static void UnrealEngine_ParticleSystemComponent_RegParticleBurst(UParticleSystemComponent* _this, UActorComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] RegParticleBurst But _this is NULL."));
		return;
	}
	if (listener == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] RegParticleBurst But listener is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnParticleBurst")));
	_this->OnParticleBurst.Add(del);
}

static void UnrealEngine_ParticleSystemComponent_RegParticleDeath(UParticleSystemComponent* _this, UActorComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] RegParticleDeath But _this is NULL."));
		return;
	}
	if (listener == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] RegParticleDeath But listener is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnParticleDeath")));
	_this->OnParticleDeath.Add(del);
}

static void UnrealEngine_ParticleSystemComponent_RegParticleCollide(UParticleSystemComponent* _this, UActorComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] RegParticleCollide But _this is NULL."));
		return;
	}
	if (listener == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] RegParticleCollide But listener is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnParticleCollide")));
	_this->OnParticleCollide.Add(del);
}

static void UnrealEngine_ParticleSystemComponent_RegSystemFinished(UParticleSystemComponent* _this, UActorComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] RegSystemFinished But _this is NULL."));
		return;
	}
	if (listener == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[ParticleSystemComponent] RegSystemFinished But listener is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnSystemFinished")));
	_this->OnSystemFinished.Add(del);
}

#endif

#if 1

static float UnrealEngine_SkeletalMeshComponent_GetGlobalAnimRateScale(USkeletalMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkeletalMeshComponent] GetGlobalAnimRateScale But _this is NULL."));
		return 0.0f;
	}
	return _this->GlobalAnimRateScale;
}

static void UnrealEngine_SkeletalMeshComponent_SetGlobalAnimRateScale(USkeletalMeshComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkeletalMeshComponent] SetGlobalAnimRateScale But _this is NULL."));
		return;
	}
	_this->GlobalAnimRateScale = value;
}

static void UnrealEngine_SkeletalMeshComponent_Play(USkeletalMeshComponent* _this, mono_bool looping)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkeletalMeshComponent] SetPlay But _this is NULL."));
		return;
	}
	_this->Play(looping != 0);
}

static void UnrealEngine_SkeletalMeshComponent_Stop(USkeletalMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkeletalMeshComponent] Stop But _this is NULL."));
		return;
	}
	_this->Stop();
}

static bool UnrealEngine_SkeletalMeshComponent_GetIsPlaying(USkeletalMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkeletalMeshComponent] GetIsPlaying But _this is NULL."));
		return false;
	}
	return _this->IsPlaying();
}

static float UnrealEngine_SkeletalMeshComponent_GetPlayRate(USkeletalMeshComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkeletalMeshComponent] GetPlayRate But _this is NULL."));
		return 0.0f;
	}
	return _this->GetPlayRate();
}

static void UnrealEngine_SkeletalMeshComponent_SetPlayRate(USkeletalMeshComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkeletalMeshComponent] SetPlayRate But _this is NULL."));
		return;
	}
	_this->SetPlayRate(value);
}

static void UnrealEngine_SkeletalMeshComponent_SetEnableBodyGravity(USkeletalMeshComponent* _this, mono_bool bEnableGravity, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkeletalMeshComponent] SetEnableBodyGravity But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkeletalMeshComponent] SetEnableBodyGravity But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->SetEnableBodyGravity(bEnableGravity != 0, name);
}

static bool UnrealEngine_SkeletalMeshComponent_IsBodyGravityEnabled(USkeletalMeshComponent* _this, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkeletalMeshComponent] IsBodyGravityEnabled But _this is NULL."));
		return false;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkeletalMeshComponent] IsBodyGravityEnabled But BoneName is NULL."));
		return false;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));

	return _this->IsBodyGravityEnabled(name);
}

#endif

#if 1

static int UnrealEngine_SkinnedMeshComponent_GetBoneIndex(USkinnedMeshComponent* _this, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetBoneIndex But _this is NULL."));
		return NULL;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetBoneIndex But BoneName is NULL."));
		return NULL;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	return _this->GetBoneIndex(name);
}

static MonoString* UnrealEngine_SkinnedMeshComponent_GetBoneName(USkinnedMeshComponent* _this, int BoneIndex)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetBoneName But _this is NULL."));
		return NULL;
	}
	MonoString* ret = mono_string_from_utf16((mono_unichar2*)_this->GetBoneName(BoneIndex).GetPlainWIDEString());
	return ret;
}

static MonoString* UnrealEngine_SkinnedMeshComponent_GetSocketBoneName(USkinnedMeshComponent* _this, MonoString* InSocketName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetSocketBoneName But _this is NULL."));
		return NULL;
	}
	if (InSocketName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetSocketBoneName But InSocketName is NULL."));
		return NULL;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(InSocketName));
	MonoString* ret = mono_string_from_utf16((mono_unichar2*)_this->GetSocketBoneName(name).GetPlainWIDEString());
	return ret;
}

static MonoString* UnrealEngine_SkinnedMeshComponent_GetParentBone(USkinnedMeshComponent* _this, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetParentBone But _this is NULL."));
		return NULL;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetParentBone But BoneName is NULL."));
		return NULL;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	MonoString* ret = mono_string_from_utf16((mono_unichar2*) _this->GetParentBone(name).GetPlainWIDEString());
	return ret;
}

static FMatrix UnrealEngine_SkinnedMeshComponent_GetBoneMatrix(USkinnedMeshComponent* _this, int BoneIndex)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetBoneMatrix But _this is NULL."));
		return FMatrix::Identity;
	}
	return _this->GetBoneMatrix(BoneIndex);
}

static FTransform UnrealEngine_SkinnedMeshComponent_GetBoneTransform0(USkinnedMeshComponent* _this, int BoneIndex, FTransform LocalToWorld)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetBoneTransform But _this is NULL."));
		return FTransform::Identity;
	}
	return _this->GetBoneTransform(BoneIndex,LocalToWorld);
}

static FTransform UnrealEngine_SkinnedMeshComponent_GetBoneTransform1(USkinnedMeshComponent* _this, int BoneIndex)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetBoneTransform But _this is NULL."));
		return FTransform::Identity;
	}
	return _this->GetBoneTransform(BoneIndex);
}

static FQuat UnrealEngine_SkinnedMeshComponent_GetBoneQuaternion(USkinnedMeshComponent* _this, MonoString* BoneName, EBoneSpaces::Type space)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetBoneQuaternion But _this is NULL."));
		return FQuat::Identity;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetBoneQuaternion But BoneName is NULL."));
		return FQuat::Identity;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	return _this->GetBoneQuaternion(name,space);
}

static FVector UnrealEngine_SkinnedMeshComponent_GetBoneLocation(USkinnedMeshComponent* _this, MonoString* BoneName, EBoneSpaces::Type Space)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetBoneLocation But _this is NULL."));
		return FVector::ZeroVector;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] GetBoneLocation But BoneName is NULL."));
		return FVector::ZeroVector;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	return _this->GetBoneLocation(name,Space);
}

static void UnrealEngine_SkinnedMeshComponent_HideBoneByName(USkinnedMeshComponent* _this, MonoString* BoneName, EPhysBodyOp PhysBodyOption)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] HideBoneByName But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] HideBoneByName But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->HideBoneByName(name, PhysBodyOption);
}

static void UnrealEngine_SkinnedMeshComponent_UnHideBoneByName(USkinnedMeshComponent* _this, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] UnHideBoneByName But _this is NULL."));
		return;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] UnHideBoneByName But BoneName is NULL."));
		return;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	_this->UnHideBoneByName(name);
}

static mono_bool UnrealEngine_SkinnedMeshComponent_IsBoneHiddenByName(USkinnedMeshComponent* _this, MonoString* BoneName)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] IsBoneHiddenByName But _this is NULL."));
		return false;
	}
	if (BoneName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[SkinnedMeshComponent] IsBoneHiddenByName But BoneName is NULL."));
		return false;
	}
	FName name = FName((TCHAR*)mono_string_to_utf16(BoneName));
	return _this->IsBoneHiddenByName(name);
}

#endif

#if 1

static MonoString* UnrealEngine_TextRenderComponent_GetText(UTextRenderComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] GetText But _this is NULL."));
		return NULL;
	}
	MonoString* ret = mono_string_from_utf16((mono_unichar2*)*_this->Text.ToString());
	return ret;
}

static void UnrealEngine_TextRenderComponent_SetText(UTextRenderComponent* _this, MonoString* value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] SetText But _this is NULL."));
		return;
	}
	if (value == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] SetText But value is NULL."));
		return;
	}
	FText val = FText();
	val.FromString(FString((TCHAR*)mono_string_to_utf16(value)));
	_this->SetText(val);
}

static FColor UnrealEngine_TextRenderComponent_GetColor(UTextRenderComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] GetColor But _this is NULL."));
		return FColor::White;
	}
	return _this->TextRenderColor;
}

static void UnrealEngine_TextRenderComponent_SetColor(UTextRenderComponent* _this, FColor value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] SetColor But _this is NULL."));
		return;
	}
	_this->SetTextRenderColor(value);
}

//ToDo:
static float UnrealEngine_TextRenderComponent_GetSourceLength(UTextRenderComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] GetSourceLength But _this is NULL."));
		return 0.0f;
	}
	return 0.0f;
}

//ToDo:
static void UnrealEngine_TextRenderComponent_SetSourceLength(UTextRenderComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] SetSourceLength But _this is NULL."));
		return;
	}
	
}

static float UnrealEngine_TextRenderComponent_GetXScale(UTextRenderComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] GetXScale But _this is NULL."));
		return 0.0f;
	}
	return _this->XScale;
}

static void UnrealEngine_TextRenderComponent_SetXScale(UTextRenderComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] SetXScale But _this is NULL."));
		return;
	}
	_this->SetXScale(value);
}

static float UnrealEngine_TextRenderComponent_GetYScale(UTextRenderComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] GetYScale But _this is NULL."));
		return 0.0f;
	}
	return _this->YScale;
}

static void UnrealEngine_TextRenderComponent_SetYScale(UTextRenderComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] SetYScale But _this is NULL."));
		return;
	}
	_this->SetYScale(value);
}

static float UnrealEngine_TextRenderComponent_GetWorldSize(UTextRenderComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] GetWorldSize But _this is NULL."));
		return 0.0f;
	}
	return _this->WorldSize;
}

static void UnrealEngine_TextRenderComponent_SetWorldSize(UTextRenderComponent* _this, float value)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[TextRenderComponent] SetWorldSize But _this is NULL."));
		return;
	}
	_this->SetWorldSize(value);
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
	mono_add_internal_call("UnrealEngine.ActorComponent::_GetName",
		reinterpret_cast<void*>(UnrealEngine_ActorComponent_GetName));
	//注册MonoComponent的函数
	mono_add_internal_call("UnrealEngine.MonoComponent::_SendEvent",
		reinterpret_cast<void*>(UnrealEngine_MonoComponent_SendEvent));
	mono_add_internal_call("UnrealEngine.MonoComponent::_SendEventWithString",
		reinterpret_cast<void*>(UnrealEngine_MonoComponent_SendEventWithString));
	mono_add_internal_call("UnrealEngine.MonoComponent::_SendEventWithInt",
		reinterpret_cast<void*>(UnrealEngine_MonoComponent_SendEventWithInt));

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
	
	#if 1
	//注册AppLifecycleComponent的回调
	mono_add_internal_call("UnrealEngine.AppLifecycleComponent::_RegAppDeactivate",
		reinterpret_cast<void*>(UnrealEngine_AppLifecycleComponent_RegAppDeactivate));
	mono_add_internal_call("UnrealEngine.AppLifecycleComponent::_RegAppHasReactivated",
		reinterpret_cast<void*>(UnrealEngine_AppLifecycleComponent_RegAppHasReactivated));
	mono_add_internal_call("UnrealEngine.AppLifecycleComponent::_RegAppWillEnterBackground",
		reinterpret_cast<void*>(UnrealEngine_AppLifecycleComponent_RegAppWillEnterBackground));
	mono_add_internal_call("UnrealEngine.AppLifecycleComponent::_RegAppHasEnteredForeground",
		reinterpret_cast<void*>(UnrealEngine_AppLifecycleComponent_RegAppHasEnteredForeground));
	mono_add_internal_call("UnrealEngine.AppLifecycleComponent::_RegAppWillTerminate",
		reinterpret_cast<void*>(UnrealEngine_AppLifecycleComponent_RegAppWillTerminate));
	#endif

	#if 1
	//注册CameraComponent的函数
	mono_add_internal_call("UnrealEngine.CameraComponent::_GetFieldOfView",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_GetFieldOfView));
	mono_add_internal_call("UnrealEngine.CameraComponent::_SetFieldOfView",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_SetFieldOfView));
	mono_add_internal_call("UnrealEngine.CameraComponent::_GetOrthoWidth",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_GetOrthoWidth));
	mono_add_internal_call("UnrealEngine.CameraComponent::_SetOrthoWidth",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_SetOrthoWidth));
	mono_add_internal_call("UnrealEngine.CameraComponent::_GetOrthoNearClipPlane",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_GetOrthoNearClipPlane));
	mono_add_internal_call("UnrealEngine.CameraComponent::_SetOrthoNearClipPlane",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_SetOrthoNearClipPlane));
	mono_add_internal_call("UnrealEngine.CameraComponent::_GetOrthoFarClipPlane",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_GetOrthoFarClipPlane));
	mono_add_internal_call("UnrealEngine.CameraComponent::_SetOrthoFarClipPlane",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_SetOrthoFarClipPlane));
	mono_add_internal_call("UnrealEngine.CameraComponent::_GetAspectRatio",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_GetAspectRatio));
	mono_add_internal_call("UnrealEngine.CameraComponent::_SetAspectRatio",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_SetAspectRatio));
	mono_add_internal_call("UnrealEngine.CameraComponent::_GetConstrainAspectRatio",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_GetConstrainAspectRatio));
	mono_add_internal_call("UnrealEngine.CameraComponent::_SetConstrainAspectRatio",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_SetConstrainAspectRatio));
	mono_add_internal_call("UnrealEngine.CameraComponent::_GetUseFieldOfViewForLOD",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_GetUseFieldOfViewForLOD));
	mono_add_internal_call("UnrealEngine.CameraComponent::_SetUseFieldOfViewForLOD",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_SetUseFieldOfViewForLOD));
	mono_add_internal_call("UnrealEngine.CameraComponent::_GetLockToHmd",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_GetLockToHmd));
	mono_add_internal_call("UnrealEngine.CameraComponent::_SetLockToHmd",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_SetLockToHmd));
	mono_add_internal_call("UnrealEngine.CameraComponent::_GetUsePawnControlRotation",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_GetUsePawnControlRotation));
	mono_add_internal_call("UnrealEngine.CameraComponent::_SetUsePawnControlRotation",
		reinterpret_cast<void*>(UnrealEngine_CameraComponent_SetUsePawnControlRotation));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetMaterial",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetMaterial));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetMaterial",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetMaterial));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetMaterialByName",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetMaterialByName));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetMaterialIndex",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetMaterialIndex));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_IsMaterialSlotNameValid",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_IsMaterialSlotNameValid));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_CreateDynamicMaterial",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_CreateDynamicMaterial));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_RegComponentHit",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_RegComponentHit));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_RegComponentBeginOverlap",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_RegComponentBeginOverlap));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_RegComponentEndOverlap",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_RegComponentEndOverlap));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_RegComponentWake",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_RegComponentWake));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_RegComponentSleep",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_RegComponentSleep));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetGenerateOverlapEvents",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetGenerateOverlapEvents));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetGenerateOverlapEvents",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetGenerateOverlapEvents)); 
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetSimulatePhysics",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetSimulatePhysics));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetGeneratesHitEvents",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetGeneratesHitEvents));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetCollisionEnabled",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetCollisionEnabled));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_IgnoreComponentWhenMoving",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_IgnoreComponentWhenMoving));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_IsOverlappingComponent",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_IsOverlappingComponent));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetBoundsScale",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetBoundsScale));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetConstraintMode",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetConstraintMode));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_AddImpulse",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_AddImpulse));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_AddImpulseAtLocation",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_AddImpulseAtLocation));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_AddRadialImpulse",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_AddRadialImpulse));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_AddForceAtLocation",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_AddForceAtLocation));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_AddRadialForce",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_AddRadialForce));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_AddTorque",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_AddTorque));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetPhysicsLinearVelocity",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetPhysicsLinearVelocity));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetPhysicsLinearVelocity",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetPhysicsLinearVelocity));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetPhysicsLinearVelocityAtPoint",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetPhysicsLinearVelocityAtPoint));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetAllPhysicsLinearVelocity",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetAllPhysicsLinearVelocity));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetPhysicsAngularVelocity",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetPhysicsAngularVelocity));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetPhysicsMaxAngularVelocity",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetPhysicsMaxAngularVelocity));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetPhysicsAngularVelocity",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetPhysicsAngularVelocity));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetCenterOfMass",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetCenterOfMass));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetCenterOfMass",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetCenterOfMass));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetClosestPointOnCollision",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetClosestPointOnCollision));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_WakeAllRigidBodies",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_WakeAllRigidBodies));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetIsGravityEnabled",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetIsGravityEnabled));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetIsGravityEnabled",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetIsGravityEnabled));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetLinearDamping",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetLinearDamping));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetLinearDamping",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetLinearDamping));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetAngularDamping",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetAngularDamping));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetAngularDamping0",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetAngularDamping0));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetMassScale",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetMassScale));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetMassScale",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetMassScale));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetAllMassScale",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetAllMassScale));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetMassOverrideInKg",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetMassOverrideInKg));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetMass",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetMass));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_GetInertiaTensor",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_GetInertiaTensor));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetScaleByMomentOfInertia",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetScaleByMomentOfInertia));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetCollisionResponseToChannel",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetCollisionResponseToChannel));
	mono_add_internal_call("UnrealEngine.PrimitiveComponent::_SetAngularDamping1",
		reinterpret_cast<void*>(UnrealEngine_PrimitiveComponent_SetAngularDamping1));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.BoxComponent::_GetBoxExtent",
		reinterpret_cast<void*>(UnrealEngine_BoxComponent_GetBoxExtent));
	mono_add_internal_call("UnrealEngine.BoxComponent::_SetBoxExtent",
		reinterpret_cast<void*>(UnrealEngine_BoxComponent_SetBoxExtent));
	mono_add_internal_call("UnrealEngine.BoxComponent::_GetShapeScale",
		reinterpret_cast<void*>(UnrealEngine_BoxComponent_GetShapeScale));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.CapsuleComponent::_GetCapsuleHalfHeight",
		reinterpret_cast<void*>(UnrealEngune_CapsuleComponent_GetCapsuleHalfHeight));
	mono_add_internal_call("UnrealEngine.CapsuleComponent::_SetCapsuleHalfHeight",
		reinterpret_cast<void*>(UnrealEngune_CapsuleComponent_SetCapsuleHalfHeight));
	mono_add_internal_call("UnrealEngine.CapsuleComponent::_GetCapsuleRadius",
		reinterpret_cast<void*>(UnrealEngune_CapsuleComponent_GetCapsuleRadius));
	mono_add_internal_call("UnrealEngine.CapsuleComponent::_SetCapsuleRadius",
		reinterpret_cast<void*>(UnrealEngune_CapsuleComponent_SetCapsuleRadius));
	mono_add_internal_call("UnrealEngine.CapsuleComponent::_GetShapeScale",
		reinterpret_cast<void*>(UnrealEngine_CapsuleComponent_GetShapeScale));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.ShapeComponent::_GetShapeColor",
		reinterpret_cast<void*>(UnrealEngine_ShapeComponent_GetShapeColor));
	mono_add_internal_call("UnrealEngine.ShapeComponent::_SetShapeColor",
		reinterpret_cast<void*>(UnrealEngine_ShapeComponent_SetShapeColor));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.SphereComponent::_GetSphereRadius",
		reinterpret_cast<void*>(UnrealEngine_SphereComponent_GetSphereRadius));
	mono_add_internal_call("UnrealEngine.SphereComponent::_SetSphereRadius",
		reinterpret_cast<void*>(UnrealEngine_SphereComponent_SetSphereRadius));
	mono_add_internal_call("UnrealEngine.SphereComponent::_GetShapeScale",
		reinterpret_cast<void*>(UnrealEngine_SphereComponent_GetShapeScale));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_GetDynamicShadowDistanceMovableLight",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_GetDynamicShadowDistanceMovableLight));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_SetDynamicShadowDistanceMovableLight",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_SetDynamicShadowDistanceMovableLight));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_GetDynamicShadowDistanceStationaryLight",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_GetDynamicShadowDistanceStationaryLight));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_SetDynamicShadowDistanceStationaryLight",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_SetDynamicShadowDistanceStationaryLight));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_GetDynamicShadowCascades",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_GetDynamicShadowCascades));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_SetDynamicShadowCascades",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_SetDynamicShadowCascades));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_GetCascadeDistributionExponent",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_GetCascadeDistributionExponent));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_SetCascadeDistributionExponent",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_SetCascadeDistributionExponent));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_GetCascadeTransitionFraction",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_GetCascadeTransitionFraction));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_SetCascadeTransitionFraction",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_SetCascadeTransitionFraction));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_GetShadowDistanceFadeoutFraction",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_GetShadowDistanceFadeoutFraction));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_SetShadowDistanceFadeoutFraction",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_SetShadowDistanceFadeoutFraction));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_GetEnableLightShaftOcclusion",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_GetEnableLightShaftOcclusion));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_SetEnableLightShaftOcclusion",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_SetEnableLightShaftOcclusion));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_GetOcclusionMaskDarkness",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_GetOcclusionMaskDarkness));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_SetOcclusionMaskDarkness",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_SetOcclusionMaskDarkness));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_GetLightShaftOverrideDirection",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_GetLightShaftOverrideDirection));
	mono_add_internal_call("UnrealEngine.DirectionalLightComponent::_SetLightShaftOverrideDirection",
		reinterpret_cast<void*>(UnrealEngine_DirectionalLightComponent_SetLightShaftOverrideDirection));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.LightComponent::_GetIntensity",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_GetIntensity));
	mono_add_internal_call("UnrealEngine.LightComponent::_SetIntensity",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_SetIntensity));
	mono_add_internal_call("UnrealEngine.LightComponent::_GetLightColor",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_GetLightColor));
	mono_add_internal_call("UnrealEngine.LightComponent::_SetLightColor",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_SetLightColor));
	mono_add_internal_call("UnrealEngine.LightComponent::_GetIndirectLightingIntensity",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_GetIndirectLightingIntensity));
	mono_add_internal_call("UnrealEngine.LightComponent::_SetIndirectLightingIntensity",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_SetIndirectLightingIntensity));
	mono_add_internal_call("UnrealEngine.LightComponent::_GetTemperature",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_GetTemperature));
	mono_add_internal_call("UnrealEngine.LightComponent::_SetTemperature",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_SetTemperature));
	mono_add_internal_call("UnrealEngine.LightComponent::_GetAffectIndirectLighting",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_GetAffectIndirectLighting));
	mono_add_internal_call("UnrealEngine.LightComponent::_SetAffectIndirectLighting",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_SetAffectIndirectLighting));
	mono_add_internal_call("UnrealEngine.LightComponent::_GetAffectTranslucentLighting",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_GetAffectTranslucentLighting));
	mono_add_internal_call("UnrealEngine.LightComponent::_SetAffectTranslucentLighting",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_SetAffectTranslucentLighting));
	mono_add_internal_call("UnrealEngine.LightComponent::_GetEnableLightShaftBloom",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_GetEnableLightShaftBloom));
	mono_add_internal_call("UnrealEngine.LightComponent::_SetEnableLightShaftBloom",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_SetEnableLightShaftBloom));
	mono_add_internal_call("UnrealEngine.LightComponent::_GetBloomScale",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_GetBloomScale));
	mono_add_internal_call("UnrealEngine.LightComponent::_SetBloomScale",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_SetBloomScale));
	mono_add_internal_call("UnrealEngine.LightComponent::_GetBloomThreshold",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_GetBloomThreshold));
	mono_add_internal_call("UnrealEngine.LightComponent::_SetBloomThreshold",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_SetBloomThreshold));
	mono_add_internal_call("UnrealEngine.LightComponent::_GetBloomTint",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_GetBloomTint));
	mono_add_internal_call("UnrealEngine.LightComponent::_SetBloomTint",
		reinterpret_cast<void*>(UnrealEngine_LightComponent_SetBloomTint));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.PointLightComponent::_GetAttenuationRadius",
		reinterpret_cast<void*>(UnrealEngine_PointLightComponent_GetAttenuationRadius));
	mono_add_internal_call("UnrealEngine.PointLightComponent::_SetAttenuationRadius",
		reinterpret_cast<void*>(UnrealEngine_PointLightComponent_SetAttenuationRadius));
	mono_add_internal_call("UnrealEngine.PointLightComponent::_GetLightFalloffExponent",
		reinterpret_cast<void*>(UnrealEngine_PointLightComponent_GetLightFalloffExponent));
	mono_add_internal_call("UnrealEngine.PointLightComponent::_SetLightFalloffExponent",
		reinterpret_cast<void*>(UnrealEngine_PointLightComponent_SetLightFalloffExponent));
	mono_add_internal_call("UnrealEngine.PointLightComponent::_GetSourceRadius",
		reinterpret_cast<void*>(UnrealEngine_PointLightComponent_GetSourceRadius));
	mono_add_internal_call("UnrealEngine.PointLightComponent::_SetSourceRadius",
		reinterpret_cast<void*>(UnrealEngine_PointLightComponent_SetSourceRadius));
	mono_add_internal_call("UnrealEngine.PointLightComponent::_GetSourceLength",
		reinterpret_cast<void*>(UnrealEngine_PointLightComponent_GetSourceLength));
	mono_add_internal_call("UnrealEngine.PointLightComponent::_SetSourceLength",
		reinterpret_cast<void*>(UnrealEngine_PointLightComponent_SetSourceLength));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.SpotLightComponent::_GetInnerConeAngle",
		reinterpret_cast<void*>(UnrealEngine_SpotLightComponent_GetInnerConeAngle));
	mono_add_internal_call("UnrealEngine.SpotLightComponent::_SetInnerConeAngle",
		reinterpret_cast<void*>(UnrealEngine_SpotLightComponent_SetInnerConeAngle));
	mono_add_internal_call("UnrealEngine.SpotLightComponent::_GetOuterConeAngle",
		reinterpret_cast<void*>(UnrealEngine_SpotLightComponent_GetOuterConeAngle));
	mono_add_internal_call("UnrealEngine.SpotLightComponent::_SetOuterConeAngle",
		reinterpret_cast<void*>(UnrealEngine_SpotLightComponent_SetOuterConeAngle));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.MeshComponent::_SetScalarParameter",
		reinterpret_cast<void*>(UnrealEngine_MeshComponent_SetScalarParameter));
	mono_add_internal_call("UnrealEngine.MeshComponent::_SetVectorParameter",
		reinterpret_cast<void*>(UnrealEngine_MeshComponent_SetVectorParameter));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_ActivateSystem",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_ActivateSystem));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_DeactivateSystem",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_DeactivateSystem));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_ResetToDefaults",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_ResetToDefaults));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_SetFloatParameter",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_SetFloatParameter));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_SetVectorParameter",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_SetVectorParameter));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_SetColorParameter",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_SetColorParameter));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_GetFloatParameter",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_GetFloatParameter));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_GetVectorParameter",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_GetVectorParameter));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_GetColorParameter",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_GetColorParameter));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_RegParticleSpawn",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_RegParticleSpawn));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_RegParticleBurst",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_RegParticleBurst));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_RegParticleDeath",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_RegParticleDeath));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_RegParticleCollide",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_RegParticleCollide));
	mono_add_internal_call("UnrealEngine.ParticleSystemComponent::_RegSystemFinished",
		reinterpret_cast<void*>(UnrealEngine_ParticleSystemComponent_RegSystemFinished));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.SkeletalMeshComponent::_GetGlobalAnimRateScale",
		reinterpret_cast<void*>(UnrealEngine_SkeletalMeshComponent_GetGlobalAnimRateScale));
	mono_add_internal_call("UnrealEngine.SkeletalMeshComponent::_SetGlobalAnimRateScale",
		reinterpret_cast<void*>(UnrealEngine_SkeletalMeshComponent_SetGlobalAnimRateScale));
	mono_add_internal_call("UnrealEngine.SkeletalMeshComponent::_Play",
		reinterpret_cast<void*>(UnrealEngine_SkeletalMeshComponent_Play));
	mono_add_internal_call("UnrealEngine.SkeletalMeshComponent::_Stop",
		reinterpret_cast<void*>(UnrealEngine_SkeletalMeshComponent_Stop));
	mono_add_internal_call("UnrealEngine.SkeletalMeshComponent::_GetIsPlaying",
		reinterpret_cast<void*>(UnrealEngine_SkeletalMeshComponent_GetIsPlaying));
	mono_add_internal_call("UnrealEngine.SkeletalMeshComponent::_GetPlayRate",
		reinterpret_cast<void*>(UnrealEngine_SkeletalMeshComponent_GetPlayRate));
	mono_add_internal_call("UnrealEngine.SkeletalMeshComponent::_SetPlayRate",
		reinterpret_cast<void*>(UnrealEngine_SkeletalMeshComponent_SetPlayRate));
	mono_add_internal_call("UnrealEngine.SkeletalMeshComponent::_SetEnableBodyGravity",
		reinterpret_cast<void*>(UnrealEngine_SkeletalMeshComponent_SetEnableBodyGravity));
	mono_add_internal_call("UnrealEngine.SkeletalMeshComponent::_IsBodyGravityEnabled",
		reinterpret_cast<void*>(UnrealEngine_SkeletalMeshComponent_IsBodyGravityEnabled));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_GetBoneIndex",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_GetBoneIndex));
	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_GetBoneName",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_GetBoneName));
	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_GetSocketBoneName",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_GetSocketBoneName));
	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_GetParentBone",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_GetParentBone));
	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_GetBoneMatrix",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_GetBoneMatrix));
	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_GetBoneTransform0",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_GetBoneTransform0));
	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_GetBoneTransform1",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_GetBoneTransform1));
	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_GetBoneQuaternion",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_GetBoneQuaternion));
	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_GetBoneLocation",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_GetBoneLocation));
	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_HideBoneByName",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_HideBoneByName));
	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_UnHideBoneByName",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_UnHideBoneByName));
	mono_add_internal_call("UnrealEngine.SkinnedMeshComponent::_IsBoneHiddenByName",
		reinterpret_cast<void*>(UnrealEngine_SkinnedMeshComponent_IsBoneHiddenByName));

	#endif

	#if 1

	mono_add_internal_call("UnrealEngine.TextRenderComponent::_GetText",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_GetText));
	mono_add_internal_call("UnrealEngine.TextRenderComponent::_SetText",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_SetText));
	mono_add_internal_call("UnrealEngine.TextRenderComponent::_GetColor",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_GetColor));
	mono_add_internal_call("UnrealEngine.TextRenderComponent::_SetColor",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_SetColor));
	mono_add_internal_call("UnrealEngine.TextRenderComponent::_GetSourceLength",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_GetSourceLength));
	mono_add_internal_call("UnrealEngine.TextRenderComponent::_SetSourceLength",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_SetSourceLength));
	mono_add_internal_call("UnrealEngine.TextRenderComponent::_GetXScale",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_GetXScale));
	mono_add_internal_call("UnrealEngine.TextRenderComponent::_SetXScale",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_SetXScale));
	mono_add_internal_call("UnrealEngine.TextRenderComponent::_GetYScale",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_GetYScale));
	mono_add_internal_call("UnrealEngine.TextRenderComponent::_SetYScale",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_SetYScale));
	mono_add_internal_call("UnrealEngine.TextRenderComponent::_GetWorldSize",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_GetWorldSize));
	mono_add_internal_call("UnrealEngine.TextRenderComponent::_SetWorldSize",
		reinterpret_cast<void*>(UnrealEngine_TextRenderComponent_SetWorldSize));

	#endif
}
