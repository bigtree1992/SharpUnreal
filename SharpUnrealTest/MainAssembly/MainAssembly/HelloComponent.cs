using System;
using UnrealEngine;

namespace MainAssembly
{
    public class HelloComponent : ActorComponent
    {
        protected override void OnRegister()
        {
            Log.Error("[HelloComponent] OnRegister");
        }

        protected override void OnUnregister()
        {
            Log.Error("[HelloComponent] OnUnregister");
        }

        protected override void Initialize()
        {
            Log.Error("[HelloComponent] Initialize");
        }

        protected override void Uninitialize()
        {
            Log.Error("[HelloComponent] Uninitialize");
        }

        protected override void Tick(float dt)
        {
            Log.Error("[HelloComponent] Tick ");
        }

        protected override void BeginPlay()
        {
            Log.Error("[HelloComponent] [BeginPlay]");
        }

        protected override void EndPlay(EndPlayReason reason)
        {
            Log.Error("[HelloComponent] [EndPlay] " + reason);
        }

    }
}
