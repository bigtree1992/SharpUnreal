using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    /// <summary>
    /// MeshComponent代表了可以渲染一组三角形的类
    /// </summary>
    public class MeshComponent : PrimitiveComponent
    {    
        /// <summary>
        /// 在Mesh的所有材质上设置参数
        /// </summary>
        /// <param name="name"></param>
        /// <param name="value"></param>
        public void SetScalarParameter(string name, float value)
        {
            _SetScalarParameter(m_NativeHandler,name, value);
        }

        /// <summary>
        /// 在Mesh的所有材质上设置参数
        /// </summary>
        /// <param name="name"></param>
        /// <param name="value"></param>
        public void SetVectorParameter(string name, LinearColor value)
        {
            _SetVectorParameter(m_NativeHandler, name, value);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetScalarParameter(IntPtr handler, string name, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetVectorParameter(IntPtr handler, string name, LinearColor value);
    }
}
