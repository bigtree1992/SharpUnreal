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
            int index = path.LastIndexOf('/');
            string name = path.Substring(index + 1, path.Length - index - 1);
            path = string.Format("/Game/{0}.{1}", path, name);
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
            int index = path.LastIndexOf('/');
            string name = path.Substring(index + 1, path.Length - index - 1);
            path = string.Format("/Game/{0}.{1}", path, name);
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

        /// <summary>
        /// 进行内存垃圾回收 
        /// </summary>
        public static void GC()
        {
            _GC();
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _LoadMaterial(string path);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _LoadTexture(string path);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _GC();
    }
}
