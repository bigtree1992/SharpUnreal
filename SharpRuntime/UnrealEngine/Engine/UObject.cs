using System;
using System.Collections.Generic;

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
            //ToDo
            get;
            set;
        }
    }

}
