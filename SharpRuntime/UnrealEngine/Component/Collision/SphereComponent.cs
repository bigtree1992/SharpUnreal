using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class SphereComponent : ShapeComponent
    {

        public float SphereRadius
        {
            get;
            set;
        }

        public float GetShapeScale()
        {
            return 0.0f;
        }
    }
}
