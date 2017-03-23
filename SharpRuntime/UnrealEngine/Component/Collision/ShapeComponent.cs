﻿using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class ShapeComponent : PrimitiveComponent
    {

        public Color ShapeColor
        {
            get { return _GetShapeColor(m_NativeHandler); }
            set { _SetShapeColor(m_NativeHandler, value); }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Color _GetShapeColor(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetShapeColor(IntPtr handler, Color value);
    }
}
