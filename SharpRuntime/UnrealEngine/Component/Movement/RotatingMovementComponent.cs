using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class RotatingMovementComponent : MovementComponent
    {
        public Rotator RotationRate
        {
            get
            {
                return _GetRotationRate(NativeHandler);
            }
            set
            {
                _SetRotationRate(NativeHandler, value);
            }
        }

        public Vector PivotTranslation
        {
            get
            {
                return _GetPivotTranslation(NativeHandler);
            }
            set
            {
                _SetPivotTranslation(NativeHandler, value);
            }
        }

        public bool RotationInLocalSpace
        {
            get
            {
                return _GetRotationInLocalSpace(NativeHandler);
            }
            set
            {
                _SetRotationInLocalSpace(NativeHandler, value);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Rotator _GetRotationRate(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetRotationRate(IntPtr handler, Rotator RotationRate);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetPivotTranslation(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPivotTranslation(IntPtr handler, Vector PivotTranslation);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetRotationInLocalSpace(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetRotationInLocalSpace(IntPtr handler, bool RotationInLocalSpace);

    }
}
