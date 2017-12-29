using System;
using UnrealEngine;

namespace MainAssembly
{
    class ShareMemoryTest: MonoComponent
    {
        public string TestString = "TestString";

        protected override void BeginPlay()
        {
            base.BeginPlay();
            ShareMemory._CreateMemory("test", 100);
            ShareMemory._WriteMemory("1111");
            Log.Error(ShareMemory._ReadMemory());
            ShareMemory._WriteMemoryWithData(Vector.ZeroVector, Rotator.ZeroRotator, Vector.ZeroVector);
            ShareMemory._DestroyMemory();
        }
    }
}
