using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class LightComponent : SceneComponent
    {
        public float Intensity
        {
            get;set;
        }

        public Color LightColor
        {
            get;set;
        }

        public float IndirectLightingIntensity
        {
            get;set;
        }

        public float Temperature
        {
            get;set;
        }

        public bool AffectIndirectLighting
        {
            get; set;
        }

        public bool AffectTranslucentLighting
        {
            get;
            set;
        }

        public float EnableLightShaftBloom
        {
            get; set;
        }

        public float BloomScale
        {
            get; set;
        }

        public float BloomThreshold
        {
            get; set;
        }

        public Color BloomTint
        {
            get; set;
        }
    }
}
