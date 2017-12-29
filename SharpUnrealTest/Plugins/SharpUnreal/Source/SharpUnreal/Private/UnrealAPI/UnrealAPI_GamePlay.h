#pragma once

/**
* 导出对应UnrealEngine.dll中GamePlay文件夹中的API
*/
class UnrealAPI_GamePlay
{
public:
	static FWindowsPlatformMemory::FSharedMemoryRegion* SharedMemoryRegion;
	static TArray<uint8> byteArr;
	static void RegisterAPI();
};