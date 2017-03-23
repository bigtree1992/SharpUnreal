using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class UObject
    {
        protected IntPtr m_NativeHandler;

        public IntPtr NativeHandler
        {
            get;set;
        }
    }

}
