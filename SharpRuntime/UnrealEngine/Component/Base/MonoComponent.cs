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

        public virtual void OnComponentHit(PrimitiveComponent self, PrimitiveComponent comp, Vector impact)
        {
        }

        public virtual void OnComponentBeginOverlap(PrimitiveComponent self, PrimitiveComponent comp, Vector impact)
        {
        }

        public virtual void OnComponentEndOverlap(PrimitiveComponent self, PrimitiveComponent comp)
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

        #region RPC函数
        public void CallOnServer(string func)
        {
            _CallOnServer(NativeHandler, func);
        }

        public void CallOnServer(string func,int data)
        {
            _CallOnServerWithInt(NativeHandler, func,data);
        }

        public void CallOnServer(string func, string data)
        {
            _CallOnServerWithString(NativeHandler, func, data);
        }

        public void CallOnAll(string func)
        {
            _CallOnAll(NativeHandler, func);
        }

        public void CallOnAll(string func, int data)
        {
            _CallOnAllWithInt(NativeHandler, func, data);
        }

        public void CallOnAll(string func, string data)
        {
            _CallOnAllWithString(NativeHandler, func, data);
        }

        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SendEvent(IntPtr handler, string evt);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SendEventWithString(IntPtr handler, string evt, string data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SendEventWithInt(IntPtr handler, string evt, int data);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnServer(IntPtr handler, string func);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnServerWithInt(IntPtr handler, string func, int data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnServerWithString(IntPtr handler, string func, string data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnAll(IntPtr handler, string func);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnAllWithInt(IntPtr handler, string func, int data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnAllWithString(IntPtr handler, string func, string data);
    }
}
