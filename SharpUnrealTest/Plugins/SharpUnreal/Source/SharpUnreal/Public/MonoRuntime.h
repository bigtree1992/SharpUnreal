#pragma once

struct _MonoObject;
struct _MonoMethod;
struct _MonoClass;
class UMonoComponent;

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
	int ReloadAssembly();
	//监听编辑器下开始运行的按键
	void OnBeginPIE(bool bIsSimulating);

	TArray<FString> GetAllMonoComponent();
	
	_MonoObject* CreateObject(const char * name);
	_MonoObject* CreateObjectFromEngine(const char * name);
	uint32_t RetainObject(_MonoObject* object);
	void FreeObject(uint32_t handle);

	void SetNativeHandler(_MonoObject* object, void* handler);

	void ResgisterComponent( UMonoComponent* const component);
	void UnResgisterComponent( UMonoComponent* const component);

	_MonoMethod* FindMethod(_MonoClass* klass,const char* name, int paramCount);
	_MonoMethod* FindMethodByObj(_MonoObject* object, const char* name, int paramCount);
	_MonoObject* InvokeMethod(_MonoMethod* method, void *obj, void **params);

	_MonoClass* FindClassByName(const char* name);

	MonoRuntime();

private:
	void CopyToTarget(const FString& source, const FString &target);
private:
	struct _MonoDomain*		m_RootDomain;
	struct _MonoDomain*		m_ChildDomain;
	struct _MonoAssembly*	m_MainAssembly;
	struct _MonoImage*		m_MainImage;
	
	struct _MonoAssembly*	m_EngineAssembly;
	struct _MonoImage*		m_EngineImage;

	TArray<FString> m_ComponentNames;
	TArray<UMonoComponent*> m_MonoComponents;
};
