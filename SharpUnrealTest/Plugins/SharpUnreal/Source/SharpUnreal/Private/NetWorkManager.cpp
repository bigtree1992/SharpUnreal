#include "SharpUnrealPrivatePCH.h"
#include "Delegate.h"
#include "NetWorkManager.h"
#include "MonoRuntime.h"
#include "MonoCallbackTable.h"
#include "NetCallbackTable.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

#include "mono/metadata/object.h"

UNetWorkManager::UNetWorkManager()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
	m_MonoComponent = NULL;

	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UNetWorkManager::OnCreateSessionComplete);
	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UNetWorkManager::OnDestroySessionComplete);
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UNetWorkManager::OnFindSessionsComplete);
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UNetWorkManager::OnJoinSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UNetWorkManager::OnStartOnlineGameComplete);
}

UNetWorkManager::~UNetWorkManager()
{
	//GLog->Logf(ELogVerbosity::Log, TEXT("[MonoComponent] destroy: %s"), *GetName());
}

bool UNetWorkManager::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers, FString mapName)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] HostSession But No OnlineSubsytem found!"));
		return false;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

	if (!Sessions.IsValid() || !UserId.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] HostSession Session Or UserId Invalid!"));
		return false;
	}

	MySessionSettings = MakeShareable(new FOnlineSessionSettings());
	MySessionSettings->bIsLANMatch = bIsLAN;
	MySessionSettings->bUsesPresence = bIsPresence;
	MySessionSettings->NumPublicConnections = MaxNumPlayers;
	MySessionSettings->NumPrivateConnections = 0;
	MySessionSettings->bAllowInvites = true;
	MySessionSettings->bAllowJoinInProgress = true;
	MySessionSettings->bShouldAdvertise = true;
	MySessionSettings->bAllowJoinViaPresence = true;
	MySessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

	MySessionSettings->Set(SETTING_MAPNAME, mapName, EOnlineDataAdvertisementType::ViaOnlineService);
	m_MapName = mapName;
	OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
	return Sessions->CreateSession(*UserId, SessionName, *MySessionSettings);
}

void UNetWorkManager::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnCreateSessionComplete But No OnlineSubsytem found!"));
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnCreateSessionComplete Session Invalid!"));
		return;
	}

	Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
	if (bWasSuccessful)
	{
		OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
		Sessions->StartSession(SessionName);
	}
	else {
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnCreateSessionComplete bWasSuccessful = false!"));
	}
}

void UNetWorkManager::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnStartOnlineGameComplete But No OnlineSubsytem found!"));
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnStartOnlineGameComplete Session Invalid!"));
		return;
	}

	Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);

	OnMyStartOnlineGameComplete(bWasSuccessful);
	if (bWasSuccessful)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*m_MapName), true, "listen");
	}

}

void UNetWorkManager::FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] FindSessions But No OnlineSubsytem found!"));
		OnFindSessionsComplete(false);
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

	if (!Sessions.IsValid() || !UserId.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] FindSessions Session Or UserID Invalid!"));
		OnFindSessionsComplete(false);
		return;
	}

	MySessionSearch = MakeShareable(new FOnlineSessionSearch());
	MySessionSearch->bIsLanQuery = bIsLAN;
	MySessionSearch->MaxSearchResults = 20;
	MySessionSearch->PingBucketSize = 50;
	if (bIsPresence)
	{
		MySessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
	}
	TSharedRef<FOnlineSessionSearch> SearchSettingsRef = MySessionSearch.ToSharedRef();
	OnFindSessionsCompleteDelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
	Sessions->FindSessions(*UserId, SearchSettingsRef);
}

void UNetWorkManager::OnFindSessionsComplete(bool bWasSuccessful)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnFindSessionsComplete But No OnlineSubsytem found!"));
		OnMyFindOnlineGameComplete(false);
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnFindSessionsComplete Session Invalid!"));
		OnMyFindOnlineGameComplete(false);
		return;
	}

	Sessions->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
	OnMyFindOnlineGameComplete(bWasSuccessful);
}

void UNetWorkManager::DoJoinSession(TSharedPtr<const FUniqueNetId> UserId)
{
	FOnlineSessionSearchResult SearchResult;
	if (MySessionSearch->SearchResults.Num() > 0)
	{
		SearchResult = MySessionSearch->SearchResults[0];
		JoinSession(UserId, GameSessionName, SearchResult);
	}
	else {
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] DoJoinSession SearchResults Num = 0."));
	}
}

bool UNetWorkManager::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] JoinSession But No OnlineSubsytem found!"));
		return false;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid() || !UserId.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] JoinSession Session Or UserId Invalid!"));
		return false;
	}

	bool bSuccessful = false;
	OnJoinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
	bSuccessful = Sessions->JoinSession(*UserId, SessionName, SearchResult);

	return bSuccessful;
}

void UNetWorkManager::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnJoinSessionComplete But No OnlineSubsytem found!"));
		OnMyJoinOnlineGameComplete(false);
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnJoinSessionComplete Session Invalid!"));
		OnMyJoinOnlineGameComplete(false);
		return;
	}

	bool bSuccess = false;
	Sessions->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
	APlayerController * const PlayerController = GWorld->GetGameInstance()->GetFirstLocalPlayerController();
	FString TravelURL;

	if (PlayerController && Sessions->GetResolvedConnectString(SessionName, TravelURL))
	{
		PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
		bSuccess = true;
	}
	OnMyJoinOnlineGameComplete(bSuccess);
}

void UNetWorkManager::DestroySession()
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] DestroySession But No OnlineSubsytem found!"));
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] DestroySession Session Invalid!"));
		return;
	}

	OnDestroySessionCompleteDelegateHandle = Sessions->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
	Sessions->DestroySession(GameSessionName);
}

void UNetWorkManager::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnDestroySessionComplete But No OnlineSubsytem found!"));
		OnMyDestroyOnlineGameComplete(false);
		return;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] OnDestroySessionComplete Session Invalid!"));
		OnMyDestroyOnlineGameComplete(false);
		return;
	}

	Sessions->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);

	//if (bWasSuccessful)
	{
		//TODO open a new map or close the game
	}

	OnMyDestroyOnlineGameComplete(bWasSuccessful);
}

void UNetWorkManager::DestroySessionAndLeaveGame()
{
	DestroySession();
}

void UNetWorkManager::FindOnlineGames()
{
	ULocalPlayer* const Player = GWorld->GetGameInstance()->GetFirstGamePlayer();
	if (Player == nullptr)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] FindOnlineGames But GetFirstGamePlayer is null"));
		return;
	}

	FindSessions(Player->GetPreferredUniqueNetId(), true, true);
}

void UNetWorkManager::StartOnlineGame(FString mapName, int32 playerNum)
{
	ULocalPlayer* const Player = GWorld->GetGameInstance()->GetFirstGamePlayer();
	if (Player == nullptr)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] StartOnlineGame But GetFirstGamePlayer is null"));
		return;
	}
	HostSession(Player->GetPreferredUniqueNetId(), GameSessionName, true, true, playerNum, mapName);
}

void UNetWorkManager::JoinOnlineGame()
{
	ULocalPlayer* const Player = GWorld->GetGameInstance()->GetFirstGamePlayer();
	if (Player == nullptr)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] JoinOnlineGame But GetFirstGamePlayer is null"));
		return;
	}
	DoJoinSession(Player->GetPreferredUniqueNetId());
}

int32 UNetWorkManager::GetOnlineGamePlayerNum()
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] GetOnlineGamePlayerNum But No OnlineSubsytem found!"));
		return 0;
	}
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoComponent] GetOnlineGamePlayerNum Session Invalid!"));
		return 0;
	}

	FNamedOnlineSession *NamedSession = Sessions->GetNamedSession(GameSessionName);
	if (NamedSession == NULL) {
		return 0;
	}
	return (NamedSession->RegisteredPlayers).Num();
}

void UNetWorkManager::OnMyStartOnlineGameComplete(bool bSuccess)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &bSuccess;
	MonoRuntime::Instance()->InvokeMethod(
		m_Callback->OnStartOnlieGameComplete, m_MonoComponent, args);

}

void UNetWorkManager::OnMyFindOnlineGameComplete(bool bSuccess)
{
	if (m_MonoComponent == NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &bSuccess;
	MonoRuntime::Instance()->InvokeMethod(
		m_Callback->OnFindOnlieGameComplete, m_MonoComponent, args);
}

void UNetWorkManager::OnMyJoinOnlineGameComplete(bool bSuccess)
{
	if (m_MonoComponent != NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &bSuccess;
	MonoRuntime::Instance()->InvokeMethod(
		m_Callback->OnJoinOnlieGameComplete, m_MonoComponent, args);
}

void UNetWorkManager::OnMyDestroyOnlineGameComplete(bool bSuccess)
{
	if (m_MonoComponent != NULL)
	{
		return;
	}

	void *args[1];
	args[0] = &bSuccess;
	MonoRuntime::Instance()->InvokeMethod(
		m_Callback->OnDestroyOnlieGameComplete, m_MonoComponent, args);
}
