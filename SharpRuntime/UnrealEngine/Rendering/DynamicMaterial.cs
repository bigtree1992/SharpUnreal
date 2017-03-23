using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class DynamicMaterial : MaterialInstance
    {
        public static DynamicMaterial Create(MaterialInstance instance,UObject outer)
        {
            var mat = new DynamicMaterial();
            mat.NativeHandler = _Create(instance.NativeHandler, outer.NativeHandler);
            return mat;
        }

        public float GetScalarParameter(string name)
        {
            return _GetScalarParameter(m_NativeHandler,name);
        }

        public void SetScalarParameter(string name,float value)
        {
            _SetScalarParameter(m_NativeHandler, name,value);
        }

        public LinearColor GetVectorParameter(string name)
        {
            return _GetVectorParameter(m_NativeHandler,name);
        }

        public void SetVectorParameter(string name, LinearColor value)
        {
            _SetVectorParameter(m_NativeHandler, name, value);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static IntPtr _Create(IntPtr mat,IntPtr outer);
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static float _GetScalarParameter(IntPtr handler,string name);
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void _SetScalarParameter(IntPtr handler, string name, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static LinearColor _GetVectorParameter(IntPtr handler, string name);
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void _SetVectorParameter(IntPtr handler, string name, LinearColor value);
    }
}
