#include "SharpUnrealPrivatePCH.h"
#include "Delegate.h"
#include "MonoComponent.h"
#include "MonoRuntime.h"
#include "MonoCallbackTable.h"
#include "mono/metadata/object.h"

UMonoComponent::UMonoComponent()
{
	bWantsInitializeComponent = true;	
	PrimaryComponentTick.bCanEverTick = false;
	m_MonoComponent = NULL;
}

UMonoComponent::~UMonoComponent()
{}

void UMonoComponent::OnRegister() 
{
	Super::OnRegister();
	
	if (m_MonoComponent != NULL) 	
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnRegister, m_MonoComponent, NULL);
	}
}

void UMonoComponent::OnUnregister() 
{
	Super::OnUnregister();
	
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnUnregister, m_MonoComponent, NULL);
	}
}

//初始化脚本的时候根据名字创建Mono对象
void UMonoComponent::InitializeComponent() 
{
	Super::InitializeComponent();
	
	m_MonoComponent = MonoRuntime::Instance()->CreateObject(TCHAR_TO_UTF8(*ComponentName));
	if (m_MonoComponent != NULL)
	{
		m_Handle = MonoRuntime::Instance()->RetainObject(m_MonoComponent);

		m_Callback = MonoCallbackTable::GetCallbackByObject(m_MonoComponent);
		if (m_Callback == NULL)
		{
			m_Callback = new MonoCallback();
			GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] Initialize Failed Callback NUL: %s."), *ComponentName);
			return;
		}
		
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->Initialize, m_MonoComponent, NULL);
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
			m_Callback->Uninitialize, m_MonoComponent, NULL);

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
		m_Callback->BeginPlay, m_MonoComponent, NULL);
	}
}

void UMonoComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	Super::EndPlay(EndPlayReason);
	GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] EndPlay %s "), *ComponentName);
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->EndPlay, m_MonoComponent, NULL);
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
			m_Callback->Tick, m_MonoComponent, args);
	}
}

void UMonoComponent::SendEventToMono(const FString& Event) 
{
	if (m_MonoComponent != NULL)
	{
		MonoString* e = mono_string_from_utf16((mono_unichar2*)*Event);
		void *args[1];
		args[0] = e;
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnEvent, m_MonoComponent, args);
	}	
}

