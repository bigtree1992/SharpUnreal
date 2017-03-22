using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class AudioComponent : SceneComponent
    {
        public float VolumeMultiplier
        {
            get;
            set;
        }

        public float Priority
        {
            get;
            set;
        }

        public float PitchMultiplier
        {
            get;
            set;
        }
        
        public bool IsPlaying
        {
            get;
        }

        public void Play(float StartTime = 0.0f)
        {

        }

        public void Stop()
        {

        }


        public void SetPaused(bool bPause)
        {

        }

        #region 设置事件回调
        public void RegAudioFinished(ActorComponent _this)
        {
        }

        public void RegAudioPlaybackPercent(ActorComponent _this)
        {
        }
        #endregion
    }
}
