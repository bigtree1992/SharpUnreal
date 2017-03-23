using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class BoxComponent : ShapeComponent
    {
        public Vector BoxExtent
        {
            get { return _GetBoxExtent(m_NativeHandler); }
            set { _SetBoxExtent(m_NativeHandler, value); }
        }

        public float ShapeScale
        {
            get { return _GetShapeScale(m_NativeHandler); }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetBoxExtent(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBoxExtent(IntPtr handler, Vector value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetShapeScale(IntPtr handler);
    }
}
