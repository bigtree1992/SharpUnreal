using System;
using UnrealEngine;

namespace MainAssembly
{
    public class WorldTest : ActorComponent
    {
        protected override void Initialize()
        {
            base.Initialize();

            var trans = new Transform();
            World.SpwanActor("/Game/Actor3_Blueprint.Actor3_Blueprint_C", ref trans);

        }
    }
}
