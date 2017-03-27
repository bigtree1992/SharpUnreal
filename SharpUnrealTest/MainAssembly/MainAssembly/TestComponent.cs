using System;
using UnrealEngine;

namespace MainAssembly
{
    public class TestComponent : ActorComponent
    {
        protected override void OnRegister()
        {
            Log.Error("[TestComponent] OnRegister");
        }

        protected override void OnUnregister()
        {
            Log.Error("[TestComponent] OnUnregister");
        }

        protected override void Initialize()
        {
            Log.Error("[TestComponent] Initialize");
            if (Actor.Root.HasTag("Hello"))
            {
                Log.Error("[TestComponent] True! Hello!");
            }
            else
            {
                Log.Error("[TestComponent] False! Hello!");
            }
            Actor.Root.LocalPosition = Actor.Root.LocalPosition + new Vector(0, 0, 100);

        }

        protected override void Uninitialize()
        {
            Log.Error("[TestComponent] Uninitialize");
        }

        protected override void Tick(float dt)
        {
            Log.Error("[TestComponent] Tick ");
        }

        protected override void BeginPlay()
        {
            Log.Error("[TestComponent] [BeginPlay] ");
        }
        protected override void EndPlay(EndPlayReason reason)
        {
            Log.Error("[TestComponent] [EndPlay] " + reason);
        }

        public override void OnEvent(string evt)
        {
        }

    }
}
