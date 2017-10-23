using System;
using System.Collections.Generic;
using System.Threading;
using UnrealEngine;

namespace MainAssembly
{
    public class ThreadTest : MonoComponent
    {
        protected override void Initialize()
        {
            base.Initialize();
            CanEverTick = true;

        }

        protected override void BeginPlay()
        {
            base.BeginPlay();
        }

        protected override void Tick(float dt)
        {
            base.Tick(dt);

            Log.Debug(Actor.Name  + "=" + Thread.CurrentThread.ManagedThreadId.ToString());
        }
    }
}
