#include "SharpUnrealPrivatePCH.h"
#include "MonoComponent.h"
#include "SharpUnreal.h"
#include "UnrealAPI_NetWork.h"

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

static void UnrealEngine_NetWorkBehavior_StartOnlineGame(UMonoComponent* _this, MonoString* mapName, int32 playerNum)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] StartOnlineGame But _this is NULL."));
		return;
	}

	if (mapName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] StartOnlineGame But mapName is NULL."));
		return;
	}

	FString map_name = FString((TCHAR*)mono_string_to_utf16(mapName));
	_this->StartOnlineGame(map_name, playerNum);
}

static void UnrealEngine_NetWorkBehavior_FindOnlineGame(UMonoComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] FindOnlineGame But _this is NULL."));
		return;
	}

	_this->FindOnlineGames();
}

static void UnrealEngine_NetWorkBehavior_JoinOnlineGame(UMonoComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] JoinOnlineGame But _this is NULL."));
		return;
	}

	_this->JoinOnlineGame();
}

static void UnrealEngine_NetWorkBehavior_DestroySessionAndLeaveGame(UMonoComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] DestroySessionAndLeaveGame But _this is NULL."));
		return;
	}

	_this->DestroySessionAndLeaveGame();
}

static int32 UnrealEngine_NetWorkBehavior_GetOnlineGamePlayerNum(UMonoComponent* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] GetOnlineGamePlayerNum But _this is NULL."));
		return 0;
	}

	return _this->GetOnlineGamePlayerNum();
}

void UnrealAPI_NetWork::RegisterAPI() 
{
	mono_add_internal_call("UnrealEngine.NetWorkBehavior::_StartOnlineGame",
		reinterpret_cast<void*>(UnrealEngine_NetWorkBehavior_StartOnlineGame));
	mono_add_internal_call("UnrealEngine.NetWorkBehavior::_FindOnlineGame",
		reinterpret_cast<void*>(UnrealEngine_NetWorkBehavior_FindOnlineGame));
	mono_add_internal_call("UnrealEngine.NetWorkBehavior::_JoinOnlineGame",
		reinterpret_cast<void*>(UnrealEngine_NetWorkBehavior_JoinOnlineGame));
	mono_add_internal_call("UnrealEngine.NetWorkBehavior::_DestroySessionAndLeaveGame",
		reinterpret_cast<void*>(UnrealEngine_NetWorkBehavior_DestroySessionAndLeaveGame));
	mono_add_internal_call("UnrealEngine.NetWorkBehavior::_GetOnlineGamePlayerNum",
		reinterpret_cast<void*>(UnrealEngine_NetWorkBehavior_GetOnlineGamePlayerNum));

}