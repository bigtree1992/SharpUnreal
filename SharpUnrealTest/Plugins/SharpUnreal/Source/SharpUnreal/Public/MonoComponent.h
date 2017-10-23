#pragma once

#include "Online.h"
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
	virtual void BeginDestroy() override;

	virtual void TickComponent( float DeltaTime, ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction ) override;
	#endif
	
	bool Reload();
	
	#if 1 //事件处理
	UPROPERTY(BlueprintAssignable, Category = "SharpUnreal")
	FOnMonoEvent OnMonoEvent;

	UPROPERTY(BlueprintAssignable, Category = "SharpUnreal")
	FOnMonoEventWithString OnMonoEventWithString;

	UPROPERTY(BlueprintAssignable, Category = "SharpUnreal")
	FOnMonoEventWithInt OnMonoEventWithInt;

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	void SendEventToMono(const FString& Event);

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	void SendEventToMonoWithInt(const FString& Event,int data);

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	void SendEventToMonoWithFloat(const FString& Event, float data);

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	void SendEventToMonoWithString(const FString& Event,const FString& data);

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	void SendEventToMonoWithVector(const FString& Event,FVector data);
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

	#if 1
	UFUNCTION(Server, reliable, WithValidation)
	void CallOnServer(int id);

	UFUNCTION(Client, reliable)
	void CallOnClient(int id);

	UFUNCTION(NetMulticast, reliable)
	void CallOnAll(int id);

	UFUNCTION(Server, reliable, WithValidation)
	void CallOnServerWithFloat(int id,float data);

	UFUNCTION(Client, reliable)
	void CallOnClientWithFloat(int id,float data);

	UFUNCTION(NetMulticast, reliable)
	void CallOnAllWithFloat(int id,float data);

	UFUNCTION(Server, reliable, WithValidation)
	void CallOnServerWithVector(int id, FVector data);

	UFUNCTION(Client, reliable)
	void CallOnClientWithVector(int id, FVector data);

	UFUNCTION(NetMulticast, reliable)
	void CallOnAllWithVector(int id, FVector data);

	UFUNCTION(Server, reliable, WithValidation)
	void CallOnServerWithRotator(int id, FRotator data);

	UFUNCTION(Client, reliable)
	void CallOnClientWithRotator(int id, FRotator data);

	UFUNCTION(NetMulticast, reliable)
	void CallOnAllWithRotator(int id, FRotator data);

	UFUNCTION(Server, reliable, WithValidation)
	void CallOnServerWithRR(int id, FRotator data, FRotator data2);

	UFUNCTION(NetMulticast, reliable)
	void CallOnAllWithRR(int id, FRotator data, FRotator data2);

	UFUNCTION(Client, reliable)
	void CallOnClientWithRR(int id, FRotator data, FRotator data2);

	UFUNCTION(Server, reliable, WithValidation)
	void CallOnServerWithVV(int id, FVector data, FVector data2);

	UFUNCTION(NetMulticast, reliable)
	void CallOnAllWithVV(int id, FVector data, FVector data2);

	UFUNCTION(Client, reliable)
	void CallOnClientWithVV(int id, FVector data, FVector data2);

	UFUNCTION(Server, reliable, WithValidation)
	void CallOnServerWithVR(int id, FVector data, FRotator data2);

	UFUNCTION(NetMulticast, reliable)
	void CallOnAllWithVR(int id, FVector data, FRotator data2);

	UFUNCTION(Client, reliable)
	void CallOnClientWithVR(int id, FVector data, FRotator data2);

	UFUNCTION(Server, reliable, WithValidation)
	void CallOnServerWithQuat(int id, FQuat data);

	UFUNCTION(NetMulticast, reliable)
	void CallOnAllWithQuat(int id, FQuat data);

	UFUNCTION(Client, reliable)
	void CallOnClientWithQuat(int id, FQuat data);

	UFUNCTION(Server, reliable, WithValidation)
	void CallOnServerWithVQ(int id, FVector data, FQuat data2);

	UFUNCTION(NetMulticast, reliable)
	void CallOnAllWithVQ(int id, FVector data, FQuat data2);

	UFUNCTION(Client, reliable)
	void CallOnClientWithVQ(int id, FVector data, FQuat data2);

	//OnlineSystem Call Function
	void StartOnlineGame(FString mapName, int32 playerNum);
	void FindOnlineGames();
	void JoinOnlineGame();
	void DestroySessionAndLeaveGame();
	int32 GetOnlineGamePlayerNum();
	//OnlineSystem CallBack Function
	void OnMyStartOnlineGameComplete(bool bSuccess);
	void OnMyFindOnlineGameComplete(bool bSuccess);
	void OnMyJoinOnlineGameComplete(bool bSuccess);
	void OnMyDestroyOnlineGameComplete(bool bSuccess);


	#endif

	_MonoObject * GetMonoObject();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonoComponent)
	FString ComponentName;
protected:	
	_MonoObject * m_MonoComponent;
	uint32_t m_Handle;
	MonoCallback* m_Callback;
protected:
	FString m_MapName;
	TSharedPtr<class FOnlineSessionSettings> MySessionSettings;
	TSharedPtr<class FOnlineSessionSearch> MySessionSearch;

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers, FString mapName);
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);
	void OnFindSessionsComplete(bool bWasSuccessful);

	void DoJoinSession(TSharedPtr<const FUniqueNetId> UserId);
	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void DestroySession();
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
};
