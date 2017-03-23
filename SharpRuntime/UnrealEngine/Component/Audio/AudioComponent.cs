using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class AudioComponent : SceneComponent
    {
        public float VolumeMultiplier
        {
            get
            {
                return _GetPitchMultiplier(m_NativeHandler);
            }
            set
            {
                _SetPitchMultiplier(m_NativeHandler, value);
            }
        }      

        public float Priority
        {
            get
            {
                return _GetPriority(m_NativeHandler);
            }
            set
            {
                _SetPriority(m_NativeHandler,value);
            }
        }      

        public float PitchMultiplier
        {
            get
            {
                return _GetPitchMultiplier(m_NativeHandler);
            }
            set
            {
                _SetPitchMultiplier(m_NativeHandler, value);
            }
        }

        public bool IsPlaying
        {
            get
            {
                return _GetIsPlaying(m_NativeHandler);
            }
        }

        public void Play(float StartTime = 0.0f)
        {
            _Play(m_NativeHandler, StartTime);
        }


        public void Stop()
        {
            _Stop(m_NativeHandler);
        }
        
        public void SetPaused(bool bPause)
        {
            _SetPaused(m_NativeHandler,bPause);
        }
        
        #region 设置事件回调
        public void RegAudioFinished(ActorComponent _this)
        {
            _RegAudioFinished(_this.NativeHandler);
        }

        public void RegAudioPlaybackPercent(ActorComponent _this)
        {
            _RegAudioPlaybackPercent(_this.NativeHandler);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetVolumeMultiplier(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetVolumeMultiplier(IntPtr handler, float volume);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetPriority(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPriority(IntPtr handler, float priority);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetPitchMultiplier(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPitchMultiplier(IntPtr handler, float multiplier);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsPlaying(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _Play(IntPtr handler, float StartTime);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _Stop(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPaused(IntPtr handler, bool bPause);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAudioFinished(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAudioPlaybackPercent(IntPtr handler);

        #endregion
    }
}
