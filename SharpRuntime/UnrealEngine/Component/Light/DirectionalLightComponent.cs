using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class DirectionalLightComponent : LightComponent
    {
        public float DynamicShadowDistanceMovableLight
        {
            get;
            set;
        }

        public float DynamicShadowDistanceStationaryLight
        {
            get;
            set;
        }

        public float DynamicShadowCascades
        {
            get;
            set;
        }

        public float CascadeDistributionExponent
        {
            get;
            set;
        }
        
        public float CascadeTransitionFraction
        {
            get;
            set;
        }

        public float SShadowDistanceFadeoutFraction
        {
            get;
            set;
        }
        
        public float EnableLightShaftOcclusion
        {
            get;
            set;
        }

        public float OcclusionMaskDarkness
        {
            get;
            set;
        }

        public Vector LightShaftOverrideDirection
        {
            get;
            set;
        }
    }
}
