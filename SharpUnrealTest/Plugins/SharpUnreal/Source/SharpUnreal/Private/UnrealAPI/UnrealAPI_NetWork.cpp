#include "SharpUnrealPrivatePCH.h"
#include "UnrealAPI_NetWork.h"

#include "UnrealNetwork.h"

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

static void UnrealEngine_NetWorkManager_StartOnlineGame(UNetWorkManager* _this, MonoString* mapName, int32 playerNum)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[UNetWorkManager] StartOnlineGame But _this is NULL."));
		return;
	}

	if (mapName == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[UNetWorkManager] StartOnlineGame But mapName is NULL."));
		return;
	}

	FString map_name = FString((TCHAR*)mono_string_chars(mapName));
	_this->StartOnlineGame(map_name, playerNum);
}

static void UnrealEngine_NetWorkManager_FindOnlineGame(UNetWorkManager* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[UNetWorkManager] FindOnlineGame But _this is NULL."));
		return;
	}

	_this->FindOnlineGames();
}

static void UnrealEngine_NetWorkManager_JoinOnlineGame(UNetWorkManager* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[UNetWorkManager] JoinOnlineGame But _this is NULL."));
		return;
	}

	_this->JoinOnlineGame();
}

static void UnrealEngine_NetWorkManager_DestroySessionAndLeaveGame(UNetWorkManager* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[UNetWorkManager] DestroySessionAndLeaveGame But _this is NULL."));
		return;
	}

	_this->DestroySessionAndLeaveGame();
}

static int32 UnrealEngine_NetWorkManager_GetOnlineGamePlayerNum(UNetWorkManager* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[UNetWorkManager] GetOnlineGamePlayerNum But _this is NULL."));
		return 0;
	}

	return _this->GetOnlineGamePlayerNum();
}

void UnrealAPI_NetWork::RegisterAPI() 
{
	mono_add_internal_call("UnrealEngine.NetWorkManager::_StartOnlineGame",
		reinterpret_cast<void*>(UnrealEngine_NetWorkManager_StartOnlineGame));
	mono_add_internal_call("UnrealEngine.NetWorkManager::_FindOnlineGame",
		reinterpret_cast<void*>(UnrealEngine_NetWorkManager_FindOnlineGame));
	mono_add_internal_call("UnrealEngine.NetWorkManager::_JoinOnlineGame",
		reinterpret_cast<void*>(UnrealEngine_NetWorkManager_JoinOnlineGame));
	mono_add_internal_call("UnrealEngine.NetWorkManager::_DestroySessionAndLeaveGame",
		reinterpret_cast<void*>(UnrealEngine_NetWorkManager_DestroySessionAndLeaveGame));
	mono_add_internal_call("UnrealEngine.NetWorkManager::_GetOnlineGamePlayerNum",
		reinterpret_cast<void*>(UnrealEngine_NetWorkManager_GetOnlineGamePlayerNum));

}