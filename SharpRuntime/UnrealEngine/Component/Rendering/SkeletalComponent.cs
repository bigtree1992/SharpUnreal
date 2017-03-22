using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class SkeletalComponent : SkinnedMeshComponent
    {

        public float GlobalAnimRateScale
        {
            get;set;
        }

        public void Play(bool looping)
        {

        }

        public void Stop()
        {

        }

        public bool IsPlaying()
        {
            return false;

        }

        public float PlayRate
        {
            get;
            set;
        }


        public void SetEnableBodyGravity(bool bEnableGravity, string BoneName)
        {

        }

        public bool IsBodyGravityEnabled(string BoneName)
        {
            return false;
        }
    }
}
