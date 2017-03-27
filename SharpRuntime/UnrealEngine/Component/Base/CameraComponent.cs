using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class CameraComponent : SceneComponent
    {
        public float FieldOfView
        {
            get { return _GetFieldOfView(NativeHandler); }
            set { _SetFieldOfView(NativeHandler, value); }
        }

        public float OrthoWidth
        {
            get { return _GetOrthoWidth(NativeHandler); }
            set { _SetOrthoWidth(NativeHandler, value); }
        }

        public float OrthoNearClipPlane
        {
            get { return _GetOrthoNearClipPlane(NativeHandler);}
            set { _SetOrthoNearClipPlane(NativeHandler, value);}
        }

        public float OrthoFarClipPlane
        {
            get { return _GetOrthoFarClipPlane(NativeHandler); }
            set { _SetOrthoFarClipPlane(NativeHandler, value); }
        }

        public float AspectRatio
        {
            get { return _GetAspectRatio(NativeHandler);}
            set { _SetAspectRatio(NativeHandler, value);}
        }

        public bool ConstrainAspectRatio
        {
            get { return _GetConstrainAspectRatio(NativeHandler);}
            set { _SetConstrainAspectRatio(NativeHandler, value);}
        }

        public bool UseFieldOfViewForLOD
        {
            get { return _GetUseFieldOfViewForLOD(NativeHandler); }
            set { _SetUseFieldOfViewForLOD(NativeHandler, value); }
        }

        public bool LockToHmd
        {
            get { return _GetLockToHmd(NativeHandler);}
            set {_SetLockToHmd(NativeHandler, value);}
        }

        public bool UsePawnControlRotation
        {
            get { return _GetUsePawnControlRotation(NativeHandler);}
            set { _SetUsePawnControlRotation(NativeHandler, value); }
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
