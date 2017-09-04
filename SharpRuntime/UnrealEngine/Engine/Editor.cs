using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class Editor
    {
        /// <summary>
        /// 监听编辑器开始游戏
        /// </summary>
        public static void OnBeginPIE()
        {
            Log.Debug("[Editor] MonoRuntime GameStart.");
            //清空静态变量中保存的上一次运行的注册对象，防止残留的野指针被调用导致编辑器崩溃
            Event.Clear();
            Timer.Clear();
        }
    }
}
