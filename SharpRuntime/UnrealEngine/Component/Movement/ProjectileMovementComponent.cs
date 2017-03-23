using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class ProjectileMovementComponent : MovementComponent
    {
        public float InitialSpeed { get; set; }

        public float MaxSpeed { get; set; }

        public bool bRotationFollowsVelocity { get; set; }

        public bool bShouldBounce { get; set; }

        public bool bInitialVelocityInLocalSpace { get; set; }

        public bool bForceSubStepping { get; set; }

        public bool bIsHomingProjectile { get; set; }

        public bool bBounceAngleAffectsFriction { get; set; }

        public bool bIsSliding { get; set; }

        public float PreviousHitTime { get; set; }

        public Vector PreviousHitNormal { get; set; }

        public float ProjectileGravityScale { get; set; }

        public float Buoyancy { get; set; }

        public float Bounciness { get; set; }

        public float Friction { get; set; }

        public float BounceVelocityStopSimulatingThreshold { get; set; }
    }
}
