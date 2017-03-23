using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class SphereComponent : ShapeComponent
    {
        public float SphereRadius
        {
            get { return _GetSphereRadius(m_NativeHandler); }
            set { _SetSphereRadius(m_NativeHandler, value); }
        }

        public float ShapeScale
        {
            get { return _GetShapeScale(m_NativeHandler); }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetSphereRadius(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetSphereRadius(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetShapeScale(IntPtr handler);
    }
}
