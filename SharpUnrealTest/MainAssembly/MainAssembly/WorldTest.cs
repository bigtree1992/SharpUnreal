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
            TestError();
        }

        /// <summary>
        /// 测试动态加载蓝图，路径以/开头表示根目录，然后输入文件的全路径
        /// </summary>
        private void TestSpawnActor()
        {
            var trans = new Transform();
            var actor = World.SpwanActor("Resources/Blueprints/Actor3_blueprint", ref trans);

            var cube = actor.GetComponentByTag<StaticMeshComponent>("Cube");
            if (cube == null)
            {
                Log.Error("[WorldTest] cube is null");
            }
            else
            {
                cube.Visible = true;
            }

            var sphere = actor.GetComponentByTag<StaticMeshComponent>("Sphere");
            if (sphere == null)
            {
                Log.Error("[WorldTest] sphere is null");
            }
            else
            {
            }

            actor.Root.LocalPosition = new Vector(1000, 1000, 1000);
            actor.Root.LocalScale = new Vector(5, 5, 5);
            var init = actor.GetMonoComponent() as InitTest;
            //测试初始化组件值，会在initialize之后调用，beginplay之前调用
            init.TestValue = 100;
            init.SendEvent("TestEventInt", 1881);
            init.SendEvent("TestEventString", "string");

            Log.Error("[WorldTest] actorname:" + actor.Name);
            //actor.Destroy();
            TimerTest.DelayInvoke(1.0f, () => {
                init.SendEvent("TestEventString", "timerstring");
                sphere.Visible = false;

            });
        }

        private void TestError()
        {
            try
            {
                StaticMeshComponent mesh = null;
                if(mesh == null)
                {
                    Log.Error("null");
                }
                else
                {
                    Log.Error("not null");
                }
            }
            catch(Exception e)
            {

            }
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
