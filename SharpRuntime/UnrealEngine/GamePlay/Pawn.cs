using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class Pawn : Actor
    {
        public PawnMovementComponent MovementComponent
        {
            get
            {
                var handle = _GetMovementComponent(NativeHandler);
                if (handle.ToInt64() != 0)
                {
                    var comp = new PawnMovementComponent();
                    comp.NativeHandler = handle;
                    return comp;
                }
                else
                {
                    return null;
                }
                
            }
        }

        public bool UseCtrlRotationPith
        {
            get
            {
                return _GetUseCtrlRotationPith(NativeHandler);
            }
            set
            {
                _SetUseCtrlRotationPith(NativeHandler, value);
            }
        }

        public bool UseCtrlRotationYaw
        {
            get
            {
                return _GetUseCtrlRotationYaw(NativeHandler);
            }
            set
            {
                _SetUseCtrlRotationYaw(NativeHandler, value);
            }
        }

        public bool UseCtrlRotationRoll
        {
            get
            {
                return _GetUseCtrlRotationRoll(NativeHandler);
            }
            set
            {
                _SetUseCtrlRotationRoll(NativeHandler, value);
            }
        }

        public bool CanAffectNavigationGeneration
        {
            get
            {
                return _GetCanAffectNavigationGeneration(NativeHandler);
            }
            set
            {
                _SetCanAffectNavigationGeneration(NativeHandler, value);
            }
        }

        public float BaseEyeHeight
        {
            get
            {
                return _GetBaseEyeHeight(NativeHandler);
            }
            set
            {
                _SetBaseEyeHeight(NativeHandler, value);
            }
        }

        public bool IsControlled
        {
            get
            {
                return _GetIsControlled(NativeHandler);
            }
        }

        public Controller Controller
        {
            get
            {
                var handle = _GetController(NativeHandler);
                if (handle.ToInt64() != 0)
                {
                    var ctrl = new Controller();
                    ctrl.NativeHandler = handle;
                    return ctrl;
                }
                else
                {
                    return null;
                }
                
            }
        }

        public Rotator ControllerRatator
        {
            get
            {
                return _GetControllerRatator(NativeHandler);
            }
        }

        public Vector NavAgentLocatioin
        {
            get
            {
                return _GetNavAgentLocatioin(NativeHandler);
            }
        }

        public Rotator BaseAimRotaion
        {
            get
            {
                return _GetBaseAimRotaion(NativeHandler);
            }
        }

        public Vector PendingMovementInputVector
        {
            get
            {
                return _GetPendingMovementInputVector(NativeHandler);
            }
        }

        public Vector LastMovementInputVector
        {
            get
            {
                return _GetLastMovementInputVector(NativeHandler);
            }
        }

        public Vector ConsumeMovementInputVector
        {
            get
            {
                return _GetConsumeMovementInputVector(NativeHandler);
            }
        }

        public bool IsMoveInputIgnored
        {
            get
            {
                return _GetIsMoveInputIgnored(NativeHandler);
            }
        }

        public void AddMovementInput(Vector worldDir, float scaleValue, bool force)
        {
            _AddMovementInput(NativeHandler, worldDir, scaleValue, force);
        }

        public void AddControllerPitchInput(float Val)
        {
            _AddControllerPitchInput(NativeHandler, Val);
        }

        public void AddControllerYawInput(float Val)
        {
            _AddControllerYawInput(NativeHandler, Val);
        }

        public void AddControllerRollInput(float Val)
        {
            _AddControllerRollInput(NativeHandler, Val);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _GetMovementComponent(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetUseCtrlRotationPith(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetUseCtrlRotationPith(IntPtr handler, bool UseCtrlRotationPith);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetUseCtrlRotationYaw(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetUseCtrlRotationYaw(IntPtr handler, bool UseCtrlRotationYaw);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetUseCtrlRotationRoll(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetUseCtrlRotationRoll(IntPtr handler, bool UseCtrlRotationRoll);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetCanAffectNavigationGeneration(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCanAffectNavigationGeneration(IntPtr handler, bool CanAffectNavigationGeneration);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetBaseEyeHeight(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBaseEyeHeight(IntPtr handler, float BaseEyeHeight);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsControlled(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _GetController(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Rotator _GetControllerRatator(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetNavAgentLocatioin(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Rotator _GetBaseAimRotaion(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetPendingMovementInputVector(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetLastMovementInputVector(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetConsumeMovementInputVector(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsMoveInputIgnored(IntPtr handler);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddMovementInput(IntPtr handler, Vector worldDir, float scaleValue, bool force);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddControllerPitchInput(IntPtr handler, float Val);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddControllerYawInput(IntPtr handler, float Val);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddControllerRollInput(IntPtr handler, float Val);
    }
}
