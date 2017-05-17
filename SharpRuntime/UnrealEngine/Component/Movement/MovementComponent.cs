using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public enum PlaneConstraintAxisSetting
    {
        /** Lock movement to a user-defined axis. */
        Custom = 0,
	    /** Lock movement in the X axis. */
	    X = 1,
	    /** Lock movement in the Y axis. */
	    Y = 2,
	    /** Lock movement in the Z axis. */
	    Z = 3,
	    /** Use the global physics project setting. */
	    UseGlobalPhysicsSetting = 4
    } 

    public class MovementComponent : ActorComponent
    {
        public Vector Velocity
        {
            get;
            set;
        }

        public bool ConstrainToPlane
        {
            get;
            set;
        }

        public bool SnapToPlaneAtStart
        {
            get;
        }

        public PlaneConstraintAxisSetting PlaneConstraint
        {
            get;
            set;
        }

        public Vector PlaneConstraintNormal
        {
            get;
            set;
        }

        public Vector PlaneConstraintOrigin
        {
            get;
            set;
        }

        public bool UpdateOnlyIfRendered
        {
            get;
            set;
        }

        public void StopMovement()//Immediately
        {

        }

        public float GravityZ
        {
            get;
        }
    
        public float MaxSpeed
        {
            get;
        }
    
        public float MaxSpeedModifier
        {
            get;
        }

        public float ModifiedMaxSpeed
        {
            get;
        }

        public bool IsExceedingMaxSpeed(float MaxSpeed)
        {
            return false;
        }

        public void SetPlaneConstraintFromVectors(Vector Forward, Vector Up)
        {

        }

        public Vector ConstrainDirectionToPlane(Vector Direction)
        {
            return Vector.ZeroVector;
        }

        public Vector ConstrainLocationToPlane(Vector Location)
        {
            return Vector.ZeroVector;
        }

        public Vector ConstrainNormalToPlane(Vector Normal)
        {
            return Vector.ZeroVector;
        }
    }
}
