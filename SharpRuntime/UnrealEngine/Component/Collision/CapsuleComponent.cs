using System;
using System.Collections.Generic;


namespace UnrealEngine
{
    public class CapsuleComponent : ShapeComponent
    {
        public float CapsuleHalfHeight
        {
            get;
            set;
        }

        public float CapsuleRadius
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
