using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class Resource
    {
        /// <summary>
        /// 根据路径加载一个材质
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        public static Material LoadMaterial(string path)
        {
            path = "/Game" + path;
            var handler = _LoadMaterial(path);
            if (handler.ToInt64() != 0)
            {
                var mat = new Material();
                mat.NativeHandler = handler;
                return mat;
            }
            else
            {
                return null;
            }
        }

        /// <summary>
        /// 根据路径加载一个贴图
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        public static Texture LoadTexture(string path)
        {
            path = "/Game" + path;
            var handler = _LoadTexture(path);
            if (handler.ToInt64() != 0)
            {
                var texture = new Texture();
                texture.NativeHandler = handler;
                return texture;
            }
            else
            {
                return null;
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _LoadMaterial(string path);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _LoadTexture(string path);
    }
}
