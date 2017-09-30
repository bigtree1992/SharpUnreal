using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class InputComponent : ActorComponent
    {
        public float GetAxisValue(int index)
        {
            return _GetAxisValue(NativeHandler,index);
        }
        
        public void BindAxis(string axis, int index)
        {
            _BindAxis(NativeHandler, axis, index);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static float _GetAxisValue(IntPtr handler,int inedx);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void _BindAxis(IntPtr handler,string axis,int index);
    }
}
