using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class DirectionalLightComponent : LightComponent
    {
        public float DynamicShadowDistanceMovableLight
        {
            get { return _GetDynamicShadowDistanceMovableLight(NativeHandler); }
            set { _SetDynamicShadowDistanceMovableLight(NativeHandler,value); }
        }

        public float DynamicShadowDistanceStationaryLight
        {
            get { return _GetDynamicShadowDistanceStationaryLight(NativeHandler); }
            set { _SetDynamicShadowDistanceStationaryLight(NativeHandler,value); }
        }

        public float DynamicShadowCascades
        {
            get { return _GetDynamicShadowCascades(NativeHandler); }
            set { _SetDynamicShadowCascades(NativeHandler, value); }
        }

        public float CascadeDistributionExponent
        {
            get { return _GetCascadeDistributionExponent(NativeHandler); }
            set { _SetCascadeDistributionExponent(NativeHandler,value); }
        }
        
        public float CascadeTransitionFraction
        {
            get { return _GetCascadeTransitionFraction(NativeHandler); }
            set { _SetCascadeTransitionFraction(NativeHandler,value); }
        }

        public float ShadowDistanceFadeoutFraction
        {
            get { return _GetShadowDistanceFadeoutFraction(NativeHandler); }
            set { _SetShadowDistanceFadeoutFraction(NativeHandler,value); }
        }
        
        public bool EnableLightShaftOcclusion
        {
            get { return _GetEnableLightShaftOcclusion(NativeHandler); }
            set { _SetEnableLightShaftOcclusion(NativeHandler, value); }
        }

        public float OcclusionMaskDarkness
        {
            get { return _GetOcclusionMaskDarkness(NativeHandler); }
            set { _SetOcclusionMaskDarkness(NativeHandler, value); }
        }

        public Vector LightShaftOverrideDirection
        {
            get { return _GetLightShaftOverrideDirection(NativeHandler); }
            set { _SetLightShaftOverrideDirection(NativeHandler, value); }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetDynamicShadowDistanceMovableLight(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetDynamicShadowDistanceMovableLight(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetDynamicShadowDistanceStationaryLight(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetDynamicShadowDistanceStationaryLight(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetDynamicShadowCascades(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetDynamicShadowCascades(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetCascadeDistributionExponent(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCascadeDistributionExponent(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetCascadeTransitionFraction(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCascadeTransitionFraction(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetShadowDistanceFadeoutFraction(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetShadowDistanceFadeoutFraction(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetEnableLightShaftOcclusion(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetEnableLightShaftOcclusion(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetOcclusionMaskDarkness(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetOcclusionMaskDarkness(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetLightShaftOverrideDirection(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLightShaftOverrideDirection(IntPtr handler, Vector value);

    }
}
