#pragma once

#include "MonoComponent.generated.h"

struct _MonoObject;
struct _MonoMethod;

UCLASS( ClassGroup=(SharpUnreal), meta=(BlueprintSpawnableComponent) )
class SHARPUNREAL_API UMonoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMonoComponent();
	virtual ~UMonoComponent();
	
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction ) override;
private:
	void InitMonoCallback();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonoComponent)
	FString ComponentName;
private:
	
	_MonoObject * m_MonoComponent;
	uint32_t m_Handle;

	_MonoMethod* ActorComponent_OnRegister;
	_MonoMethod* ActorComponent_OnUnregister;
	_MonoMethod* ActorComponent_Initialize;
	_MonoMethod* ActorComponent_Uninitialize;
	_MonoMethod* ActorComponent_BeginPlay;
	_MonoMethod* ActorComponent_EndPlay;
	_MonoMethod* ActorComponent_Tick;
};
