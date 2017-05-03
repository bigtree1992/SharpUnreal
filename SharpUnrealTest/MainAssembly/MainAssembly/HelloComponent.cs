using System;
using UnrealEngine;

namespace MainAssembly
{
    public class HelloComponent : ActorComponent
    {
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
