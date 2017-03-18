using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class SceneComponent : ActorComponent
    {
        public SceneComponent(IntPtr handler) : base(handler)
        {}

        /// <summary>
        /// 设置跟获取可见性
        /// </summary>
        public bool Visible
        {
            get { return _GetVisible(m_NativeHandler); }
            set { _SetVisible(m_NativeHandler, value); }
        }

        /// <summary>
        /// 设置跟获取是否隐藏
        /// </summary>
        public bool HiddenInGame
        {
            get { return _GetHiddenInGame(m_NativeHandler); }
            set { _SetHiddenInGame(m_NativeHandler, value); }
        }

        public Transform Transform
        {
            get
            {
                return _GetTransform(m_NativeHandler);
            }
            set
            {
                _SetTransform(m_NativeHandler, value);
            }
        }

        public Vector Position
        {
            get
            {
                return _GetPosition(m_NativeHandler);
            }
            set
            {
                _SetPosition(m_NativeHandler, value);
            }
        }

        public Quat Rotation
        {
            get
            {
                return _GetRotation(m_NativeHandler);
            }
            set
            {
                _SetRotation(m_NativeHandler, value);
            }
        }

        public Vector Scale
        {
            get
            {
                return _GetScale(m_NativeHandler);
            }
            set
            {
                _SetScale(m_NativeHandler, value);
            }
        }

        public Vector Forward
        {
            get
            {
                return _GetForward(m_NativeHandler);
            }
        }

        public Vector Right
        {
            get
            {
                return _GetRight(m_NativeHandler);
            }
        }

        public Vector Up
        {
            get
            {
                return _GetUp(m_NativeHandler);
            }
        }
        
        public Transform LocalTransform
        {
            get
            {
                return _GetLocalTransform(m_NativeHandler);
            }
            set
            {
                _SetLocalTransform(m_NativeHandler, value);
            }
        }

        public Vector LocalPosition
        {
            get
            {
                return _GetLocalPosition(m_NativeHandler);
            }
            set
            {
                _SetLocalPosition(m_NativeHandler, value);
            }
        }

        public Quat LocalRotation
        {
            get
            {
                return _GetLocalRotation(m_NativeHandler);
            }
            set
            {
                _SetLocalRotation(m_NativeHandler, value);
            }
        }
        
        public Vector LocalScale
        {
            get
            {
                return _GetLocalScale(m_NativeHandler);
            }
        }     

        public bool SimulatingPhysics
        {
            get { return _GetSimulatingPhysics(m_NativeHandler); }
            set { _SetSimulatingPhysics(m_NativeHandler, value); }
        }
        
        public void AttachTo(SceneComponent parent, string socket)
        {
            _AttachTo(m_NativeHandler,parent,socket);
        }       

        public void SnapTo(SceneComponent parent, string socket)
        {
            _SnapTo(m_NativeHandler, parent, socket);
        }
        
        public void Detach()
        {
            _Detach(m_NativeHandler);
        }
        
        public string AttachedSocket
        {
            get { return _GetAttachedSocket(m_NativeHandler); }
        }
        
        public Transform GetSocketTransform(string socket)
        {
            return _GetSocketTransform(m_NativeHandler, socket);
        }
        
        public Vector GetSocketLocation(string socket)
        {
            return _GetSocketLocation(m_NativeHandler,socket);
        }
        
        public Quat GetSocketRotation(string socket)
        {
            return _GetSocketRotation(m_NativeHandler,socket);
        }
        
        bool DoesSocketExist(string socket)
        {
            return _DoesSocketExist(m_NativeHandler,socket);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Transform _GetTransform(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetTransform(IntPtr handle, Transform trans);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetPosition(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPosition(IntPtr handle, Vector trans);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Quat _GetRotation(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetRotation(IntPtr handle, Quat trans);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetScale(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetScale(IntPtr handle, Vector trans);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetForward(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetRight(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetUp(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Transform _GetLocalTransform(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLocalTransform(IntPtr handle, Transform trans);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetLocalPosition(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLocalPosition(IntPtr handle, Vector trans);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Quat _GetLocalRotation(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLocalRotation(IntPtr handle, Quat trans);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetLocalScale(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLocalScale(IntPtr handle, Vector trans);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetSimulatingPhysics(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AttachTo(IntPtr handle, SceneComponent parent, string socket);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SnapTo(IntPtr handle, SceneComponent parent, string socket);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _Detach(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static string _GetAttachedSocket(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Transform _GetSocketTransform(IntPtr handle, string socket);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetSocketLocation(IntPtr handle, string socket);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Quat _GetSocketRotation(IntPtr handle, string socket);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _DoesSocketExist(IntPtr handle, string socket);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetVisible(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetVisible(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetHiddenInGame(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetHiddenInGame(IntPtr handler, bool value);
    }
}
