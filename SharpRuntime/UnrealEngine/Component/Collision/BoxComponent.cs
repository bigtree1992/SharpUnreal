using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class BoxComponent : ShapeComponent
    {
        public Vector BoxExtent
        {
            get { return _GetBoxExtent(NativeHandler); }
            set { _SetBoxExtent(NativeHandler, value); }
        }

        public Vector ShapeScale
        {
            get { return _GetShapeScale(NativeHandler); }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetBoxExtent(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBoxExtent(IntPtr handler, Vector value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetShapeScale(IntPtr handler);
    }
}
