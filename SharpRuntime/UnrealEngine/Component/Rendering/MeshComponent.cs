using System;
using System.Collections.Generic;

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

        }

        /// <summary>
        /// 在Mesh的所有材质上设置参数
        /// </summary>
        /// <param name="name"></param>
        /// <param name="value"></param>
        public void SetVectorParameter(string name, LinearColor value)
        {

        }
    }
}
