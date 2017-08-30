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
            Vector end = new Vector(Actor.Root.LocalPosition.X, Actor.Root.LocalPosition.Y, -1000);
            Vector hitpoint = Physics.LineTraceSingleGetPointWithTag(start,end,CollisionChannel.WorldStatic,"Floor");
            Log.Error("[TraceLineTest] start:" + start + ",end:" + end + ",hitpoint:" + hitpoint);
        }
    }
}
