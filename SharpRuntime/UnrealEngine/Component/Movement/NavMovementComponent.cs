using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class NavMovementComponent : MovementComponent
    {
        public bool CanCrouch
        {
            get
            {
                return _GetCanCrouch(NativeHandler);
            }
            set
            {
                _SetCanCrouch(NativeHandler, value);
            }
        }

        public bool CanJump
        {
            get
            {
                return _GetCanJump(NativeHandler);
            }
            set
            {
                _SetCanJump(NativeHandler, value);
            }
        }

        public bool CanWalk
        {
            get
            {
                return _GetCanWalk(NativeHandler);
            }
            set
            {
                _SetCanWalk(NativeHandler, value);
            }
        }

        public bool CanSwim
        {
            get
            {
                return _GetCanSwim(NativeHandler);
            }
            set
            {
                _SetCanSwim(NativeHandler, value);
            }
        }

        public bool CanFly
        {
            get
            {
                return _GetCanFly(NativeHandler);
            }
            set
            {
                _SetCanFly(NativeHandler, value);
            }
        }

        public float AgentRadius
        {
            get
            {
                return _GetAgentRadius(NativeHandler);
            }
            set
            {
                _SetAgentRadius(NativeHandler, value);
            }
        }

        public float AgentHeight
        {
            get
            {
                return _GetAgentHeight(NativeHandler);
            }
            set
            {
                _SetAgentHeight(NativeHandler, value);
            }
        }

        public float AgentStepHeight
        {
            get
            {
                return _GetAgentStepHeight(NativeHandler);
            }
            set
            {
                _SetAgentStepHeight(NativeHandler, value);
            }
        }

        public float NavWalkingSearchHeightScale
        {
            get
            {
                return _GetNavWalkingSearchHeightScale(NativeHandler);
            }
            set
            {
                _SetNavWalkingSearchHeightScale(NativeHandler, value);
            }
        }

        public bool IsCrouching
        {
            get
            {
                return _GetIsCrouching(NativeHandler);
            }
        }

        public bool IsFalling
        {
            get
            {
                return _GetIsFalling(NativeHandler);
            }
        }

        public bool IsMovingOnGround
        {
            get
            {
                return _GetIsMovingOnGround(NativeHandler);
            }
        }

        public bool IsSwimming
        {
            get
            {
                return _GetIsSwimming(NativeHandler);
            }
        }

        public bool IsFlying
        {
            get
            {
                return _GetIsFlying(NativeHandler);
            }
        }

        public void StopActiveMovement()
        {
            _StopActiveMovement(NativeHandler);
        }

        public void StopMovementKeepPathing()
        {
            _StopMovementKeepPathing(NativeHandler);
        }

        public float FixedBrakingDistance
        {
            set
            {
                _SetFixedBrakingDistance(NativeHandler, value);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetCanCrouch(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCanCrouch(IntPtr handler, bool CanCrouch);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetCanJump(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCanJump(IntPtr handler, bool CanJump);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetCanWalk(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCanWalk(IntPtr handler, bool CanWalk);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetCanSwim(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCanSwim(IntPtr handler, bool CanSwim);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetCanFly(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCanFly(IntPtr handler, bool CanFly);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetAgentRadius(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetAgentRadius(IntPtr handler, float AgentRadius);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetAgentHeight(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetAgentHeight(IntPtr handler, float AgentHeight);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetAgentStepHeight(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetAgentStepHeight(IntPtr handler, float AgentStepHeight);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetNavWalkingSearchHeightScale(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetNavWalkingSearchHeightScale(IntPtr handler, float NavWalkingSearchHeightScale);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsCrouching(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsFalling(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsMovingOnGround(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsSwimming(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsFlying(IntPtr handler);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _StopActiveMovement(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _StopMovementKeepPathing(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetFixedBrakingDistance(IntPtr handler,float distance);
    }
}
