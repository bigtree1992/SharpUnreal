#pragma once

#include "MonoComponent.generated.h"

UCLASS( ClassGroup=(Mono), meta=(BlueprintSpawnableComponent) )
class SHARPUNREAL_API UMonoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonoComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
