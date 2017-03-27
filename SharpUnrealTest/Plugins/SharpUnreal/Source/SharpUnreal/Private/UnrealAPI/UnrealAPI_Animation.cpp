#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "UnrealAPI_Animation.h"
#include "MonoComponent.h"
#include "LevelSequenceActor.h"

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


static void UnrealEngine_Sequencer_Play(ULevelSequencePlayer* _this) 
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] Play But _this is NULL."));
		return ;
	}

	_this->Play();
}

static void UnrealEngine_Sequencer_Pause(ULevelSequencePlayer* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] Pause But _this is NULL."));
		return;
	}

	_this->Pause();
}

static void UnrealEngine_Sequencer_Stop(ULevelSequencePlayer* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] Stop But _this is NULL."));
		return;
	}

	_this->Stop();
}

static float UnrealEngine_Sequencer_GetLength(ULevelSequencePlayer* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] GetLength But _this is NULL."));
		return 0.0f;
	}

	return _this->GetLength();
}

static float UnrealEngine_Sequencer_GetCurrent(ULevelSequencePlayer* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] GetCurrent But _this is NULL."));
		return 0.0f;
	}
	return _this->GetPlaybackPosition();
}

static void UnrealEngine_Sequencer_SetCurrent(ULevelSequencePlayer* _this, float current)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] SetCurrent But _this is NULL."));
		return ;
	}
	_this->SetPlaybackPosition(current);
}

static float UnrealEngine_Sequencer_GetPlayRate(ULevelSequencePlayer* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] GetPlayRate But _this is NULL."));
		return 0.0f;
	}
	return _this->GetPlayRate();
}

static void UnrealEngine_Sequencer_SetPlayRate(ULevelSequencePlayer* _this, float current)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] SetPlayRate But _this is NULL."));
		return ;
	}
	_this->SetPlayRate(current);
}

static float UnrealEngine_Sequencer_GetStartTime(ULevelSequencePlayer* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] GetStartTime But _this is NULL."));
		return 0.0f;
	}
	return _this->GetPlaybackStart();
}

static float UnrealEngine_Sequencer_GetEndTime(ULevelSequencePlayer* _this)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] GetEndTime But _this is NULL."));
		return 0.0f;
	}
	return _this->GetPlaybackEnd();
}

static void UnrealEngine_Sequencer_SetPlaybackRange(ULevelSequencePlayer* _this, float startTime, float endTime)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] SetPlaybackRange But _this is NULL."));
		return ;
	}
	_this->SetPlaybackRange(startTime, endTime);
}

static void UnrealEngine_Sequencer_RegSequencerPlay(ULevelSequencePlayer* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] RegSequencerPlay But _this is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnSequencerPlay")));
	_this->OnPlay.AddUnique(del);
}

static void UnrealEngine_Sequencer_RegSequencerPause(ULevelSequencePlayer* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] RegSequencerPause But _this is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnSequencerPause")));
	_this->OnPlay.AddUnique(del);
}

static void UnrealEngine_Sequencer_RegSequencerStop(ULevelSequencePlayer* _this, UMonoComponent* listener)
{
	if (_this == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[Sequencer] RegSequencerStop But _this is NULL."));
		return;
	}
	FScriptDelegate del;
	del.BindUFunction(listener, FName(TEXT("OnSequencerStop")));
	_this->OnPlay.AddUnique(del);
}

void UnrealAPI_Animation::RegisterAPI()
{
	mono_add_internal_call("UnrealEngine.Sequencer::_Sequencer_Play",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_Play));
	mono_add_internal_call("UnrealEngine.Sequencer::_Pause",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_Pause));
	mono_add_internal_call("UnrealEngine.Sequencer::_Stop",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_Stop));
	mono_add_internal_call("UnrealEngine.Sequencer::_GetLength",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_GetLength));
	mono_add_internal_call("UnrealEngine.Sequencer::_GetCurrent",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_GetCurrent));
	mono_add_internal_call("UnrealEngine.Sequencer::_SetCurrent",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_SetCurrent));
	mono_add_internal_call("UnrealEngine.Sequencer::_GetPlayRate",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_GetPlayRate));
	mono_add_internal_call("UnrealEngine.Sequencer::_SetPlayRate",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_SetPlayRate));
	mono_add_internal_call("UnrealEngine.Sequencer::_GetStartTime",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_GetStartTime));
	mono_add_internal_call("UnrealEngine.Sequencer::_GetEndTime",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_GetEndTime));
	mono_add_internal_call("UnrealEngine.Sequencer::_SetPlaybackRange",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_SetPlaybackRange));
	mono_add_internal_call("UnrealEngine.Sequencer::_RegSequencerPlay",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_RegSequencerPlay));
	mono_add_internal_call("UnrealEngine.Sequencer::_RegSequencerPause",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_RegSequencerPause));
	mono_add_internal_call("UnrealEngine.Sequencer::_RegSequencerStop",
		reinterpret_cast<void*>(UnrealEngine_Sequencer_RegSequencerStop));

}
