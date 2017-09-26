using System;
using UnrealEngine;

namespace MainAssembly
{
    public class NetWorkBehaviorTest: NetWorkBehavior
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
            Log.Error("[NetWorkBehaviorTest] EndPlay");
        }

        public override void OnAppWillTerminate()
        {
            base.OnAppWillTerminate();
            Log.Error("[NetWorkBehaviorTest] OnAppWillTerminate");
        }

        public override void OnStartOnlieGameComplete(bool bSuccess)
        {
            base.OnStartOnlieGameComplete(bSuccess);
            Log.Error("[NetWorkBehaviorTest] OnStartOnlieGameComplete:" + bSuccess);
        }

        public override void OnFindOnlieGameComplete(bool bSuccess)
        {
            base.OnFindOnlieGameComplete(bSuccess);
            Log.Error("[NetWorkBehaviorTest] OnFindOnlieGameComplete:" + bSuccess);
            if (bSuccess)
            {
                JoinOnlineGame();
            }
        }

        public override void OnJoinOnlieGameComplete(bool bSuccess)
        {
            base.OnJoinOnlieGameComplete(bSuccess);
            Log.Error("[NetWorkBehaviorTest] OnJoinOnlieGameComplete:" + bSuccess);
        }

        public override void OnDestroyOnlieGameComplete(bool bSuccess)
        {
            base.OnDestroyOnlieGameComplete(bSuccess);
            Log.Error("[NetWorkBehaviorTest] OnDestroyOnlieGameComplete:" + bSuccess);
        }
    }
}
