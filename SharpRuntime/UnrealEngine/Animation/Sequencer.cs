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
            _Play(m_NativeHandler);
        }


        public void Pause()
        {
            _Pause(m_NativeHandler);
        }


        public void Stop()
        {
            _Stop(m_NativeHandler);
        }

        public float Length
        {
            get
            {
                return _GetLength(m_NativeHandler);
            }
        }
        public float Current
        {
            get
            {
                return _GetLength(m_NativeHandler);
            }
            set
            {
                _SetCurrent(m_NativeHandler, value);
            }
        }

        public float PlayRate
        {
            get
            {
                return _GetPlayRate(m_NativeHandler);
            }
            set
            {
                _SetPlayRate(m_NativeHandler, value);
            }
        }
        
        public float StartTime
        {
            get { return _GetStartTime(m_NativeHandler); }
        }

        public float EndTime
        {
            get
            {
                return _GetStartTime(m_NativeHandler);
            }
        }        

        public void SetPlaybackRange(float startTime, float endTime)
        {
            _SetPlaybackRange(m_NativeHandler, startTime, endTime);
        }

        #region 设置事件回调
        public void RegSequencerStart(ActorComponent _this)
        {
            _RegSequencerStart(m_NativeHandler,_this.NativeHandler);
        }
        
        public void RegSequencerPause(ActorComponent _this)
        {
            _RegSequencerPause(m_NativeHandler, _this.NativeHandler);
        }
        
        public void RegSequencerStop(ActorComponent _this)
        {
            _RegSequencerStop(m_NativeHandler,_this.NativeHandler);
        }
        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _Play(IntPtr handler);
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
        private extern static void _RegSequencerStart(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegSequencerPause(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegSequencerStop(IntPtr handler, IntPtr listener);

    }
}
