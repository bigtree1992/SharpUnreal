using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    /// <summary>
    /// 组件脚本的基类
    /// </summary>
    public class ActorComponent : UObject
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

        #region 属性
        /// <summary>
        /// Actor是否是激活状态
        /// </summary>
        public bool Activited
        {
            get { return _GetActivited(NativeHandler);}
            set { _SetActivited(NativeHandler,value);}
        }

        /// <summary>
        /// 是否Tick函数会被调用
        /// </summary>
        public bool CanEverTick
        {
            get { return _GetCanEverTick(NativeHandler);}
            set { _SetCanEverTick(NativeHandler,value);}
        }

        private Actor m_Owner;
        public Actor Actor
        {
            get
            {
                if (m_Owner == null)
                {
                    var handler = _GetOwner(NativeHandler);
                    if (handler.ToInt64() == 0)
                    {
                        m_Owner = null;
                    }
                    else
                    {
                        m_Owner = new Actor();
                        m_Owner.NativeHandler = handler;
                    }
                }
                return m_Owner;
            }
            
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
            _SendEventWithString(NativeHandler, evt, data);
        }

        /// <summary>
        /// 发送事件到蓝图
        /// </summary>
        /// <param name="evt"></param>
        /// <param name="data"></param>
        public void SendEvent(string evt, int data)
        {
            _SendEventWithInt(NativeHandler, evt,data);
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

        public virtual void OnComponentHit(PrimitiveComponent self,PrimitiveComponent comp,Vector impact)
        {
        }

        public virtual void OnComponentBeginOverlap(PrimitiveComponent self, PrimitiveComponent comp, Vector impact)
        {
        }

        public virtual void OnComponentEndOverlap(PrimitiveComponent self, PrimitiveComponent comp)
        {
        }

        public virtual void OnComponentWake(PrimitiveComponent self,string bone_name)
        {
        }

        public virtual void OnComponentSleep(PrimitiveComponent self,string bone_name)
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

        public virtual void OnAudioPlaybackPercent(string event_name,float percent)
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

        public bool HasTag(string tag)
        {
            return _HasTag(NativeHandler, tag);
        }

        public void SetTickableWhenPaused(bool bTickableWhenPaused)
        {
            _SetTickableWhenPaused(NativeHandler, bTickableWhenPaused);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetActivited(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetActivited(IntPtr handler,bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetCanEverTick(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCanEverTick(IntPtr handler,bool value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _GetOwner(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetTickableWhenPaused(IntPtr handle, bool bTickableWhenPaused);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _HasTag(IntPtr handle,string tag);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SendEvent(IntPtr handler, string evt);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SendEventWithString(IntPtr handler, string evt,string data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SendEventWithInt(IntPtr handler, string evt,int data);

    }
}
