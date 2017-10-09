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
	
	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	static void SendIntEvent(FString evt, int data);

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	static void SendFloatEvent(FString evt, float data);

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	static void SetStringData(FString key, FString data);

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	static void SetIntData(FString key, int data);

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	static void SetFloatData(FString key, float data);

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	static FString GetStringData(FString key);

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	static int GetIntData(FString key);

	UFUNCTION(BlueprintCallable, Category = "SharpUnreal")
	static float GetFloatData(FString key);

};
