using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class SceneComponent : ActorComponent
    {
        /// <summary>
        /// 设置跟获取可见性
        /// </summary>
        public bool Visible
        {
            get { return _GetVisible(NativeHandler); }
            set { _SetVisible(NativeHandler, value); }
        }

        /// <summary>
        /// 设置跟获取是否隐藏
        /// </summary>
        public bool HiddenInGame
        {
            get { return _GetHiddenInGame(NativeHandler); }
            set { _SetHiddenInGame(NativeHandler, value); }
        }

        public Transform Transform
        {
            get
            {
                return _GetTransform(NativeHandler);
            }
            set
            {
                _SetTransform(NativeHandler, value);
            }
        }

        public Vector Position
        {
            get
            {
                return _GetPosition(NativeHandler);
            }
            set
            {
                _SetPosition(NativeHandler, value);
            }
        }

        public Quat Rotation
        {
            get
            {
                return _GetRotation(NativeHandler);
            }
            set
            {
                _SetRotation(NativeHandler, value);
            }
        }

        public Vector Scale
        {
            get
            {
                return _GetScale(NativeHandler);
            }
            set
            {
                _SetScale(NativeHandler, value);
            }
        }

        public void AddLocalOffset(Vector vector)
        {
            _AddLocalOffset(NativeHandler, vector);
        }

        public void AddLocalRotation(Rotator rot)
        {
            _AddLocalRotation(NativeHandler, rot);
        }

        public Vector Forward
        {
            get
            {
                return _GetForward(NativeHandler);
            }
        }

        public Vector Right
        {
            get
            {
                return _GetRight(NativeHandler);
            }
        }

        public Vector Up
        {
            get
            {
                return _GetUp(NativeHandler);
            }
        }
        
        public Transform LocalTransform
        {
            get
            {
                return _GetLocalTransform(NativeHandler);
            }
            set
            {
                _SetLocalTransform(NativeHandler, value);
            }
        }

        public Vector LocalPosition
        {
            get
            {
                return _GetLocalPosition(NativeHandler);
            }
            set
            {
                _SetLocalPosition(NativeHandler, value);
            }
        }

        public Rotator LocalRotation
        {
            get
            {
                return _GetLocalRotation(NativeHandler);
            }
            set
            {
                _SetLocalRotation(NativeHandler, value);
            }
        }
        
        public Vector LocalScale
        {
            get
            {
                return _GetLocalScale(NativeHandler);
            }
            set
            {
                _SetLocalScale(NativeHandler, value);
            }
        }     

        public bool SimulatingPhysics
        {
            get { return _GetSimulatingPhysics(NativeHandler); }
        }
        
        public void AttachTo(SceneComponent parent)
        {
            _AttachTo(NativeHandler,parent.NativeHandler);
        }       

        public void SnapTo(SceneComponent parent)
        {
            _SnapTo(NativeHandler, parent.NativeHandler);
        }

        public void AttachToSocket(SceneComponent parent, string socket)
        {
            _AttachToSocket(NativeHandler, parent.NativeHandler, socket);
        }

        public void SnapToSocket(SceneComponent parent, string socket)
        {
            _SnapToSocket(NativeHandler, parent.NativeHandler, socket);
        }

        public void Detach()
        {
            _Detach(NativeHandler);
        }
        
        public string AttachedSocket
        {
            get { return _GetAttachedSocket(NativeHandler); }
        }
        
        public Transform GetSocketTransform(string socket)
        {
            return _GetSocketTransform(NativeHandler, socket);
        }
        
        public Vector GetSocketLocation(string socket)
        {
            return _GetSocketLocation(NativeHandler,socket);
        }
        
        public Quat GetSocketRotation(string socket)
        {
            return _GetSocketRotation(NativeHandler,socket);
        }
        
        public bool DoesSocketExist(string socket)
        {
            return _DoesSocketExist(NativeHandler,socket);
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
        private extern static void _AddLocalRotation(IntPtr handle, Rotator rot);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddLocalOffset(IntPtr handle, Vector vector);

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
        private extern static Rotator _GetLocalRotation(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLocalRotation(IntPtr handle, Rotator trans);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetLocalScale(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLocalScale(IntPtr handle, Vector trans);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetSimulatingPhysics(IntPtr handle);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AttachTo(IntPtr handle, IntPtr parent);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SnapTo(IntPtr handle, IntPtr parent);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AttachToSocket(IntPtr handle, IntPtr parent, string socket);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SnapToSocket(IntPtr handle, IntPtr parent, string socket);
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
