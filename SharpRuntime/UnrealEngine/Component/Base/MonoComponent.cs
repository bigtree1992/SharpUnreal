using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class MonoComponent : ActorComponent
    {
        #region 生命周期函数
        protected virtual void OnRegister()
        {
        }

        protected virtual void OnUnregister()
        {
            NativeHandler = IntPtr.Zero;
            if (m_Owner != null)
            {
                m_Owner.UnRegister();
                m_Owner = null;
            }
        }

        protected virtual void Initialize()
        {
        }

        protected virtual void Uninitialize()
        {
        }

        protected virtual void BeginPlay()
        {
        }

        protected virtual void EndPlay(EndPlayReason reason)
        {
        }

        protected virtual void Tick(float dt)
        {
        }
        #endregion

        #region 事件处理
        /// <summary>
        /// 蓝图调用C#脚本的通用事件函数
        /// </summary>
        /// <param name="evt"></param>
        public virtual void OnEvent(string evt)
        {
        }

        /// <summary>
        /// 蓝图调用C#脚本的通用事件函数
        /// </summary>
        /// <param name="evt"></param>
        public virtual void OnEventWithInt(string evt, int data)
        {
        }
        public virtual void OnEventWithFloat(string evt, float data)
        {
        }
        /// <summary>
        /// 蓝图调用C#脚本的通用事件函数
        /// </summary>
        /// <param name="evt"></param>
        public virtual void OnEventWithString(string evt, string data)
        {
        }
        /// <summary>
        /// 蓝图调用C#脚本的通用事件函数
        /// </summary>
        /// <param name="evt"></param>
        public virtual void OnEventWithVector(string evt, Vector data)
        {
        }

        /// <summary>
        /// 发送事件到蓝图
        /// </summary>
        /// <param name="evt"></param>
        public void SendEvent(string evt)
        {
            _SendEvent(NativeHandler, evt);
        }

        /// <summary>
        /// 发送事件到蓝图
        /// </summary>
        /// <param name="evt"></param>
        /// <param name="data"></param>
        public void SendEvent(string evt, string data)
        {
            //如果不是MonoComponent则忽略
            _SendEventWithString(NativeHandler, evt, data);
        }

        /// <summary>
        /// 发送事件到蓝图
        /// </summary>
        /// <param name="evt"></param>
        /// <param name="data"></param>
        public void SendEvent(string evt, int data)
        {
            //如果不是MonoComponent则忽略
            _SendEventWithInt(NativeHandler, evt, data);
        }
        #endregion

        #region 回调函数
        public virtual void OnAppDeactivate()
        {
        }

        public virtual void OnAppHasReactivated()
        {
        }

        public virtual void OnAppWillEnterBackground()
        {
        }

        public virtual void OnAppHasEnteredForeground()
        {
        }

        public virtual void OnAppWillTerminate()
        {
        }

        public virtual void OnComponentHit(PrimitiveComponent self, PrimitiveComponent other, Vector impact)
        {
        }

        public virtual void OnComponentBeginOverlap(PrimitiveComponent self, PrimitiveComponent other, Vector impact)
        {
        }

        public virtual void OnComponentEndOverlap(PrimitiveComponent self, PrimitiveComponent other)
        {
        }

        public virtual void OnComponentWake(PrimitiveComponent self, string bone_name)
        {
        }

        public virtual void OnComponentSleep(PrimitiveComponent self, string bone_name)
        {
        }

        public virtual void OnParticleSpawn(string event_name)
        {
        }

        public virtual void OnParticleBurst(string event_name)
        {
        }

        public virtual void OnParticleDeath(string event_name)
        {
        }

        public virtual void OnParticleCollide(string event_name)
        {
        }

        public virtual void OnSystemFinished(string event_name)
        {
        }

        public virtual void OnAudioFinished(string event_name)
        {
        }

        public virtual void OnAudioPlaybackPercent(string event_name, float percent)
        {
        }

        public virtual void OnSequencerPlay()
        {
        }

        public virtual void OnSequencerPause()
        {
        }

        public virtual void OnSequencerStop()
        {
        }

        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SendEvent(IntPtr handler, string evt);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SendEventWithString(IntPtr handler, string evt, string data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SendEventWithInt(IntPtr handler, string evt, int data);

    }
}
