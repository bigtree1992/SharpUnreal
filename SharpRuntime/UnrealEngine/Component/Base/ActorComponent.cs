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

        protected Actor m_Owner;
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

        public bool HasTag(string tag)
        {
            return _HasTag(NativeHandler, tag);
        }
        public void AddTag(string tag)
        {
            _AddTag(NativeHandler, tag);
        }
        public void RemoveTag(string tag)
        {
            _RemoveTag(NativeHandler, tag);
        }

        public void SetTickableWhenPaused(bool bTickableWhenPaused)
        {
            _SetTickableWhenPaused(NativeHandler, bTickableWhenPaused);
        }
        
        public Pawn Pawn
        {
            get
            {
                if(m_Owner == null || m_Owner.GetType() != typeof(Pawn) )
                {
                    var handler = _GetPawn(NativeHandler);
                    if (handler.ToInt64() == 0)
                    {
                        return null;
                    }
                    m_Owner = new Pawn();
                    m_Owner.NativeHandler = handler;
                }
                return m_Owner as Pawn;
            }
        }

        public void Clear()
        {
            NativeHandler = IntPtr.Zero;
            if (m_Owner != null)
            {
                m_Owner.UnRegister();
                m_Owner = null;
            }
        }

        public string Name
        {
            get
            {
                return _GetName(NativeHandler);
            }
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
        private extern static IntPtr _GetPawn(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetTickableWhenPaused(IntPtr handle, bool bTickableWhenPaused);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _HasTag(IntPtr handle,string tag);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddTag(IntPtr handle, string tag);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RemoveTag(IntPtr handle, string tag);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static string _GetName(IntPtr handler);

    }
}
