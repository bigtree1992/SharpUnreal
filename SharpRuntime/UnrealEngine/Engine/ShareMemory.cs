using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class ShareMemory
    {
        /// <summary>
        /// 创建共享内存
        /// </summary>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void _CreateMemory(string name, int size);

        /// <summary>
        /// 销毁共享内存
        /// </summary>
        /// <param name="name"></param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void _DestroyMemory();

        /// <summary>
        /// 写数据到共享内存
        /// </summary>
        /// <param name="name"></param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void _WriteMemory(string data);

        /// <summary>
        /// 写数据到共享内存
        /// </summary>
        /// <param name="name"></param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void _WriteMemoryWithData(Vector data, Rotator data2, Vector data3);

        /// <summary>
        /// 读数据从共享内存
        /// </summary>
        /// <param name="name"></param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static string _ReadMemory();
    }
}
