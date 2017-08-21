using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class AudioComponent : SceneComponent
    {
        /// <summary>
        /// 播放音量
        /// </summary>
        public float VolumeMultiplier
        {
            get
            {
                return _GetPitchMultiplier(NativeHandler);
            }
            set
            {
                _SetPitchMultiplier(NativeHandler, value);
            }
        }      

        public float Priority
        {
            get
            {
                return _GetPriority(NativeHandler);
            }
            set
            {
                _SetPriority(NativeHandler,value);
            }
        }      

        /// <summary>
        /// 播放速率
        /// </summary>
        public float PitchMultiplier
        {
            get
            {
                return _GetPitchMultiplier(NativeHandler);
            }
            set
            {
                _SetPitchMultiplier(NativeHandler, value);
            }
        }

        public bool IsPlaying
        {
            get
            {
                return _GetIsPlaying(NativeHandler);
            }
        }

        public void Play(float StartTime = 0.0f)
        {
            _Play(NativeHandler, StartTime);
        }


        public void Stop()
        {
            _Stop(NativeHandler);
        }
        
        public void SetPaused(bool bPause)
        {
            _SetPaused(NativeHandler,bPause);
        }
        
        #region 设置事件回调
        public void RegAudioFinished(ActorComponent _this)
        {
            _RegAudioFinished(NativeHandler,_this.NativeHandler);
        }

        public void RegAudioPlaybackPercent(ActorComponent _this)
        {
            _RegAudioPlaybackPercent(NativeHandler, _this.NativeHandler);
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
        private extern static void _RegAudioFinished(IntPtr handler,IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAudioPlaybackPercent(IntPtr handler,IntPtr listener);

        #endregion
    }
}
