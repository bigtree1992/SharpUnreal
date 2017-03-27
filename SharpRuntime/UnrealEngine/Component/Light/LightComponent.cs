using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class LightComponent : SceneComponent
    {
        public float Intensity
        {
            get { return _GetIntensity(NativeHandler); }
            set { _SetIntensity(NativeHandler, value); }
        }

        public Color LightColor
        {
            get { return _GetLightColor(NativeHandler); }
            set { _SetLightColor(NativeHandler, value); }
        }       
   
        public float IndirectLightingIntensity
        {
            get { return _GetIndirectLightingIntensity(NativeHandler); }
            set { _SetIndirectLightingIntensity(NativeHandler, value); }
        }
        
        public float Temperature
        {
            get { return _GetTemperature(NativeHandler); }
            set { _SetTemperature(NativeHandler, value); }
        }
            
        public bool AffectIndirectLighting
        {
            get { return _GetAffectIndirectLighting(NativeHandler); }
            set { _SetAffectIndirectLighting(NativeHandler,value); }
        }

        public bool AffectTranslucentLighting
        {
            get { return _GetAffectTranslucentLighting(NativeHandler); }
            set { _SetAffectTranslucentLighting(NativeHandler, value); }
        }
        
        public bool EnableLightShaftBloom
        {
            get { return _GetEnableLightShaftBloom(NativeHandler); }
            set { _SetEnableLightShaftBloom(NativeHandler, value); }
        }
        
        public float BloomScale
        {
            get { return _GetBloomScale(NativeHandler); }
            set { _SetBloomScale(NativeHandler,value); }
        }

        public float BloomThreshold
        {
            get { return _GetBloomThreshold(NativeHandler); }
            set { _SetBloomThreshold(NativeHandler,value); }
        }
        
        public Color BloomTint
        {
            get { return _GetBloomTint(NativeHandler); }
            set { _SetBloomTint(NativeHandler,value); }
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
