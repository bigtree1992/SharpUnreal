using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class PawnMovementComponent : NavMovementComponent
    {
        public Vector PendingInputVector
        {
            get
            {
                return _GetPendingInputVector(NativeHandler);
            }
        }

        public Vector LastInputVector
        {
            get
            {
                return _GetLastInputVector(NativeHandler);
            }
        }

        public Vector ConsumeInputVector
        {
            get
            {
                return _GetConsumeInputVector(NativeHandler);
            }
        }

        public bool IsMoveInputIgnored
        {
            get
            {
                return _GetIsMoveInputIgnored(NativeHandler);
            }
        }

        public void AddInputVector(Vector WorldVector, bool bForce)
        {
            _AddInputVector(NativeHandler, WorldVector, bForce);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetPendingInputVector(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetLastInputVector(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetConsumeInputVector(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsMoveInputIgnored(IntPtr handler);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddInputVector(IntPtr handler, Vector WorldVector, bool bForce);
    }
}
