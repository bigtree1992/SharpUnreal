// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
