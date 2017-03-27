using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class CapsuleComponent : ShapeComponent
    {
        public float CapsuleHalfHeight
        {
            get { return _GetCapsuleHalfHeight(m_NativeHandler); }
            set { _SetCapsuleHalfHeight(m_NativeHandler,value); }
        }

        public float CapsuleRadius
        {
            get { return _GetCapsuleRadius(m_NativeHandler); }
            set { _SetCapsuleHalfHeight(m_NativeHandler, value); }
        }

        public float ShapeScale
        {
            get { return _GetShapeScale(m_NativeHandler); }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetCapsuleHalfHeight(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCapsuleHalfHeight(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetCapsuleRadius(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCapsuleRadius(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetShapeScale(IntPtr handler);
    }
}
