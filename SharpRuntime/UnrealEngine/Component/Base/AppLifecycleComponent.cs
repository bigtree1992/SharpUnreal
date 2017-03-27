using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class AppLifecycleComponent : ActorComponent
    {
        #region 设置事件回调

        public void RegAppDeactivate(ActorComponent _this)
        {
            _RegAppDeactivate(NativeHandler, _this.NativeHandler);
        }

        public void RegAppHasReactivated(ActorComponent _this)
        {
            _RegAppHasReactivated(NativeHandler,_this.NativeHandler);
        }

        public void RegAppWillEnterBackground(ActorComponent _this)
        {
            _RegAppWillEnterBackground(NativeHandler, _this.NativeHandler);
        }

        public void RegAppHasEnteredForeground(ActorComponent _this)
        {
            _RegAppHasEnteredForeground(NativeHandler, _this.NativeHandler);
        }

        public void RegAppWillTerminate(ActorComponent _this)
        {
            _RegAppWillTerminate(NativeHandler, _this.NativeHandler);
        }
        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAppDeactivate(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAppHasReactivated(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAppWillEnterBackground(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAppHasEnteredForeground(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAppWillTerminate(IntPtr handler, IntPtr listener);

    }
}
