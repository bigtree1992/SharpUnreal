using System;
using System.Collections.Generic;


namespace UnrealEngine
{
    public class BoxComponent : ShapeComponent
    {
        public Vector BoxExtent
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
