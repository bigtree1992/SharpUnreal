#pragma once

#include "MonoComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMonoEvent,const FString&,Event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMonoEventWithString,const FString&,Event,const FString&,Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMonoEventWithInt,const FString&,Event,int,Data);

struct _MonoObject;
struct MonoCallback;

UCLASS( ClassGroup=(SharpUnreal), meta=(BlueprintSpawnableComponent) )
class SHARPUNREAL_API UMonoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMonoComponent();
	virtual ~UMonoComponent();
	#if 1 //生命周期函数
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction ) override;
	#endif
	
	#if 1 //事件处理
	UPROPERTY(BlueprintAssignable, Category = "SharpUnreal")
	FOnMonoEvent OnMonoEvent;

	UPROPERTY(BlueprintAssignable, Category = "SharpUnreal")
	FOnMonoEventWithString OnMonoEventWithString;

	UPROPERTY(BlueprintAssignable, Category = "SharpUnreal")
	FOnMonoEventWithInt OnMonoEventWithInt;

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	void SendEventToMono(const FString& Event);
	#endif

	#if 1 // 回调函数
	UFUNCTION()
	void OnAppDeactivate();
	UFUNCTION()
	void OnAppHasReactivated();
	UFUNCTION()
	void OnAppWillEnterBackground();
	UFUNCTION()
	void OnAppHasEnteredForeground();
	UFUNCTION()
	void OnAppWillTerminate();
	
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
		 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnComponentWake(UPrimitiveComponent* WakingComponent, FName BoneName);
	UFUNCTION()
	void OnComponentSleep(UPrimitiveComponent* SleepingComponent, FName BoneName);

	UFUNCTION()
	void OnParticleSpawn(FName EventName, float EmitterTime, FVector Location, FVector Velocity);
	UFUNCTION()
	void OnParticleBurst(FName EventName, float EmitterTime, int32 ParticleCount);
	UFUNCTION()
	void OnParticleDeath(FName EventName, float EmitterTime, int32 ParticleTime, 
		FVector Location, FVector Velocity, FVector Direction);
	UFUNCTION()
	void OnParticleCollide(FName EventName, float EmitterTime, int32 ParticleTime, 
		FVector Location, FVector Velocity, FVector Direction, FVector Normal, FName BoneName, UPhysicalMaterial* PhysMat);
	UFUNCTION()
	void OnSystemFinished(UParticleSystemComponent* PSystem);
	
	UFUNCTION()
	void OnAudioFinished(const UAudioComponent* Audio);
	UFUNCTION()
	void OnAudioPlaybackPercent(const UAudioComponent* Audio,const class USoundWave* PlayingSoundWave, const float PlaybackPercent);
	
	UFUNCTION()
	void OnSequencerPlay();
	UFUNCTION()
	void OnSequencerPause();
	UFUNCTION()
	void OnSequencerStop();

	#endif

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonoComponent)
	FString ComponentName;
private:
	
	_MonoObject * m_MonoComponent;
	uint32_t m_Handle;

	MonoCallback* m_Callback;
};
