using System;
using System.Collections.Generic;


namespace UnrealEngine
{
    public class NavMovementComponent : MovementComponent
    {        
        public bool CanCrouch
        {
            get;
            set;
        }

        public bool CanJump
        {
            get;
            set;
        }

        public bool CanWalk
        {
            get;
            set;
        }

        public bool CanSwim
        {
            get;
            set;
        }

        public bool CanFly
        {
            get;
            set;
        }

        public float AgentRadius
        {
            get;
            set;
        }

        public float AgentHeight
        {
            get;
            set;
        }

        public float AgentStepHeight
        {
            get;
            set;
        }

        public float NavWalkingSearchHeightScale
        {
            get;
            set;
        }

        public float FixedPathBrakingDistance
        {
            get;
            set;
        }    
    
        public bool UpdateNavAgentWithOwnersCollision
        {
            get;
            set;
        }

        public bool UseAccelerationForPaths
        {
            get;
            set;
        }

        public bool UseFixedBrakingDistanceForPaths
        {
            get;
            set;
        }

        public void StopActiveMovement()
        {

        }

        public void StopMovementKeepPathing()
        {

        }

        public bool IsCrouching
        {
            get;
        }
    
        public bool IsFalling
        {
            get;
        }

        public bool IsMovingOnGround
        {
            get;
        }

        public bool IsSwimming
        {
            get;
        }

        public bool IsFlying
        {
            get;
        }
    }
}
