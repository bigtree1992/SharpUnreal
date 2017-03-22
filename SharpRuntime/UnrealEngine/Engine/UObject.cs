using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
