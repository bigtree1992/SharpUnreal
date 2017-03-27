using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class TextRenderComponent : PrimitiveComponent
    {
        public string Text
        {
            get { return _GetText(NativeHandler); }
            set { _SetText(NativeHandler, value); }
        }

        public Color Color
        {
            get { return _GetColor(NativeHandler); }
            set { _SetColor(NativeHandler,value); }
        }

        public float XScale
        {
            get { return _GetXScale(NativeHandler); }
            set { _SetXScale(NativeHandler,value); }
        }

        public float YScale
        {
            get { return _GetYScale(NativeHandler); }
            set { _SetYScale(NativeHandler, value); }
        }

        public float WorldSize
        {
            get { return _GetWorldSize(NativeHandler); }
            set { _SetWorldSize(NativeHandler,value); }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static string _GetText(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetText(IntPtr handler, string value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Color _GetColor(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetColor(IntPtr handler, Color value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetSourceLength(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetSourceLength(IntPtr handler, float value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetXScale(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetXScale(IntPtr handler, float value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetYScale(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetYScale(IntPtr handler, float value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetWorldSize(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetWorldSize(IntPtr handler, float value);
    }
}
