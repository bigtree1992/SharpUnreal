using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class PointLightComponent : LightComponent
    {
        public float AttenuationRadius
        {
            get;set;
        }
        public float LightFalloffExponent
        {
            get; set;
        }
        public float SourceRadius
        {
            get; set;
        }
        public float SourceLength
        {
            get; set;
        }
    }
}
