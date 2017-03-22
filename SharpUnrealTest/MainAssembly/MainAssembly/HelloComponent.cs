using System;
using UnrealEngine;

namespace MainAssembly
{
    public class HelloComponent : ActorComponent
    {
        public override void OnRegister()
        {
            Log.Error("[HelloComponent] OnRegister");
        }

        public override void OnUnregister()
        {
            Log.Error("[HelloComponent] OnUnregister");
        }

        public override void Initialize()
        {
            Log.Error("[HelloComponent] Initialize");
        }

        public override void Uninitialize()
        {
            Log.Error("[HelloComponent] Uninitialize");
        }

        public override void Tick(float dt)
        {
            Log.Error("[HelloComponent] Tick ");
        }

        public override void BeginPlay()
        {
            Log.Error("[HelloComponent] [BeginPlay]");
        }

        public override void EndPlay()
        {
            Log.Error("[HelloComponent] [EndPlay]");
        }

    }
}
