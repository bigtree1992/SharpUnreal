using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class ProjectileMovementComponent : MovementComponent
    {
        public float InitialSpeed
        {
            get
            {
                return _GetInitialSpeed(NativeHandler);
            }
            set
            {
                _SetInitialSpeed(NativeHandler, value);
            }
        }

        public bool RotationFollowsVelocity
        {
            get
            {
                return _GetRotationFollowsVelocity(NativeHandler);
            }
            set
            {
                _SetRotationFollowsVelocity(NativeHandler, value);
            }
        }

        public bool ShouldBounce
        {
            get
            {
                return _GetShouldBounce(NativeHandler);
            }
            set
            {
                _SetShouldBounce(NativeHandler, value);
            }
        }

        public bool InitialVelocityInLocalSpace
        {
            get
            {
                return _GetInitialVelocityInLocalSpace(NativeHandler);
            }
            set
            {
                _SetInitialVelocityInLocalSpace(NativeHandler, value);
            }
        }

        public bool ForceSubStepping
        {
            get
            {
                return _GetForceSubStepping(NativeHandler);
            }
            set
            {
                _SetForceSubStepping(NativeHandler, value);
            }
        }

        public bool IsHomingProjectile
        {
            get
            {
                return _GetIsHomingProjectile(NativeHandler);
            }
            set
            {
                _SetIsHomingProjectile(NativeHandler, value);
            }
        }

        public bool BounceAngleAffectsFriction
        {
            get
            {
                return _GetBounceAngleAffectsFriction(NativeHandler);
            }
            set
            {
                _SetBounceAngleAffectsFriction(NativeHandler, value);
            }
        }

        public bool IsSliding
        {
            get
            {
                return _GetIsSliding(NativeHandler);
            }
            set
            {
                _SetIsSliding(NativeHandler, value);
            }
        }

        public float PreviousHitTime
        {
            get
            {
                return _GetPreviousHitTime(NativeHandler);
            }
            set
            {
                _SetPreviousHitTime(NativeHandler, value);
            }
        }

        public Vector PreviousHitNormal
        {
            get
            {
                return _GetPreviousHitNormal(NativeHandler);
            }
            set
            {
                _SetPreviousHitNormal(NativeHandler, value);
            }
        }

        public float ProjectileGravityScale
        {
            get
            {
                return _GetProjectileGravityScale(NativeHandler);
            }
            set
            {
                _SetProjectileGravityScale(NativeHandler, value);
            }
        }

        public float Buoyancy
        {
            get
            {
                return _GetBuoyancy(NativeHandler);
            }
            set
            {
                _SetBuoyancy(NativeHandler, value);
            }
        }

        public float Bounciness
        {
            get
            {
                return _GetBounciness(NativeHandler);
            }
            set
            {
                _SetBounciness(NativeHandler, value);
            }
        }

        public float Friction
        {
            get
            {
                return _GetFriction(NativeHandler);
            }
            set
            {
                _SetFriction(NativeHandler, value);
            }
        }

        public float BounceVelocityStopSimulatingThreshold
        {
            get
            {
                return _GetBounceVelocityStopSimulatingThreshold(NativeHandler);
            }
            set
            {
                _SetBounceVelocityStopSimulatingThreshold(NativeHandler, value);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetInitialSpeed(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetInitialSpeed(IntPtr handler, float InitialSpeed);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetRotationFollowsVelocity(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetRotationFollowsVelocity(IntPtr handler, bool RotationFollowsVelocity);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetShouldBounce(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetShouldBounce(IntPtr handler, bool ShouldBounce);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetInitialVelocityInLocalSpace(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetInitialVelocityInLocalSpace(IntPtr handler, bool InitialVelocityInLocalSpace);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetForceSubStepping(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetForceSubStepping(IntPtr handler, bool ForceSubStepping);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsHomingProjectile(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetIsHomingProjectile(IntPtr handler, bool IsHomingProjectile);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetBounceAngleAffectsFriction(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBounceAngleAffectsFriction(IntPtr handler, bool BounceAngleAffectsFriction);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsSliding(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetIsSliding(IntPtr handler, bool IsSliding);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetPreviousHitTime(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPreviousHitTime(IntPtr handler, float PreviousHitTime);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetPreviousHitNormal(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPreviousHitNormal(IntPtr handler, Vector PreviousHitNormal);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetProjectileGravityScale(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetProjectileGravityScale(IntPtr handler, float ProjectileGravityScale);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetBuoyancy(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBuoyancy(IntPtr handler, float Buoyancy);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetBounciness(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBounciness(IntPtr handler, float Bounciness);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetFriction(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetFriction(IntPtr handler, float Friction);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetBounceVelocityStopSimulatingThreshold(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBounceVelocityStopSimulatingThreshold(IntPtr handler, float BounceVelocityStopSimulatingThreshold);

    }
}
