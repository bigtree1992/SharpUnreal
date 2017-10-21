#include "SharpUnrealPrivatePCH.h"
#include "Delegate.h"
#include "MonoComponent.h"
#include "MonoRuntime.h"
#include "MonoCallbackTable.h"
#include "NetCallbackTable.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"

#include "mono/metadata/object.h"

UMonoComponent::UMonoComponent()
{
	bWantsInitializeComponent = true;	
	PrimaryComponentTick.bCanEverTick = false;
	m_MonoComponent = NULL;

	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UMonoComponent::OnCreateSessionComplete);
	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UMonoComponent::OnDestroySessionComplete);
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UMonoComponent::OnFindSessionsComplete);
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UMonoComponent::OnJoinSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UMonoComponent::OnStartOnlineGameComplete);
	//GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] ctor: %s"),*GetName());
}

UMonoComponent::~UMonoComponent()
{
	//GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] destroy: %s"), *GetName());
}

_MonoObject* UMonoComponent::GetMonoObject() 
{
	return this->m_MonoComponent;
}

void UMonoComponent::OnRegister() 
{
	Super::OnRegister();
	//GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] OnRegister: %s"), *GetName());
	if (Reload())
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnRegister, m_MonoComponent, NULL);
#if WITH_EDITOR
		MonoRuntime::Instance()->ResgisterComponent(this);
#endif // WITH_EDITOR

	}
}

void UMonoComponent::OnUnregister() 
{
	Super::OnUnregister();
	//GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] OnUnregister: %s"), *GetName());
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnUnregister, m_MonoComponent, NULL);

		//MonoRuntime::Instance()->ClearNativeHandler(m_MonoComponent);
#if WITH_EDITOR
		MonoRuntime::Instance()->UnResgisterComponent(this);
#endif // WITH_EDITOR
		MonoRuntime::Instance()->FreeObject(m_Handle);
		m_MonoComponent = NULL;
	}
}

bool UMonoComponent::Reload()
{
	if (m_MonoComponent != NULL) 
	{
		MonoRuntime::Instance()->FreeObject(m_Handle);
		m_MonoComponent = NULL;
	}

	if (ComponentName.IsEmpty()) 
	{
		return false;
	}

	m_MonoComponent = MonoRuntime::Instance()->CreateObject(TCHAR_TO_UTF8(*ComponentName));

	if (m_MonoComponent == NULL) {
		m_MonoComponent = MonoRuntime::Instance()->CreateObjectFromEngine(TCHAR_TO_UTF8(*ComponentName));
	}

	if (m_MonoComponent != NULL)
	{
		m_Handle = MonoRuntime::Instance()->RetainObject(m_MonoComponent);

		m_Callback = MonoCallbackTable::GetCallbackByObject(m_MonoComponent);
		if (m_Callback == NULL)
		{
			m_Callback = new MonoCallback();
			GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] Initialize Failed Callback NUL: %s."), *ComponentName);
			return false;
		}

		//设置Mono对象的本地对象为自己
		void * _this = this;
		MonoRuntime::Instance()->SetNativeHandler(m_MonoComponent, &_this);
	}
	else {
		GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] Initialize Failed : %s."), *ComponentName);
		return false;
	}

	return true;
}

//初始化脚本的时候根据名字创建Mono对象
void UMonoComponent::InitializeComponent() 
{
	Super::InitializeComponent();
	//GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] InitializeComponent: %s"), *GetName());
	
	if (m_MonoComponent != NULL)
	{
		//调用Mono初始化方法
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->Initialize, m_MonoComponent, NULL);
	}	
}
//销毁Mono对象
void UMonoComponent::UninitializeComponent() 
{
	Super::UninitializeComponent();
	//GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] UninitializeComponent:%s"), *GetName());
	//销毁Mono对象
	if (m_MonoComponent != NULL) 
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->Uninitialize, m_MonoComponent, NULL);
	}
}

void UMonoComponent::BeginPlay()
{
	Super::BeginPlay();
	//GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] BeginPlay %s "), *ComponentName);
	
	if (m_MonoComponent != NULL)
	{		
		MonoRuntime::Instance()->InvokeMethod(
		m_Callback->BeginPlay, m_MonoComponent, NULL);
	}
}

void UMonoComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	Super::EndPlay(EndPlayReason);
	//GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] EndPlay %s "), *ComponentName);
	if (m_MonoComponent != NULL)
	{
		void *args[1];
		auto reason = EndPlayReason;
		args[0] = &reason;
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->EndPlay, m_MonoComponent, args);
	}
}

void UMonoComponent::BeginDestroy() 
{
	if (m_MonoComponent != NULL)
	{

	}
	
	Super::BeginDestroy();		
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

void UMonoComponent::SendEventToMonoWithInt(const FString& Event,int data)
{
	if (m_MonoComponent != NULL)
	{
		MonoString* e = mono_string_from_utf16((mono_unichar2*)*Event);
		void *args[2];
		args[0] = e;
		args[1] = &data;
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnEventWithInt, m_MonoComponent, args);
	}
}

void UMonoComponent::SendEventToMonoWithFloat(const FString& Event, float data)
{
	if (m_MonoComponent != NULL)
	{
		MonoString* e = mono_string_from_utf16((mono_unichar2*)*Event);
		void *args[2];
		args[0] = e;
		args[1] = &data;
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnEventWithFloat, m_MonoComponent, args);
	}
}

void UMonoComponent::SendEventToMonoWithString(const FString& Event,const FString& data)
{
	if (m_MonoComponent != NULL)
	{
		MonoString* e = mono_string_from_utf16((mono_unichar2*)*Event);
		MonoString* s = mono_string_from_utf16((mono_unichar2*)*data);
		void *args[2];
		args[0] = e;
		args[1] = s;
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnEventWithString, m_MonoComponent, args);
	}
}

void UMonoComponent::SendEventToMonoWithVector(const FString& Event, FVector data)
{
	if (m_MonoComponent != NULL)
	{
		MonoString* e = mono_string_from_utf16((mono_unichar2*)*Event);
		void *args[2];
		args[0] = e;
		args[1] = &data;
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnEventWithVector, m_MonoComponent, args);
	}
}

void UMonoComponent::OnAppDeactivate()
{
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnAppDeactivate, m_MonoComponent, NULL);
	}
}

void UMonoComponent::OnAppHasReactivated() 
{
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnAppHasReactivated, m_MonoComponent, NULL);
	}
}

void UMonoComponent::OnAppWillEnterBackground() 
{
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnAppWillEnterBackground, m_MonoComponent, NULL);
	}
}

void UMonoComponent::OnAppHasEnteredForeground() 
{
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnAppHasEnteredForeground, m_MonoComponent, NULL);
	}

}

void UMonoComponent::OnAppWillTerminate() 
{
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnAppWillTerminate, m_MonoComponent, NULL);
	}
}

void UMonoComponent::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	if (m_MonoComponent != NULL)
	{
		//参数1 自己的组件
		MonoObject* self = MonoRuntime::Instance()->CreateObjectFromEngine("PrimitiveComponent");
		MonoRuntime::Instance()->SetNativeHandler(self, &HitComponent);
		if (self == NULL)
		{
			GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] Create PrimitiveComponent Failed. %s "), *ComponentName);
			return;
		}

		//参数2 碰撞组件
		MonoObject* other = MonoRuntime::Instance()->CreateObjectFromEngine("PrimitiveComponent");
		MonoRuntime::Instance()->SetNativeHandler(other, &OtherComp);
		if (other == NULL)
		{
			GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] Create PrimitiveComponent Failed. %s "), *ComponentName);
			return;
		}
		//参数3 作用点
		FVector impact = Hit.ImpactPoint;

		void *args[3];
		args[0] = self;
		args[1] = other;
		args[2] = &impact;

		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnComponentHit, m_MonoComponent, args);
	}
}

void UMonoComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (m_MonoComponent != NULL)
	{
		//参数1 自己的组件
		MonoObject* self = MonoRuntime::Instance()->CreateObjectFromEngine("PrimitiveComponent");
		MonoRuntime::Instance()->SetNativeHandler(self, &OverlappedComponent);
		if (self == NULL)
		{
			GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] Create PrimitiveComponent Failed. %s "), *ComponentName);
			return;
		}
		//参数2 触发组件
		MonoObject* other = MonoRuntime::Instance()->CreateObjectFromEngine("PrimitiveComponent");
		MonoRuntime::Instance()->SetNativeHandler(other, &OtherComp);
		if (other == NULL)
		{
			GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] Create PrimitiveComponent Failed. %s "), *ComponentName);
			return;
		}
		//参数2 作用点
		FVector impact = SweepResult.ImpactPoint;

		void *args[3];
		args[0] = self;
		args[1] = other;
		args[2] = &impact;

		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnComponentBeginOverlap, m_MonoComponent, args);
	}
}

void UMonoComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (m_MonoComponent != NULL)
	{
		//参数1 自己的组件
		MonoObject* self = MonoRuntime::Instance()->CreateObjectFromEngine("PrimitiveComponent");
		MonoRuntime::Instance()->SetNativeHandler(self, &OverlappedComponent);
		if (self == NULL)
		{
			GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] Create PrimitiveComponent Failed. %s "), *ComponentName);
			return;
		}
		//参数2 触发组件
		MonoObject* other = MonoRuntime::Instance()->CreateObjectFromEngine("PrimitiveComponent");
		MonoRuntime::Instance()->SetNativeHandler(other, &OtherComp);
		if (other == NULL)
		{
			GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] Create PrimitiveComponent Failed. %s "), *ComponentName);
			return;
		}

		void *args[2];
		args[0] = self;
		args[1] = other;

		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnComponentEndOverlap, m_MonoComponent, args);
	}
}

void UMonoComponent::OnComponentWake(UPrimitiveComponent* WakingComponent, FName BoneName) 
{
	if (m_MonoComponent != NULL)
	{
		//参数1 自己的组件
		MonoObject* self = MonoRuntime::Instance()->CreateObjectFromEngine("PrimitiveComponent");
		MonoRuntime::Instance()->SetNativeHandler(self, &WakingComponent);
		if (self == NULL)
		{
			GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] Create PrimitiveComponent Failed. %s "), *ComponentName);
			return;
		}

		MonoString* name = mono_string_from_utf16((mono_unichar2*)BoneName.GetPlainWIDEString());
		void *args[2];
		args[0] = self;
		args[1] = name;

		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnComponentWake, m_MonoComponent, args);
	}
}

void UMonoComponent::OnComponentSleep(UPrimitiveComponent* SleepingComponent, FName BoneName) 
{
	if (m_MonoComponent != NULL)
	{
		//参数1 自己的组件
		MonoObject* self = MonoRuntime::Instance()->CreateObjectFromEngine("PrimitiveComponent");
		MonoRuntime::Instance()->SetNativeHandler(self, &SleepingComponent);
		if (self == NULL)
		{
			GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] Create PrimitiveComponent Failed. %s "), *ComponentName);
			return;
		}

		MonoString* name = mono_string_from_utf16((mono_unichar2*)BoneName.GetPlainWIDEString());
		void *args[2];
		args[1] = self;
		args[1] = name;

		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnComponentSleep, m_MonoComponent, args);
	}
}

void UMonoComponent::OnParticleSpawn(FName EventName, float EmitterTime, FVector Location, FVector Velocity)
{
	if (m_MonoComponent != NULL)
	{
		MonoString* name = mono_string_from_utf16((mono_unichar2*)EventName.GetPlainWIDEString());
		void *args[1];
		args[0] = name;

		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnParticleSpawn, m_MonoComponent, args);
	}
}

void UMonoComponent::OnParticleBurst(FName EventName, float EmitterTime, int32 ParticleCount)
{
	if (m_MonoComponent != NULL)
	{
		MonoString* name = mono_string_from_utf16((mono_unichar2*)EventName.GetPlainWIDEString());
		void *args[1];
		args[0] = name;

		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnParticleBurst, m_MonoComponent, args);
	}
}

void UMonoComponent::OnParticleDeath(FName EventName, float EmitterTime, int32 ParticleTime,
	FVector Location, FVector Velocity, FVector Direction) 
{
	if (m_MonoComponent != NULL)
	{
		MonoString* name = mono_string_from_utf16((mono_unichar2*)EventName.GetPlainWIDEString());
		void *args[1];
		args[0] = name;

		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnParticleDeath, m_MonoComponent, args);
	}
}

void UMonoComponent::OnParticleCollide(FName EventName, float EmitterTime, int32 ParticleTime,
	FVector Location, FVector Velocity, FVector Direction, 
	FVector Normal, FName BoneName, UPhysicalMaterial* PhysMat) 
{
	if (m_MonoComponent != NULL)
	{
		MonoString* name = mono_string_from_utf16((mono_unichar2*)EventName.GetPlainWIDEString());
		void *args[1];
		args[0] = name;

		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnParticleCollide, m_MonoComponent, args);
	}
}

void UMonoComponent::OnSystemFinished(UParticleSystemComponent* PSystem)
{
	if (m_MonoComponent != NULL)
	{
		MonoString* name = mono_string_from_utf16((mono_unichar2*)*PSystem->GetName());
		void *args[1];
		args[0] = name;
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnSystemFinished, m_MonoComponent, args);
	}
}

void UMonoComponent::OnAudioFinished(const UAudioComponent* Audio)
{
	if (m_MonoComponent != NULL)
	{
		MonoString* name = mono_string_from_utf16((mono_unichar2*)*Audio->GetName());
		void *args[1];
		args[0] = name;
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnAudioFinished, m_MonoComponent, args);
	}
}

void UMonoComponent::OnAudioPlaybackPercent(const UAudioComponent* Audio,const USoundWave* PlayingSoundWave, const float PlaybackPercen)
{
	if (m_MonoComponent != NULL)
	{
		MonoString* name = mono_string_from_utf16((mono_unichar2*)*Audio->GetName());
		float persent = PlaybackPercen;
		void *args[2];
		args[0] = name;
		args[1] = &persent;
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnAudioPlaybackPercent, m_MonoComponent, args);
	}
}

void UMonoComponent::OnSequencerPlay() 
{
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnSequencerPlay, m_MonoComponent, NULL);
	}
}

void UMonoComponent::OnSequencerPause() 
{
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnSequencerPause, m_MonoComponent, NULL);
	}
}

void UMonoComponent::OnSequencerStop() 
{
	if (m_MonoComponent != NULL)
	{
		MonoRuntime::Instance()->InvokeMethod(
			m_Callback->OnSequencerStop, m_MonoComponent, NULL);
	}
}

bool UMonoComponent::CallOnServer_Validate(int id)
{
	return true;
}

void UMonoComponent::CallOnServer_Implementation(int id) 
{
	if (m_MonoComponent == NULL)
	{
		return ;
	}

	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, NULL);
}

void UMonoComponent::CallOnClient_Implementation(int id)
{
	if (m_MonoComponent == NULL)
	{
		return ;
	}
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, NULL);
}

void UMonoComponent::CallOnAll_Implementation(int id)
{
	if (m_MonoComponent == NULL)
	{
		return ;
	}

	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, NULL);
}

bool UMonoComponent::CallOnServerWithFloat_Validate(int id, float data)
{
	return true;
}

void UMonoComponent::CallOnServerWithFloat_Implementation(int id, float data)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &data;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnClientWithFloat_Implementation(int id, float data)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &data;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnAllWithFloat_Implementation(int id, float data)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &data;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

bool UMonoComponent::CallOnServerWithVector_Validate(int id, FVector data)
{
	return true;
}

void UMonoComponent::CallOnServerWithVector_Implementation(int id, FVector data)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &data;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnClientWithVector_Implementation(int id, FVector data)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &data;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnAllWithVector_Implementation(int id, FVector data)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &data;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

bool UMonoComponent::CallOnServerWithRotator_Validate(int id, FRotator data)
{
	return true;
}

void UMonoComponent::CallOnServerWithRotator_Implementation(int id, FRotator data)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &data;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnClientWithRotator_Implementation(int id, FRotator data)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &data;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnAllWithRotator_Implementation(int id, FRotator data)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &data;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

bool UMonoComponent::CallOnServerWithRR_Validate(int id, FRotator data, FRotator data2)
{
	return true;
}

void UMonoComponent::CallOnServerWithRR_Implementation(int id, FRotator data, FRotator data2)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[2];
	args[0] = &data;
	args[1] = &data2;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnClientWithRR_Implementation(int id, FRotator data, FRotator data2)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[2];
	args[0] = &data;
	args[1] = &data2;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnAllWithRR_Implementation(int id, FRotator data, FRotator data2)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[2];
	args[0] = &data;
	args[1] = &data2;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

bool UMonoComponent::CallOnServerWithVR_Validate(int id, FVector data, FRotator data2)
{
	return true;
}

void UMonoComponent::CallOnServerWithVR_Implementation(int id, FVector data, FRotator data2)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[2];
	args[0] = &data;
	args[1] = &data2;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnClientWithVR_Implementation(int id, FVector data, FRotator data2)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[2];
	args[0] = &data;
	args[1] = &data2;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnAllWithVR_Implementation(int id, FVector data, FRotator data2)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[2];
	args[0] = &data;
	args[1] = &data2;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

bool UMonoComponent::CallOnServerWithVV_Validate(int id, FVector data, FVector data2)
{
	return true;
}

void UMonoComponent::CallOnServerWithVV_Implementation(int id, FVector data, FVector data2)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[2];
	args[0] = &data;
	args[1] = &data2;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnClientWithVV_Implementation(int id, FVector data, FVector data2)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[2];
	args[0] = &data;
	args[1] = &data2;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

void UMonoComponent::CallOnAllWithVV_Implementation(int id, FVector data, FVector data2)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[2];
	args[0] = &data;
	args[1] = &data2;
	MonoMethod* method = NetCallbackTable::GetMethod(mono_object_get_class(m_MonoComponent), id);
	MonoRuntime::Instance()->InvokeMethod(method, m_MonoComponent, args);
}

bool UMonoComponent::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers, FString mapName)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] HostSession But No OnlineSubsytem found!"));
		return false;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

	if (!Sessions.IsValid() || !UserId.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] HostSession Session Or UserId Invalid!"));
		return false;
	}

	MySessionSettings = MakeShareable(new FOnlineSessionSettings());
	MySessionSettings->bIsLANMatch = bIsLAN;
	MySessionSettings->bUsesPresence = bIsPresence;
	MySessionSettings->NumPublicConnections = MaxNumPlayers;
	MySessionSettings->NumPrivateConnections = 0;
	MySessionSettings->bAllowInvites = true;
	MySessionSettings->bAllowJoinInProgress = true;
	MySessionSettings->bShouldAdvertise = true;
	MySessionSettings->bAllowJoinViaPresence = true;
	MySessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

	MySessionSettings->Set(SETTING_MAPNAME, mapName, EOnlineDataAdvertisementType::ViaOnlineService);
	m_MapName = mapName;
	OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
	return Sessions->CreateSession(*UserId, SessionName, *MySessionSettings);
}

void UMonoComponent::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnCreateSessionComplete But No OnlineSubsytem found!"));
		return ;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnCreateSessionComplete Session Invalid!"));
		return ;
	}

	Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
	if (bWasSuccessful)
	{
		OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
		Sessions->StartSession(SessionName);
	}
	else {
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnCreateSessionComplete bWasSuccessful = false!"));
	}
}

void UMonoComponent::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnStartOnlineGameComplete But No OnlineSubsytem found!"));
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnStartOnlineGameComplete Session Invalid!"));
		return;
	}

	Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);

	OnMyStartOnlineGameComplete(bWasSuccessful);
	if (bWasSuccessful)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*m_MapName), true, "listen");
	}
	
}

void UMonoComponent::FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] FindSessions But No OnlineSubsytem found!"));
		OnFindSessionsComplete(false);
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

	if (!Sessions.IsValid() || ! UserId.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] FindSessions Session Or UserID Invalid!"));
		OnFindSessionsComplete(false);
		return;
	}

	MySessionSearch = MakeShareable(new FOnlineSessionSearch());
	MySessionSearch->bIsLanQuery = bIsLAN;
	MySessionSearch->MaxSearchResults = 20;
	MySessionSearch->PingBucketSize = 50;
	if (bIsPresence)
	{
		MySessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
	}
	TSharedRef<FOnlineSessionSearch> SearchSettingsRef = MySessionSearch.ToSharedRef();
	OnFindSessionsCompleteDelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
	Sessions->FindSessions(*UserId, SearchSettingsRef);
}

void UMonoComponent::OnFindSessionsComplete(bool bWasSuccessful)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnFindSessionsComplete But No OnlineSubsytem found!"));
		OnMyFindOnlineGameComplete(false);
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnFindSessionsComplete Session Invalid!"));
		OnMyFindOnlineGameComplete(false);
		return;
	}

	Sessions->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
	OnMyFindOnlineGameComplete(bWasSuccessful);	
}

void UMonoComponent::DoJoinSession(TSharedPtr<const FUniqueNetId> UserId)
{
	FOnlineSessionSearchResult SearchResult;
	if (MySessionSearch->SearchResults.Num() > 0)
	{
		SearchResult = MySessionSearch->SearchResults[0];
		JoinSession(UserId, GameSessionName, SearchResult);
	}
	else {
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] DoJoinSession SearchResults Num = 0."));
	}
}

bool UMonoComponent::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult)
{	
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] JoinSession But No OnlineSubsytem found!"));
		return false;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid() || !UserId.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] JoinSession Session Or UserId Invalid!"));
		return false;
	}

	bool bSuccessful = false;
	OnJoinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
	bSuccessful = Sessions->JoinSession(*UserId, SessionName, SearchResult);

	return bSuccessful;
}

void UMonoComponent::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnJoinSessionComplete But No OnlineSubsytem found!"));
		OnMyJoinOnlineGameComplete(false);
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnJoinSessionComplete Session Invalid!"));
		OnMyJoinOnlineGameComplete(false);
		return;
	}

	bool bSuccess = false;
	Sessions->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
	APlayerController * const PlayerController = GWorld->GetGameInstance()->GetFirstLocalPlayerController();
	FString TravelURL;
	
	if (PlayerController && Sessions->GetResolvedConnectString(SessionName, TravelURL))
	{
		PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
		bSuccess = true;
	}
	OnMyJoinOnlineGameComplete(bSuccess);
}

void UMonoComponent::DestroySession()
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] DestroySession But No OnlineSubsytem found!"));
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] DestroySession Session Invalid!"));
		return;
	}

	OnDestroySessionCompleteDelegateHandle = Sessions->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
	Sessions->DestroySession(GameSessionName);
}

void UMonoComponent::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnDestroySessionComplete But No OnlineSubsytem found!"));
		OnMyDestroyOnlineGameComplete(false);
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnDestroySessionComplete Session Invalid!"));
		OnMyDestroyOnlineGameComplete(false);
		return;
	}

	Sessions->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
	
	//if (bWasSuccessful)
	{
		//TODO open a new map or close the game
	}

	OnMyDestroyOnlineGameComplete(bWasSuccessful);
}

void UMonoComponent::DestroySessionAndLeaveGame()
{
	DestroySession();
}

void UMonoComponent::FindOnlineGames()
{
	ULocalPlayer* const Player = GWorld->GetGameInstance()->GetFirstGamePlayer();
	if (Player == nullptr) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] FindOnlineGames But GetFirstGamePlayer is null"));
		return;
	}

	FindSessions(Player->GetPreferredUniqueNetId(), true, true);
}

void UMonoComponent::StartOnlineGame(FString mapName, int32 playerNum)
{
	ULocalPlayer* const Player = GWorld->GetGameInstance()->GetFirstGamePlayer();
	if (Player == nullptr) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] StartOnlineGame But GetFirstGamePlayer is null"));
		return;
	}
	HostSession(Player->GetPreferredUniqueNetId(), GameSessionName, true, true, playerNum, mapName);
}

void UMonoComponent::JoinOnlineGame()
{
	ULocalPlayer* const Player = GWorld->GetGameInstance()->GetFirstGamePlayer();
	if (Player == nullptr)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] JoinOnlineGame But GetFirstGamePlayer is null"));
		return;
	}
	DoJoinSession(Player->GetPreferredUniqueNetId());
}

int32 UMonoComponent::GetOnlineGamePlayerNum()
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] GetOnlineGamePlayerNum But No OnlineSubsytem found!"));
		return 0;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] GetOnlineGamePlayerNum Session Invalid!"));
		return 0;
	}

	FNamedOnlineSession *NamedSession = Sessions->GetNamedSession(GameSessionName);
	if (NamedSession == NULL) {
		return 0;
	}
	return (NamedSession->RegisteredPlayers).Num();
}

void UMonoComponent::OnMyStartOnlineGameComplete(bool bSuccess)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &bSuccess;
	MonoRuntime::Instance()->InvokeMethod(
		m_Callback->OnStartOnlieGameComplete, m_MonoComponent, args);

}

void UMonoComponent::OnMyFindOnlineGameComplete(bool bSuccess)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &bSuccess;
	MonoRuntime::Instance()->InvokeMethod(
		m_Callback->OnFindOnlieGameComplete, m_MonoComponent, args);
}

void UMonoComponent::OnMyJoinOnlineGameComplete(bool bSuccess)
{
	if (m_MonoComponent != NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &bSuccess;
	MonoRuntime::Instance()->InvokeMethod(
		m_Callback->OnJoinOnlieGameComplete, m_MonoComponent, args);
}

void UMonoComponent::OnMyDestroyOnlineGameComplete(bool bSuccess)
{
	if (m_MonoComponent != NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &bSuccess;
	MonoRuntime::Instance()->InvokeMethod(
		m_Callback->OnDestroyOnlieGameComplete, m_MonoComponent, args);
}

