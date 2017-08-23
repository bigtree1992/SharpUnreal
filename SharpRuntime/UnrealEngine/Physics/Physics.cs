using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;


namespace UnrealEngine
{
    public class Physics
    {
        /// <summary>
        /// 射线检测
        /// </summary>
        public static Vector LineTraceSingleGetPoint(Vector start,Vector end,CollisionChannel channel)
        {
            return _LineTraceSingleGetPoint(start, end, channel);
        }

        /// <summary>
        /// 球形碰撞检测
        /// </summary>
        public static void SphereTrace()
        {

        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _LineTraceSingleGetPoint(Vector start, Vector end, CollisionChannel channel);

    }
}
