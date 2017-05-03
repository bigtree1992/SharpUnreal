using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class DynamicMaterial : Material
    {
        public static DynamicMaterial Create(Material instance,UObject outer)
        {
            var mat = new DynamicMaterial();
            mat.NativeHandler = _Create(instance.NativeHandler, outer.NativeHandler);
            return mat;
        }

        public float GetScalarParameter(string name)
        {
            return _GetScalarParameter(NativeHandler,name);
        }

        public void SetScalarParameter(string name,float value)
        {
            _SetScalarParameter(NativeHandler, name,value);
        }

        public LinearColor GetVectorParameter(string name)
        {
            return _GetVectorParameter(NativeHandler,name);
        }

        public void SetVectorParameter(string name, LinearColor value)
        {
            _SetVectorParameter(NativeHandler, name, value);
        }

        public Texture GetTextureParameter(string name)
        {
            var handler = _GetTextureParameter(NativeHandler, name);
            if (handler.ToInt64() != 0)
            {
                var texture = new Texture();
                texture.NativeHandler = handler;
                return texture;
            }
            else
            {
                return null;
            }
        }

        public void SetTextureParameter(string name, Texture texture)
        {
            _SetTextureParameter(NativeHandler, name, texture.NativeHandler);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _Create(IntPtr mat,IntPtr outer);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetScalarParameter(IntPtr handler,string name);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetScalarParameter(IntPtr handler, string name, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static LinearColor _GetVectorParameter(IntPtr handler, string name);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetVectorParameter(IntPtr handler, string name, LinearColor value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _GetTextureParameter(IntPtr handler, string name);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetTextureParameter(IntPtr handler, string name, IntPtr texture);
        
    }
}
