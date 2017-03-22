#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SharpFunctionLibrary.generated.h"

/**
 * 主要用于实现C#与蓝图的相互通讯
 */
UCLASS(ClassGroup = (SharpUnreal), meta = (BlueprintSpawnableComponent))
class SHARPUNREAL_API USharpFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable,Category="SharpUnreal")
	static void SendStringEvent(FString evt, FString data);
	
};
