using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class SpotLightComponent : LightComponent
    {
        public float InnerConeAngle
        {
            get { return _GetInnerConeAngle(NativeHandler); }
            set { _SetInnerConeAngle(NativeHandler, value); }
        }

        public float OuterConeAngle
        {
            get { return _GetOuterConeAngle(NativeHandler); }
            set { _SetOuterConeAngle(NativeHandler, value); }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetInnerConeAngle(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetInnerConeAngle(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetOuterConeAngle(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetOuterConeAngle(IntPtr handler, float value);
    }
}
