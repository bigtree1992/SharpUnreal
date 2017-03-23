using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class AppLifecycleComponent : ActorComponent
    {
        #region 设置事件回调

        public void RegAppDeactivate(ActorComponent _this)
        {
            _RegAppDeactivate(_this.NativeHandler);
        }

        public void RegAppHasReactivated(ActorComponent _this)
        {
            _RegAppHasReactivated(_this.NativeHandler);
        }

        public void RegAppWillEnterBackground(ActorComponent _this)
        {
            _RegAppWillEnterBackground(_this.NativeHandler);
        }

        public void RegAppHasEnteredForeground(ActorComponent _this)
        {
            _RegAppHasEnteredForeground(_this.NativeHandler);
        }

        public void RegAppWillTerminate(ActorComponent _this)
        {
            _RegAppWillTerminate(_this.NativeHandler);
        }
        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAppDeactivate(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAppHasReactivated(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAppWillEnterBackground(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAppHasEnteredForeground(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegAppWillTerminate(IntPtr handler);

    }
}
