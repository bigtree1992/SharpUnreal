using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class MovementComponent : ActorComponent
    {
        public Vector Velocity
        {
            get
            {
                return _GetVelocity(NativeHandler);
            }
            set
            {
                _SetVelocity(NativeHandler, value);
            }
        }

        public bool ConstrainToPlane
        {
            get
            {
                return _GetConstrainToPlane(NativeHandler);
            }
            set
            {
                _SetConstrainToPlane(NativeHandler, value);
            }
        }

        public bool SnapToPlaneAtStart
        {
            get
            {
                return _GetSnapToPlaneAtStart(NativeHandler);
            }
        }

        public PlaneConstraintAxisSetting PlaneConstraint
        {
            get
            {
                return _GetPlaneConstraint(NativeHandler);
            }
            set
            {
                _SetPlaneConstraint(NativeHandler, value);
            }
        }

        public Vector PlaneConstraintNormal
        {
            get
            {
                return _GetPlaneConstraintNormal(NativeHandler);
            }
            set
            {
                _SetPlaneConstraintNormal(NativeHandler, value);
            }
        }

        public Vector PlaneConstraintOrigin
        {
            get
            {
                return _GetPlaneConstraintOrigin(NativeHandler);
            }
            set
            {
                _SetPlaneConstraintOrigin(NativeHandler, value);
            }
        }

        public bool UpdateOnlyIfRendered
        {
            get
            {
                return _GetUpdateOnlyIfRendered(NativeHandler);
            }
            set
            {
                _SetUpdateOnlyIfRendered(NativeHandler, value);
            }
        }

        public float GravityZ
        {
            get
            {
                return _GetGravityZ(NativeHandler);
            }
        }

        public float MaxSpeed
        {
            get
            {
                return _GetMaxSpeed(NativeHandler);
            }
        }

        public float MaxSpeedModifier
        {
            get
            {
                return _GetMaxSpeedModifier(NativeHandler);
            }
        }

        public float ModifiedMaxSpeed
        {
            get
            {
                return _GetModifiedMaxSpeed(NativeHandler);
            }
        }

        public void StopMovement()
        {
            _StopMovement(NativeHandler);
        }

        public bool IsExceedingMaxSpeed(float MaxSpeed)
        {
            return _IsExceedingMaxSpeed(NativeHandler, MaxSpeed);
        }

        public void SetPlaneConstraintFromVectors(Vector Forward, Vector Up)
        {
            _SetPlaneConstraintFromVectors(NativeHandler, Forward, Up);
        }

        public Vector ConstrainDirectionToPlane(Vector Direction)
        {
            return _ConstrainDirectionToPlane(NativeHandler, Direction);
        }

        public Vector ConstrainLocationToPlane(Vector Location)
        {
            return _ConstrainLocationToPlane(NativeHandler, Location);
        }

        public Vector ConstrainNormalToPlane(Vector Normal)
        {
            return _ConstrainNormalToPlane(NativeHandler, Normal);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetVelocity(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetVelocity(IntPtr handler, Vector Velocity);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetConstrainToPlane(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetConstrainToPlane(IntPtr handler, bool ConstrainToPlane);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetSnapToPlaneAtStart(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static PlaneConstraintAxisSetting _GetPlaneConstraint(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPlaneConstraint(IntPtr handler, PlaneConstraintAxisSetting PlaneConstraint);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetPlaneConstraintNormal(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPlaneConstraintNormal(IntPtr handler, Vector PlaneConstraintNormal);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetPlaneConstraintOrigin(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPlaneConstraintOrigin(IntPtr handler, Vector PlaneConstraintOrigin);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetUpdateOnlyIfRendered(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetUpdateOnlyIfRendered(IntPtr handler, bool UpdateOnlyIfRendered);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetGravityZ(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetMaxSpeed(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetMaxSpeedModifier(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetModifiedMaxSpeed(IntPtr handler);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _StopMovement(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _IsExceedingMaxSpeed(IntPtr handler, float MaxSpeed);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPlaneConstraintFromVectors(IntPtr handler, Vector Forward, Vector Up);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _ConstrainDirectionToPlane(IntPtr handler, Vector Direction);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _ConstrainLocationToPlane(IntPtr handler, Vector Location);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _ConstrainNormalToPlane(IntPtr handler, Vector Normal);
    }
}
