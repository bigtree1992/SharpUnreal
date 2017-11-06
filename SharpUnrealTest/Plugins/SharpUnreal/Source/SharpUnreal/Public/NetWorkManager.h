// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Delegates/DelegateCombinations.h"
#include "Components/ActorComponent.h"
#include "Online.h"
#include "NetWorkManager.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (SharpUnreal), meta = (BlueprintSpawnableComponent))
class SHARPUNREAL_API UNetWorkManager : public UMonoComponent
{
	GENERATED_BODY()
	
public:
		UNetWorkManager();
		virtual ~UNetWorkManager();
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
