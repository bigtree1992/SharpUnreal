using System;
using System.Collections.Generic;


namespace UnrealEngine
{
    /// <summary>
    /// 表示一个材质
    /// </summary>
    public class Material : UObject
    {
        public Material(IntPtr handler)
        {
            m_NativeHandler = handler;
        }
    }
}
