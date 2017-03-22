using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    enum EEndPlayReason
    {
        /** When the Actor or Component is explicitly destroyed. */
        Destroyed,
        /** When the world is being unloaded for a level transition. */
        LevelTransition,
        /** When the world is being unloaded because PIE is ending. */
        EndPlayInEditor,
        /** When the level it is a member of is streamed out. */
        RemovedFromWorld,
        /** When the application is being exited. */
        Quit,
    };

    /// <summary>
    /// 组件脚本的基类
    /// </summary>
    public class ActorComponent : UObject
    {     
        #region 生命周期函数
        public virtual void OnRegister()
        {          
        }

        public virtual void OnUnregister()
        {
        }

        public virtual void Initialize()
        {
        }

        public virtual void Uninitialize()
        {
        }

        public virtual void BeginPlay()
        {
        }

        public virtual void EndPlay()
        {
        }

        public virtual void Tick(float dt)
        {
        }
        #endregion

        #region 属性
        /// <summary>
        /// Actor是否是激活状态
        /// </summary>
        public bool Activited
        {
            get { return _GetActivited(m_NativeHandler);}
            set { _SetActivited(m_NativeHandler,value);}
        }

        /// <summary>
        /// 是否Tick函数会被调用
        /// </summary>
        public bool CanEverTick
        {
            get { return _GetCanEverTick(m_NativeHandler);}
            set { _SetCanEverTick(m_NativeHandler,value);}
        }

        private Actor m_Owner;
        public Actor GetOwner()
        {
            if(m_Owner == null)
            {
                m_Owner = new Actor(_GetOwner(m_NativeHandler));
            }
            return m_Owner;
        }
        #endregion

        #region 事件处理
        /// <summary>
        /// 蓝图调用C#脚本的通用事件函数
        /// </summary>
        /// <param name="dt"></param>
        public virtual void OnEvent(string evt)
        {
        }

        /// <summary>
        /// 发送事件到蓝图
        /// </summary>
        /// <param name="evt"></param>
        public void SendEvent(string evt)
        {
            _SendEvent(m_NativeHandler, evt);
        }

        /// <summary>
        /// 发送事件到蓝图
        /// </summary>
        /// <param name="evt"></param>
        /// <param name="data"></param>
        public void SendEvent(string evt, string data)
        {
            _SendEventWithString(m_NativeHandler, evt, data);
        }

        /// <summary>
        /// 发送事件到蓝图
        /// </summary>
        /// <param name="evt"></param>
        /// <param name="data"></param>
        public void SendEvent(string evt, int data)
        {
            _SendEventWithInt(m_NativeHandler, evt,data);
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

        public virtual void OnComponentHit()
        {
        }

        public virtual void OnComponentBeginOverlap()
        {
        }

        public virtual void OnComponentEndOverlap()
        {
        }

        public virtual void OnComponentWake()
        {
        }

        public virtual void OnComponentSleep()
        {
        }

        public virtual void OnParticleSpawn()
        {
        }

        public virtual void OnParticleBurst()
        {
        }

        public virtual void OnParticleDeath()
        {
        }

        public virtual void OnParticleCollide()
        {
        }

        public virtual void OnAudioFinished()
        {
        }

        public virtual void OnAudioPlaybackPercent()
        {
        }

        public virtual void OnSequencerStart()
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
            return _HasTag(m_NativeHandler, tag);
        }

        public void SetTickableWhenPaused(bool bTickableWhenPaused)
        {
            _SetTickableWhenPaused(m_NativeHandler, bTickableWhenPaused);
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
