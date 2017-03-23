using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class PointLightComponent : LightComponent
    {
        public float AttenuationRadius
        {
            get { return _GetAttenuationRadius(m_NativeHandler); }
            set { _SetAttenuationRadius(m_NativeHandler, value); }
        }
        public float LightFalloffExponent
        {
            get { return _GetLightFalloffExponent(m_NativeHandler); }
            set { _SetLightFalloffExponent(m_NativeHandler, value); }
        }
        public float SourceRadius
        {
            get { return _GetSourceRadius(m_NativeHandler); }
            set { _SetSourceRadius(m_NativeHandler, value); }
        }
        public float SourceLength
        {
            get { return _GetSourceLength(m_NativeHandler); }
            set { _SetSourceLength(m_NativeHandler, value); }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetAttenuationRadius(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetAttenuationRadius(IntPtr handler, float value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetLightFalloffExponent(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLightFalloffExponent(IntPtr handler, float value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetSourceRadius(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetSourceRadius(IntPtr handler, float value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetSourceLength(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetSourceLength(IntPtr handler, float value);

    }
}
