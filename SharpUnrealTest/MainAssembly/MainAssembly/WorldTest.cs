using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试动态加载蓝图，动态加载场景。
    /// </summary>
    public class WorldTest : ActorComponent
    {
        protected override void Initialize()
        {
            Log.Error("[worldtest] 11");
            TestSpawnActor();
        }

        /// <summary>
        /// 测试动态加载蓝图，路径以/开头表示根目录，然后输入文件的全路径
        /// </summary>
        private void TestSpawnActor()
        {
            var trans = new Transform();
            var actor = World.SpwanActor("Resources/Blueprints/Actor3_blueprint", ref trans);
              
        }

        /// <summary>
        /// 测试加载关卡
        /// </summary>
        private void TestLoadLevel()
        {
            //要加载的窗口必须 窗口->关卡 菜单中注册
            World.LoadStreamingLevel("SubMain");
        }
    }
}
