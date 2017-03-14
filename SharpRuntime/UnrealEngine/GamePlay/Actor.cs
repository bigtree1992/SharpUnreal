using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace UnrealEngine
{
    public class Actor
    {
        /// <summary>
        /// 设置跟获取可见性
        /// </summary>
        public bool Visible
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        /// <summary>
        /// 设置跟获取是否隐藏
        /// </summary>
        public bool HiddenInGame
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        /// <summary>
        /// 查找Actor上的指定类型的组件
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        public T GetComponent<T>() where T : ActorComponent 
        {
            return GetComponent(typeof(T).Name) as T;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern ActorComponent GetComponent(string type);

        /// <summary>
        /// 根据Tag查找Actor指定类型的组件
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="tag"></param>
        /// <returns></returns>
        public T GetComponentByTag<T>(string tag) where T : ActorComponent
        {
            return GetComponentByTag(typeof(T).Name,tag) as T;
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern ActorComponent GetComponentByTag(string type, string tag);

        /// <summary>
        /// 获取当前世界的引用
        /// </summary>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern UWorld GetWorld();

        /// <summary>
        /// 销毁这个Actor
        /// </summary>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Destroy();
    }
}
