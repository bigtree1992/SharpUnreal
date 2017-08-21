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

_MonoObject* UMonoComponent::GetMonoObject() 
{
	return this->m_MonoComponent;
}

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

		//设置Mono对象的本地对象为自己
		void * _this = this;
		MonoRuntime::Instance()->SetNativeHandler(m_MonoComponent, &_this);
		//调用Mono初始化方法
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

bool UMonoComponent::CallOnServer_Validate()
{
	return true;
}

void UMonoComponent::CallOnServer_Implementation() 
{

}

void UMonoComponent::CallOnAll_Implementation()
{

}