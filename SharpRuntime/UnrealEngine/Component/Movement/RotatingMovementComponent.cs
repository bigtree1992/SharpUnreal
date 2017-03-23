using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class RotatingMovementComponent : MovementComponent
    {
        public Rotator RotationRate { get; set; }
        public Vector PivotTranslation { get; set; }
        public bool RotationInLocalSpace { get; set; }
    }
}
