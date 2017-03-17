using System;
using UnrealEngine;

namespace MainAssembly
{
    public class TestComponent : ActorComponent
    {
        public TestComponent()
        {
        }
        public override void OnRegister()
        {
            base.OnRegister();
            Log.Error("[TestComponent] OnRegister");
        }

        public override void OnUnregister()
        {
            base.OnUnregister();
            Log.Error("[TestComponent] OnUnregister");
        }

        public override void Initialize()
        {
            base.Initialize();
            Log.Error("[TestComponent] Initialize");
        }

        public override void Uninitialize()
        {
            base.Uninitialize();
            Log.Error("[TestComponent] Uninitialize");
        }

        public override void Tick(float dt)
        {
            base.Tick(dt);
            Log.Error("[TestComponent] Tick ");
        }

        public override void BeginPlay()
        {
            base.BeginPlay();
            Log.Error("[TestComponent] BeginPlay ");
        }
        public override void EndPlay()
        {
            base.EndPlay();
            Log.Error("[TestComponent] EndPlay ");
        }

    }
}
