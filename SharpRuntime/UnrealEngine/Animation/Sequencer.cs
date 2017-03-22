using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    /// <summary>
    /// 定序器
    /// </summary>
    public class Sequencer : Actor
    {
        public void Play()
        {
        }

        public void Pause()
        {
        }

        public void Stop()
        {
        }

        public int GetLength()
        {
            return 0;
        }

        public int Current
        {
            get;
            set;
        }

        public float PlayRate
        {
            get;
            set;
        }

        public float StartTime
        {
            get;
        }

        public float EndTime
        {
            get;
        }

        public void SetPlaybackRange(float startTime, float endTime)
        {

        }

        #region 设置事件回调
        public void RegSequencerStart(ActorComponent _this)
        {

        }

        public void RegSequencerPause(ActorComponent _this)
        {

        }

        public void RegSequencerStop(ActorComponent _this)
        {

        }
        
        #endregion
    }
}
