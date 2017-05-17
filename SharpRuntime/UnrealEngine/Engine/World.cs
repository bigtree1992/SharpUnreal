using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class World
    {
        /// <summary>
        /// 获取当前的关卡名字
        /// </summary>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static string GetCurrentLevel();

        /// <summary>
        /// 流式加载场景
        /// </summary>
        /// <param name="name"></param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void LoadStreamingLevel(string name);

        /// <summary>
        /// 流式卸载场景
        /// </summary>
        /// <param name="name"></param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void UnLoadStreamingLevel(string name);

        /// <summary>
        /// 根据路径生成一个Actor
        /// </summary>
        /// <param name="path"></param>
        /// <param name="trans"></param>
        /// <returns></returns>
        public static Actor SpwanActor(string path, ref Transform trans)
        {
            int index = path.LastIndexOf('/');
            string name = path.Substring(index + 1, path.Length - index - 1);
            path = string.Format("/Game/{0}.{1}_C", name, name);           
            var handler = _SpwanActor(path, ref trans);
            if (handler.ToInt64() == 0)
            {
                return null;
            }
            return new Actor(handler);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _SpwanActor(string path, ref Transform trans);        
    }

}
