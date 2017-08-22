using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    /// <summary>
    /// 定序器
    /// </summary>
    public class Sequencer : UObject
    {
        public void Play()
        {
            _Sequencer_Play(NativeHandler);
        }


        public void Pause()
        {
            _Pause(NativeHandler);
        }


        public void Stop()
        {
            _Stop(NativeHandler);
        }

        public float Length
        {
            get
            {
                return _GetLength(NativeHandler);
            }
        }

        public float Current
        {
            get
            {
                return _GetLength(NativeHandler);
            }
            set
            {
                _SetCurrent(NativeHandler, value);
            }
        }

        public float PlayRate
        {
            get
            {
                return _GetPlayRate(NativeHandler);
            }
            set
            {
                _SetPlayRate(NativeHandler, value);
            }
        }
        
        public float StartTime
        {
            get { return _GetStartTime(NativeHandler); }
        }

        public float EndTime
        {
            get
            {
                return _GetStartTime(NativeHandler);
            }
        }        

        public void SetPlaybackRange(float startTime, float endTime)
        {
            _SetPlaybackRange(NativeHandler, startTime, endTime);
        }

        #region 设置事件回调
        public void RegSequencerPlay(ActorComponent _this)
        {
            _RegSequencerPlay(NativeHandler,_this.NativeHandler);
        }
        
        public void RegSequencerPause(ActorComponent _this)
        {
            _RegSequencerPause(NativeHandler, _this.NativeHandler);
        }
        
        public void RegSequencerStop(ActorComponent _this)
        {
            _RegSequencerStop(NativeHandler,_this.NativeHandler);
        }
        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _Sequencer_Play(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _Pause(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _Stop(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetLength(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetCurrent(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCurrent(IntPtr handler, float current);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetPlayRate(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPlayRate(IntPtr handler, float current);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetStartTime(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetEndTime(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPlaybackRange(IntPtr handler, float startTime, float endTime);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegSequencerPlay(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegSequencerPause(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegSequencerStop(IntPtr handler, IntPtr listener);

    }
}
