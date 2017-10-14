using System;
using UnrealEngine;

namespace MainAssembly
{
    public class NetWorkTest: NetWorkManager
    {
        protected override void BeginPlay()
        {
            base.BeginPlay();

            var life = Actor.GetComponent<AppLifecycleComponent>();
            life.RegAppWillTerminate(this);

            GameConfig.InitConfig(Resource.GetGameConfigDir() + "GameConfig.xml");

            if (GameConfig.singleton.StartAsServer == 1)
            {
                StartOnlineGame("NetWorkMap1", 10);
            }
            else
            {
                FindOnlineGame();
            }

        }

        protected override void EndPlay(EndPlayReason reason)
        {
            base.EndPlay(reason);
            Log.Error("[NetWorkTest] EndPlay");
        }

        public override void OnAppWillTerminate()
        {
            base.OnAppWillTerminate();
            Log.Error("[NetWorkTest] OnAppWillTerminate");
        }

        protected override void OnStartOnlieGameComplete(bool bSuccess)
        {
            base.OnStartOnlieGameComplete(bSuccess);
            Log.Error("[NetWorkTest] OnStartOnlieGameComplete:" + bSuccess);
        }

        protected override void OnFindOnlieGameComplete(bool bSuccess)
        {
            base.OnFindOnlieGameComplete(bSuccess);
            Log.Error("[NetWorkTest] OnFindOnlieGameComplete:" + bSuccess);

            if (bSuccess)
            {
                JoinOnlineGame();
            }
        }

        protected override void OnJoinOnlieGameComplete(bool bSuccess)
        {
            base.OnJoinOnlieGameComplete(bSuccess);
            Log.Error("[NetWorkTest] OnJoinOnlieGameComplete:" + bSuccess);
        }

        protected override void OnDestroyOnlieGameComplete(bool bSuccess)
        {
            base.OnDestroyOnlieGameComplete(bSuccess);
            Log.Error("[NetWorkTest] OnDestroyOnlieGameComplete:" + bSuccess);
        }
    }
}
