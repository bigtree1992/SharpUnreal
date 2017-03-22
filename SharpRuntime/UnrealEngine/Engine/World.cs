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
        public static Actor SpwanActor(string path, Transform trans)
        {
            return new Actor(_SpwanActor(path, trans));
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _SpwanActor(string path, Transform trans);

        /// <summary>
        /// 在世界中根据Tag找到Actor
        /// </summary>
        /// <param name="tag"></param>
        /// <returns></returns>
        public Actor FindByTag(string tag)
        {
            return null;
        }

        /// <summary>
        /// 根据路径加载一个材质
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        public Material LoadMaterial(string path)
        {
            return null;
        }
    }

}
