// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreUObject.h"

struct _MonoMethod;
struct _MonoClass;
struct _MonoObject;

/*
* 保存了一个MonoCall的回调引用
*/
struct MonoCallback 
{
	_MonoMethod* OnRegister;
	_MonoMethod* OnUnregister;
	_MonoMethod* Initialize;
	_MonoMethod* Uninitialize;
	_MonoMethod* BeginPlay;
	_MonoMethod* EndPlay;
	_MonoMethod* Tick;
	_MonoMethod* OnEvent;
	_MonoMethod* OnEventWithInt;
	_MonoMethod* OnEventWithFloat;
	_MonoMethod* OnEventWithString;
	_MonoMethod* OnEventWithVector;
	_MonoMethod* OnIntEvent;
	_MonoMethod* OnIntEventWithInt;
	_MonoMethod* OnIntEventWithFloat;
	_MonoMethod* OnIntEventWithString;
	_MonoMethod* OnIntEventWithVector;
	
	_MonoMethod* OnAppDeactivate;
	_MonoMethod* OnAppHasReactivated;	
	_MonoMethod* OnAppWillEnterBackground;
	_MonoMethod* OnAppHasEnteredForeground;	
	_MonoMethod* OnAppWillTerminate;

	
	_MonoMethod* OnComponentHit;
	_MonoMethod* OnComponentBeginOverlap;
	_MonoMethod* OnComponentEndOverlap;
	_MonoMethod* OnComponentWake;
	_MonoMethod* OnComponentSleep;
	_MonoMethod* OnParticleSpawn;
	_MonoMethod* OnParticleBurst;
	_MonoMethod* OnParticleDeath;
	_MonoMethod* OnParticleCollide;
	_MonoMethod* OnSystemFinished;
	_MonoMethod* OnAudioFinished;
	_MonoMethod* OnAudioPlaybackPercent;
	_MonoMethod* OnSequencerPlay;
	_MonoMethod* OnSequencerPause;
	_MonoMethod* OnSequencerStop;

	_MonoMethod* OnStartOnlieGameComplete;
	_MonoMethod* OnFindOnlieGameComplete;
	_MonoMethod* OnJoinOnlieGameComplete;
	_MonoMethod* OnDestroyOnlieGameComplete;

	void Clear() 
	{
		OnRegister = NULL;
		OnUnregister = NULL;
		Initialize = NULL;
		Uninitialize = NULL;
		BeginPlay = NULL;
		EndPlay = NULL;
		Tick = NULL;
		OnEvent = NULL;
		OnEventWithInt = NULL;
		OnEventWithString = NULL;
		OnEventWithVector = NULL;
		OnEventWithFloat = NULL;
		OnIntEvent = NULL;
		OnIntEventWithInt = NULL;
		OnIntEventWithFloat = NULL;
		OnIntEventWithString = NULL;
		OnIntEventWithVector = NULL;

		OnAppDeactivate = NULL;
		OnAppHasReactivated = NULL;
		OnAppWillEnterBackground = NULL;
		OnAppHasEnteredForeground = NULL;
		OnAppWillTerminate = NULL;

		OnComponentHit = NULL;
		OnComponentBeginOverlap = NULL;
		OnComponentEndOverlap = NULL;
		OnComponentWake = NULL;
		OnComponentSleep = NULL;
		OnParticleSpawn = NULL;
		OnParticleBurst = NULL;
		OnParticleDeath = NULL;
		OnParticleCollide = NULL;
		OnSystemFinished = NULL;
		OnAudioFinished = NULL;
		OnAudioPlaybackPercent = NULL;
		OnSequencerPlay = NULL;
		OnSequencerPause = NULL;
		OnSequencerStop = NULL;

		OnStartOnlieGameComplete = NULL;
		OnFindOnlieGameComplete = NULL;
		OnJoinOnlieGameComplete = NULL;
		OnDestroyOnlieGameComplete = NULL;
	}
};

/**
* 保存了MonoClass跟Callback的对应关系
*/
class MonoCallbackTable
{
public:
	//初始化一个类的回调函数
	static void CreateClassCallback(_MonoClass* klass);
	//销毁所有的回调
	static void DestroyAllCallback();
	//根据MonoCalss获取对应的Callback
	static MonoCallback* GetCallbackByClass(_MonoClass* klass);
	//根据MonoObject获取对应的Callback
	static MonoCallback* GetCallbackByObject(_MonoObject* obj);
};
