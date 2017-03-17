#include "SharpUnrealPrivatePCH.h"
#include "MonoComponent.h"
#include "MonoRuntime.h"

UMonoComponent::UMonoComponent()
{
	bWantsInitializeComponent = true;	
	PrimaryComponentTick.bCanEverTick = false;
	m_MonoComponent = NULL;
}

UMonoComponent::~UMonoComponent()
{}

void UMonoComponent::InitMonoCallback() 
{
	ActorComponent_OnRegister = MonoRuntime::Instance()->FindMethodByObj(m_MonoComponent, "OnRegister", -1);
	if (ActorComponent_OnRegister == NULL)
	{
		GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] ActorComponent_OnRegister == NULL "));
	}
	ActorComponent_OnUnregister = MonoRuntime::Instance()->FindMethodByObj(m_MonoComponent, "OnUnregister", -1);
	if (ActorComponent_OnUnregister == NULL)
	{
		GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] ActorComponent_OnUnregister == NULL "));
	}
	ActorComponent_Initialize = MonoRuntime::Instance()->FindMethodByObj(m_MonoComponent, "Initialize", -1);
	if (ActorComponent_Initialize == NULL)
	{
		GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] ActorComponent_Initialize == NULL "));
	}
	ActorComponent_Uninitialize = MonoRuntime::Instance()->FindMethodByObj(m_MonoComponent, "Uninitialize", -1);
	if (ActorComponent_Uninitialize == NULL)
	{
		GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] ActorComponent_Uninitialize == NULL "));
	}
	ActorComponent_BeginPlay = MonoRuntime::Instance()->FindMethodByObj(m_MonoComponent, "BeginPlay", -1);
	if (ActorComponent_BeginPlay == NULL)
	{
		GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] ActorComponent_BeginPlay == NULL "));
	}
	ActorComponent_EndPlay = MonoRuntime::Instance()->FindMethodByObj(m_MonoComponent, "EndPlay", -1);
	if (ActorComponent_EndPlay == NULL)
	{
		GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] ActorComponent_EndPlay == NULL "));
	}
	ActorComponent_Tick = MonoRuntime::Instance()->FindMethodByObj(m_MonoComponent, "Tick", 1);
	if (ActorComponent_Tick == NULL)
	{
		GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] ActorComponent_Tick == NULL "));
	}
}

void UMonoComponent::OnRegister() 
{
	Super::OnRegister();
	
	if (m_MonoComponent != NULL) 	
	{
		MonoRuntime::Instance()->InvokeMethod(
			ActorComponent_OnRegister, m_MonoComponent, NULL);
	}
}

void UMonoComponent::OnUnregister() 
{
	Super::OnUnregister();
	
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			ActorComponent_OnUnregister, m_MonoComponent, NULL);
	}
}

//初始化脚本的时候根据名字创建Mono对象
void UMonoComponent::InitializeComponent() 
{
	Super::InitializeComponent();
		
	m_MonoComponent = MonoRuntime::Instance()->CreateObject(TCHAR_TO_UTF8(*ComponentName));
	if (m_MonoComponent != NULL)
	{
		InitMonoCallback();
		m_Handle = MonoRuntime::Instance()->RetainObject(m_MonoComponent);

		MonoRuntime::Instance()->InvokeMethod(
			ActorComponent_Initialize, m_MonoComponent, NULL);
	}
	else {
		GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] Initialize Failed : %s."), *ComponentName);
	}
}
//销毁Mono对象
void UMonoComponent::UninitializeComponent() 
{
	Super::UninitializeComponent();
	
	//销毁Mono对象
	if (m_MonoComponent != NULL) 
	{
		MonoRuntime::Instance()->InvokeMethod(
			ActorComponent_Uninitialize, m_MonoComponent, NULL);

		MonoRuntime::Instance()->FreeObject(m_Handle);
		m_MonoComponent = NULL;
	}
}

void UMonoComponent::BeginPlay()
{
	Super::BeginPlay();
	GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] BeginPlay %s "), *ComponentName);
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			ActorComponent_BeginPlay, m_MonoComponent, NULL);
	}
}

void UMonoComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	Super::EndPlay(EndPlayReason);
	GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] EndPlay %s "), *ComponentName);
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			ActorComponent_EndPlay, m_MonoComponent, NULL);
	}
}

void UMonoComponent::TickComponent( 
	float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (m_MonoComponent != NULL)
	{
		void *args[1];
		args[0] = &DeltaTime;

		MonoRuntime::Instance()->InvokeMethod(
			ActorComponent_Tick, m_MonoComponent, args);
	}
}

