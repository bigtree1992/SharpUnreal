using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class UObject
    {
        private IntPtr m_NativeHandler;

        public IntPtr NativeHandler
        {
            get { return m_NativeHandler; }
            set { m_NativeHandler = value; }
        }

        /// <summary>
        /// 是否被垃圾回收器的根节点引用
        /// </summary>
        public bool IsRooted
        {
            get
            {
                return _GetIsRooted(NativeHandler);
            }
            set
            {
                _SetIsRooted(NativeHandler, value);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsRooted(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetIsRooted(IntPtr handler, bool value);
    }

}
