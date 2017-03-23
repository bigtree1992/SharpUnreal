using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class CameraComponent : SceneComponent
    {
        public float FieldOfView
        {
            get { return _GetFieldOfView(m_NativeHandler); }
            set { _SetFieldOfView(m_NativeHandler, value); }
        }

        public float OrthoWidth
        {
            get { return _GetOrthoWidth(m_NativeHandler); }
            set { _SetOrthoWidth(m_NativeHandler, value); }
        }

        public float OrthoNearClipPlane
        {
            get { return _GetOrthoNearClipPlane(m_NativeHandler);}
            set { _SetOrthoNearClipPlane(m_NativeHandler, value);}
        }

        public float OrthoFarClipPlane
        {
            get { return _GetOrthoFarClipPlane(m_NativeHandler); }
            set { _SetOrthoFarClipPlane(m_NativeHandler, value); }
        }

        public float AspectRatio
        {
            get { return _GetAspectRatio(m_NativeHandler);}
            set { _SetAspectRatio(m_NativeHandler, value);}
        }

        public bool ConstrainAspectRatio
        {
            get { return _GetConstrainAspectRatio(m_NativeHandler);}
            set { _SetConstrainAspectRatio(m_NativeHandler, value);}
        }

        public bool UseFieldOfViewForLOD
        {
            get { return _GetUseFieldOfViewForLOD(m_NativeHandler); }
            set { _SetUseFieldOfViewForLOD(m_NativeHandler, value); }
        }

        public bool LockToHmd
        {
            get { return _GetLockToHmd(m_NativeHandler);}
            set {_SetLockToHmd(m_NativeHandler, value);}
        }

        public bool UsePawnControlRotation
        {
            get { return _GetUsePawnControlRotation(m_NativeHandler);}
            set { _SetUsePawnControlRotation(m_NativeHandler, value); }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetFieldOfView(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetFieldOfView(IntPtr handler, float FieldOfView);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetOrthoWidth(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetOrthoWidth(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetOrthoNearClipPlane(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetOrthoNearClipPlane(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetOrthoFarClipPlane(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetOrthoFarClipPlane(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetAspectRatio(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetAspectRatio(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetConstrainAspectRatio(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetConstrainAspectRatio(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetUseFieldOfViewForLOD(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetUseFieldOfViewForLOD(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetLockToHmd(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLockToHmd(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetUsePawnControlRotation(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetUsePawnControlRotation(IntPtr handler, bool value);
    }
}
