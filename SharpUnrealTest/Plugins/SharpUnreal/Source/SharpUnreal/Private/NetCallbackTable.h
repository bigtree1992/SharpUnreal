#pragma once

struct _MonoClass;
struct _MonoImage;
struct _MonoMethod;

/**
* 保存了MonoClass跟UClass的对应关系
*/
class NetCallbackTable
{
public:
	static bool CreateTable(_MonoImage* engine,_MonoImage* main);
	
	static void DestroyTable();
	
	static _MonoMethod* GetMethod(_MonoClass* mono_class,int id);

};
