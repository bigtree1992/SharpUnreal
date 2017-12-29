using System;
using UnrealEngine;

namespace MainAssembly
{
    class GetMonoByNameAndActorByTagTest: MonoComponent
    {
        protected override void BeginPlay()
        {
            base.BeginPlay();
            var mono = Actor.GetMonoComponentByTag("ShareMemoryTest") as ShareMemoryTest;
            Log.Error(mono.Name);
            Log.Error(mono.TestString);
            //Log.Error((Actor.GetMonoComponentByName("MonoShareMemory") as ShareMemoryTest).TestString);

            Actor act = new Actor( World.GetActorWithTag("Cube"));
            Log.Error(act.Name);
            Actor.Root.Position = act.Root.Position;
        }
    }
}
