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
	#if 1 //声明周期函数
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
	

	#endif

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonoComponent)
	FString ComponentName;
private:
	
	_MonoObject * m_MonoComponent;
	uint32_t m_Handle;

	MonoCallback* m_Callback;
};
