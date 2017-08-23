using System;
using UnrealEngine;

namespace MainAssembly
{
    class TraceLineTest:MonoComponent
    {
        protected override void BeginPlay()
        {
            base.BeginPlay();
            TestLineTrace();
        }

        private void TestLineTrace()
        {
            if(Actor == null)
            {
                Log.Error("[TraceLineTest] Actor is null");
                return;
            }
            if(Actor.Root == null)
            {
                Log.Error("[TraceLineTest] Actor.Root is null");
            }
            Vector start = Actor.Root.LocalPosition;
            Vector end = Actor.Root.Up * -1000;
            Vector hitpoint = Physics.LineTraceSingleGetPoint(start,end,CollisionChannel.Visibility);
            Log.Error("[TraceLineTest] start:" + start + ",end:" + end + ",hitpoint:" + hitpoint);
        }
    }
}
