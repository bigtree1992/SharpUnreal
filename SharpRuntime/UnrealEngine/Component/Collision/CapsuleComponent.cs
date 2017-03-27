using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class CapsuleComponent : ShapeComponent
    {
        public float CapsuleHalfHeight
        {
            get { return _GetCapsuleHalfHeight(NativeHandler); }
            set { _SetCapsuleHalfHeight(NativeHandler,value); }
        }

        public float CapsuleRadius
        {
            get { return _GetCapsuleRadius(NativeHandler); }
            set { _SetCapsuleHalfHeight(NativeHandler, value); }
        }

        public float ShapeScale
        {
            get { return _GetShapeScale(NativeHandler); }
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
