using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class NetComponent : MonoComponent
    {
        public bool IsServer()
        {
            return _IsServer(NativeHandler);
        }

        public void CallOnServer(int fid)
        {
            _CallOnServer(NativeHandler, fid);
        }

        public void CallOnClient(int fid)
        {
            _CallOnClient(NativeHandler, fid);
        }
        
        public void CallOnAll(int fid)
        {
            _CallOnAll(NativeHandler, fid);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _IsServer(IntPtr handler);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnServer(IntPtr handler, int fid);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnClient(IntPtr handler, int fid);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnAll(IntPtr handler, int fid);

    }
}
