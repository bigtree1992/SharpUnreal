using System;
using UnrealEngine;

namespace MainAssembly
{
    public class TestComponent : ActorComponent
    {
        public override void OnRegister()
        {
            Log.Error("[TestComponent] OnRegister");
        }

        public override void OnUnregister()
        {
            Log.Error("[TestComponent] OnUnregister");
        }

        public override void Initialize()
        {
            Log.Error("[TestComponent] Initialize");
        }

        public override void Uninitialize()
        {
            Log.Error("[TestComponent] Uninitialize");
        }

        public override void Tick(float dt)
        {
            Log.Error("[TestComponent] Tick ");
        }

        public override void BeginPlay()
        {
            Log.Error("[TestComponent] [BeginPlay] ");
        }
        public override void EndPlay()
        {
            Log.Error("[TestComponent] [EndPlay] ");
        }

        public override void OnEvent(string evt)
        {
        }

    }
}
