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
            TestSpawnActor();
        }

        /// <summary>
        /// 测试动态加载蓝图，路径以/开头表示根目录，然后输入文件的全路径
        /// </summary>
        private void TestSpawnActor()
        {
            var trans = new Transform();
            var actor = World.SpwanActor("/Actor3_Blueprint", ref trans);
            var init = actor.GetMonoComponent() as InitTest;
            //测试初始化组件值，会在Initialize之后调用，BeginPlay之前调用
            init.TestValue = 100;

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
