#include "SharpUnrealPrivatePCH.h"
#include "UnrealAPI_Audio.h"
#include "MonoComponent.h"

#include "Components/AudioComponent.h"

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

static float UnrealAPI_AudioComponent_GetVolumeMultiplier(UAudioComponent* _this) 
{
	return _this->VolumeMultiplier;
}

static void UnrealAPI_AudioComponent_SetVolumeMultiplier(UAudioComponent* _this, float volume) 
{
	_this->SetVolumeMultiplier(volume);
}

static float UnrealAPI_AudioComponent_GetPriority(UAudioComponent* _this) 
{
	return _this->Priority;
}

static void UnrealAPI_AudioComponent_SetPriority(UAudioComponent* _this, float priority) 
{
	_this->Priority = priority;
}

static float UnrealAPI_AudioComponent_GetPitchMultiplier(UAudioComponent* _this) 
{
	return _this->PitchMultiplier;
}

static void UnrealAPI_AudioComponent_SetPitchMultiplier(UAudioComponent* _this, float multiplier) 
{
	_this->SetPitchMultiplier(multiplier);
}

static bool UnrealAPI_AudioComponent_GetIsPlaying(UAudioComponent* _this) 
{
	return _this->IsPlaying();
}

static void UnrealAPI_AudioComponent_Play(UAudioComponent* _this, float StartTime) 
{
	_this->Play(StartTime);
}

static void UnrealAPI_AudioComponent_Stop(UAudioComponent* _this) 
{
	_this->Stop();
}

static void UnrealAPI_AudioComponent_SetPaused(UAudioComponent* _this, bool bPause) 
{
	_this->SetPaused(bPause);
}

static void UnrealAPI_AudioComponent_RegAudioFinished(UAudioComponent* _this,UMonoComponent* listener) 
{
	_this->OnAudioFinishedNative.AddLambda([=] (const UAudioComponent* audio)-> void {
		listener->OnAudioFinished(audio);
	});
}

static void UnrealAPI_AudioComponent_RegAudioPlaybackPercent(UAudioComponent* _this, UMonoComponent* listener)
{
	_this->OnAudioPlaybackPercentNative.AddLambda(
		[=](const class UAudioComponent* audio, const class USoundWave* sound, const float percent)-> void {
			listener->OnAudioPlaybackPercent(audio,sound,percent);
	});
}


void UnrealAPI_Audio::RegisterAPI()
{
	mono_add_internal_call("UnrealEngine.AudioComponent::_GetVolumeMultiplier",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_GetVolumeMultiplier));
	mono_add_internal_call("UnrealEngine.AudioComponent::_SetVolumeMultiplier",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_SetVolumeMultiplier));
	mono_add_internal_call("UnrealEngine.AudioComponent::_GetPriority",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_GetPriority));
	mono_add_internal_call("UnrealEngine.AudioComponent::_SetPriority",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_SetPriority));
	mono_add_internal_call("UnrealEngine.AudioComponent::_GetPitchMultiplier",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_GetPitchMultiplier));
	mono_add_internal_call("UnrealEngine.AudioComponent::_SetPitchMultiplier",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_SetPitchMultiplier));
	mono_add_internal_call("UnrealEngine.AudioComponent::_GetIsPlaying",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_GetIsPlaying));
	mono_add_internal_call("UnrealEngine.AudioComponent::_Play",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_Play));
	mono_add_internal_call("UnrealEngine.AudioComponent::_Stop",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_Stop));
	mono_add_internal_call("UnrealEngine.AudioComponent::_SetPaused",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_SetPaused));
	mono_add_internal_call("UnrealEngine.AudioComponent::_RegAudioFinished",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_RegAudioFinished));
	mono_add_internal_call("UnrealEngine.AudioComponent::_RegAudioPlaybackPercent",
		reinterpret_cast<void*>(UnrealAPI_AudioComponent_RegAudioPlaybackPercent));

}