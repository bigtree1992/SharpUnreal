using System;
using System.Runtime.CompilerServices;


namespace UnrealEngine
{
    public class Actor : UObject
    {
        public Actor()
        {
        }

        public Actor(IntPtr handler)
        {
            m_NativeHandler = handler;
        }
        
        /// <summary>
        /// 设置跟获取是否隐藏
        /// </summary>
        public bool HiddenInGame
        {
            get { return _GetHiddenInGame(m_NativeHandler); }
            set { _SetHiddenInGame(m_NativeHandler, value); }
        }

        /// <summary>
        /// 获取场景的根组件
        /// </summary>
        private SceneComponent m_Root;
        public SceneComponent Root
        {
            get
            {
                if (m_Root == null)
                {
                    var root = new SceneComponent();
                    root.NativeHandler = _GetSceneComponent(m_NativeHandler);
                    m_Root = root;
                }
                return m_Root;
            }
            set { _SetSceneComponent(m_NativeHandler, value.NativeHandler); }
        }

        public Sequencer Sequencer
        {
            get
            {
                var sequencer = new Sequencer();
                sequencer.NativeHandler = _GetSequencer(m_NativeHandler);
                return sequencer;
            }
        }

        /// <summary>
        /// 查找Actor上的指定类型的组件
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        public T GetComponent<T>() where T : ActorComponent 
        {
            var ret = new ActorComponent() as T;
            ret.NativeHandler = _GetComponent(m_NativeHandler, typeof(T).Name);
            return ret;
        }

        /// <summary>
        /// 根据Tag查找Actor指定类型的组件
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="tag"></param>
        /// <returns></returns>
        public T GetComponentByTag<T>(string tag) where T : ActorComponent
        {
            var ret = new ActorComponent() as T;
            ret.NativeHandler = _GetComponentByTag(m_NativeHandler, typeof(T).Name, tag);
            return ret;               
        }
        
        /// <summary>
        /// 销毁这个Actor
        /// </summary>
        public void Destroy()
        {
            _Destroy(m_NativeHandler);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _GetSequencer(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetHiddenInGame(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetHiddenInGame(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _GetSceneComponent(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetSceneComponent(IntPtr handler, IntPtr value);
        [MethodImpl(MethodImplOptions.InternalCall)]      
        private extern static IntPtr _GetComponent(IntPtr handler, string type);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _GetComponentByTag(IntPtr handler, string type, string tag);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _Destroy(IntPtr handler);
    }
}
