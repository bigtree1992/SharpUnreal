using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class LightComponent : SceneComponent
    {
        public float Intensity
        {
            get { return _GetIntensity(m_NativeHandler); }
            set { _SetIntensity(m_NativeHandler, value); }
        }

        public Color LightColor
        {
            get { return _GetLightColor(m_NativeHandler); }
            set { _SetLightColor(m_NativeHandler, value); }
        }       
   
        public float IndirectLightingIntensity
        {
            get { return _GetIndirectLightingIntensity(m_NativeHandler); }
            set { _SetIndirectLightingIntensity(m_NativeHandler, value); }
        }
        
        public float Temperature
        {
            get { return _GetTemperature(m_NativeHandler); }
            set { _SetTemperature(m_NativeHandler, value); }
        }
            
        public bool AffectIndirectLighting
        {
            get { return _GetAffectIndirectLighting(m_NativeHandler); }
            set { _SetAffectIndirectLighting(m_NativeHandler,value); }
        }

        public bool AffectTranslucentLighting
        {
            get { return _GetAffectTranslucentLighting(m_NativeHandler); }
            set { _SetAffectTranslucentLighting(m_NativeHandler, value); }
        }
        
        public bool EnableLightShaftBloom
        {
            get { return _GetEnableLightShaftBloom(m_NativeHandler); }
            set { _SetEnableLightShaftBloom(m_NativeHandler, value); }
        }
        
        public float BloomScale
        {
            get { return _GetBloomScale(m_NativeHandler); }
            set { _SetBloomScale(m_NativeHandler,value); }
        }

        public float BloomThreshold
        {
            get { return _GetBloomThreshold(m_NativeHandler); }
            set { _SetBloomThreshold(m_NativeHandler,value); }
        }
        
        public Color BloomTint
        {
            get { return _GetBloomTint(m_NativeHandler); }
            set { _SetBloomTint(m_NativeHandler,value); }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetIntensity(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetIntensity(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Color _GetLightColor(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLightColor(IntPtr handler, Color value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetIndirectLightingIntensity(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetIndirectLightingIntensity(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetTemperature(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetTemperature(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetAffectIndirectLighting(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetAffectIndirectLighting(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetAffectTranslucentLighting(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetAffectTranslucentLighting(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetEnableLightShaftBloom(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetEnableLightShaftBloom(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetBloomScale(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBloomScale(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetBloomThreshold(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBloomThreshold(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Color _GetBloomTint(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBloomTint(IntPtr handler, Color value);
    }
}
