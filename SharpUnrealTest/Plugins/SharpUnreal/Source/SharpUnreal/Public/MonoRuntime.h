#pragma once

#include "mono/metadata/metadata.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/debug-helpers.h>

/**
* 管理Mono虚拟机的创建，C# dll加载
*/
class SHARPUNREAL_API MonoRuntime
{
public:
	//创建一个全局Mono运行时
	static int CreateInstance();
	//销毁全局Mono运行时
	static void DestoryInstance();
	//获取Mono运行时的单例
	static MonoRuntime* Instance();
	//重新加载主逻辑脚本
	int ReloadMainAssembly();

	MonoRuntime();
private:
	void CopyToTarget(FString &target);
private:
	MonoDomain*		m_RootDomain;
	MonoDomain*		m_ChildDomain;
	MonoAssembly*	m_MainAssembly;
	MonoImage*		m_MainImage;
};
