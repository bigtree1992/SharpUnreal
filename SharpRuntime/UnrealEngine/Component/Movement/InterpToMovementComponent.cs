using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class InterpToMovementComponent : MovementComponent
    {
        public void RestartMovement(float InitialDirection)
        {
            _RestartMovement(NativeHandler, InitialDirection);
        }


        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RestartMovement(IntPtr handler, float InitialDirection);
    }
}
