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
        public ActorComponent(IntPtr handler)
        {
            m_NativeHandler = handler;
        }

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
        
        public bool HasTag(string tag)
        {
            return _HasTag(m_NativeHandler,tag);
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
    }
}
