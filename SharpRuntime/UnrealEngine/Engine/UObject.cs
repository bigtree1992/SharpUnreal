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
    }

}
