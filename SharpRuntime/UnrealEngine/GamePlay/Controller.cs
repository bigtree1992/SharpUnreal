using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class Controller : Actor
    {
        public Rotator ControllerRotator
        {
            get
            {
                return _GetControllerRotator(NativeHandler);
            }
            set
            {
                _SetControllerRotator(NativeHandler, value);
            }
        }

        public AIController AsAIController()
        {
            AIController ai = this as AIController;
            if(ai == null)
            {
                ai = new AIController();
                ai.NativeHandler = this.NativeHandler;
                return ai;
            }
            else
            {
                return ai;
            }
        }

        public bool IgnoreMoveInput
        {
            get
            {
                return _GetIgnoreMoveInput(NativeHandler);
            }
            set
            {
                _SetIgnoreMoveInput(NativeHandler, value);
            }
        }

        public bool IgnoreLookInput
        {
            get
            {
                return _GetIgnoreLookInput(NativeHandler);
            }
            set
            {
                _SetIgnoreLookInput(NativeHandler, value);
            }
        }

        public void SetInitialLocationAndRotation(Vector NewLocation, Rotator NewRotation)
        {
            _SetInitialLocationAndRotation(NativeHandler, NewLocation, NewRotation);
        }

        public bool LineOfSightTo(Actor Other, Vector ViewPoint, bool bAlternateChecks)
        {
            return _LineOfSightTo(NativeHandler, Other.NativeHandler, ViewPoint, bAlternateChecks);
        }

        public void StopMovement()
        {
            _StopMovement(NativeHandler);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Rotator _GetControllerRotator(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetControllerRotator(IntPtr handler, Rotator ControllerRotator);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIgnoreMoveInput(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetIgnoreMoveInput(IntPtr handler, bool IgnoreMoveInput);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIgnoreLookInput(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetIgnoreLookInput(IntPtr handler, bool IgnoreLookInput);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetInitialLocationAndRotation(IntPtr handler, Vector NewLocation, Rotator NewRotation);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _LineOfSightTo(IntPtr handler, IntPtr Other, Vector ViewPoint, bool bAlternateChecks);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _StopMovement(IntPtr handler);
    }
}
