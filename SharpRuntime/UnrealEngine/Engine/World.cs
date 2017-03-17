using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace UnrealEngine
{
    public class UWorld
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
        /// 根据Tag在世界中寻找Actor
        /// </summary>
        /// <param name="tag"></param>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static Actor FindActorByTag(string tag);

        /// <summary>
        /// 根据Tag在世界中寻找Actor
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="tag"></param>
        /// <returns></returns>
        public static T FindActorByTag<T>(string tag) where T : Actor
        {
            return FindActorByTag(tag) as T;
        }

        /// <summary>
        /// 在世界中查找指定类型的组件
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        public static T FindComponent<T>()
        {
            return default(T);
        }

        public static T[] FindComponents<T>()
        {
            return default(T[]);
        }

        public static T FindComponentByTag<T>(string tag)
        {
            return default(T);
        }

        public static T[] FindComponentsByTag<T>(string tag)
        {
            return default(T[]);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static Actor SpwanActor(string path, Transform trans);
    }

}
