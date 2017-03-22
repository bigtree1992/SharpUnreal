using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class SpotLightComponent : LightComponent
    {
        public float InnerConeAngle
        {
            get;set;
        }

        public float OuterConeAngle
        {
            get;set;
        }
    }
}
