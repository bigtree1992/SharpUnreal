using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class NetComponent : MonoComponent
    {
        public bool IsSelf(bool isServerPlayer)
        {
            if (IsServer())
            {
                return (GetRole() == ENetRole.ROLE_Authority) && (isServerPlayer);
            }
            else
            {
                return GetRole() == ENetRole.ROLE_AutonomousProxy;
            }
        }

        public bool IsServer()
        {
            return _IsServer(NativeHandler);
        }

        public ENetRole GetRole()
        {
            return _GetRole(NativeHandler);
        }

        public void CallOnServer(int fid)
        {
            _CallOnServer(NativeHandler, fid);
        }

        private void CallOnClient(int fid)
        {
            _CallOnClient(NativeHandler, fid);
        }
        
        public void CallOnAll(int fid)
        {
            if (!IsServer())
            {
                Log.Error("[NetComponent] CallOnAll can't call on client!");
                return;
            }
            _CallOnAll(NativeHandler, fid);
        }

        public void CallOnServerWithFloat(int fid, float data)
        {
            _CallOnServerWithFloat(NativeHandler, fid,data);
        }

        private void CallOnClientWithFloat(int fid, float data)
        {
            _CallOnClientWithFloat(NativeHandler, fid, data);
        }

        public void CallOnAllWithFloat(int fid, float data)
        {
            if (!IsServer())
            {
                Log.Error("[NetComponent] CallOnAllWithFloat can't call on client!");
                return;
            }
            _CallOnAllWithFloat(NativeHandler, fid, data);
        }

        public void CallOnServerWithVector(int fid, Vector data)
        {
            _CallOnServerWithVector(NativeHandler, fid,data);
        }

        private void CallOnClientWithVector(int fid, Vector data)
        {
            _CallOnClientWithVector(NativeHandler, fid, data);
        }

        public void CallOnAllWithVector(int fid, Vector data)
        {
            if (!IsServer())
            {
                Log.Error("[NetComponent] CallOnAllWithVector can't call on client!");
                return;
            }
            _CallOnAllWithVector(NativeHandler, fid, data);
        }

        public void CallOnServerWithRotator(int fid, Rotator data)
        {
            _CallOnServerWithRotator(NativeHandler, fid, data);
        }

        private void CallOnClientWithRotator(int fid, Rotator data)
        {
            _CallOnClientWithRotator(NativeHandler, fid, data);
        }

        public void CallOnAllWithRotator(int fid, Rotator data)
        {
            if (!IsServer())
            {
                Log.Error("[NetComponent] CallOnAllWithRotatorr can't call on client!");
                return;
            }
            _CallOnAllWithRotator(NativeHandler, fid, data);
        }

        public void CallOnServerWithRR(int fid, Rotator data,Rotator data2)
        {
            _CallOnServerWithRR(NativeHandler, fid, data,data2);
        }

        private void CallOnClientWithRR(int fid, Rotator data,Rotator data2)
        {
            _CallOnClientWithRR(NativeHandler, fid, data,data2);
        }

        public void CallOnAllWithRR(int fid, Rotator data,Rotator data2)
        {
            if (!IsServer())
            {
                Log.Error("[NetComponent] CallOnAllWithRR can't call on client!");
                return;
            }
            _CallOnAllWithRR(NativeHandler, fid, data,data2);
        }

        public void CallOnServerWithVR(int fid, Vector data, Rotator data2)
        {
            _CallOnServerWithVR(NativeHandler, fid, data, data2);
        }

        private void CallOnClientWithVR(int fid, Vector data, Rotator data2)
        {
            _CallOnClientWithVR(NativeHandler, fid, data, data2);
        }

        public void CallOnAllWithVR(int fid, Vector data, Rotator data2)
        {
            if (!IsServer())
            {
                Log.Error("[NetComponent] CallOnAllWithVR can't call on client!");
                return;
            }
            _CallOnAllWithVR(NativeHandler, fid, data, data2);
        }

        public void CallOnServerWithVV(int fid, Vector data, Vector data2)
        {
            _CallOnServerWithVV(NativeHandler, fid, data, data2);
        }

        private void CallOnClientWithVV(int fid, Vector data, Vector data2)
        {
            _CallOnClientWithVV(NativeHandler, fid, data, data2);
        }

        public void CallOnAllWithVV(int fid, Vector data, Vector data2)
        {
            if (!IsServer())
            {
                Log.Error("[NetComponent] CallOnAllWithRR can't call on client!");
                return;
            }
            _CallOnAllWithVV(NativeHandler, fid, data, data2);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static ENetRole _GetRole(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _IsServer(IntPtr handler);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnServer(IntPtr handler, int fid);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnClient(IntPtr handler, int fid);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnAll(IntPtr handler, int fid);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnServerWithFloat(IntPtr handler, int fid, float data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnClientWithFloat(IntPtr handler, int fid, float data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnAllWithFloat(IntPtr handler, int fid, float data);
        

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnServerWithVector(IntPtr handler, int fid, Vector data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnClientWithVector(IntPtr handler, int fid, Vector data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnAllWithVector(IntPtr handler, int fid, Vector data);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnServerWithRotator(IntPtr handler, int fid, Rotator data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnClientWithRotator(IntPtr handler, int fid, Rotator data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnAllWithRotator(IntPtr handler, int fid, Rotator data);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnServerWithRR(IntPtr handler, int fid, Rotator data, Rotator data2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnClientWithRR(IntPtr handler, int fid, Rotator data, Rotator data2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnAllWithRR(IntPtr handler, int fid, Rotator data, Rotator data2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnServerWithVR(IntPtr handler, int fid, Vector data, Rotator data2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnClientWithVR(IntPtr handler, int fid, Vector data, Rotator data2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnAllWithVR(IntPtr handler, int fid, Vector data, Rotator data2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnServerWithVV(IntPtr handler, int fid, Vector data, Vector data2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnClientWithVV(IntPtr handler, int fid, Vector data, Vector data2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _CallOnAllWithVV(IntPtr handler, int fid, Vector data, Vector data2);
    }
}
