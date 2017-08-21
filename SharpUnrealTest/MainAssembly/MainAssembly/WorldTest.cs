using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试动态加载蓝图，动态加载场景。
    /// </summary>
    public class WorldTest : MonoComponent
    {
        private float timer = 0.0f;

        protected override void Initialize()
        {
            base.Initialize();
            CanEverTick = false;
            Event.AddListener("TestListener", Listener);
        }

        public void Listener()
        {
            Log.Error("[WorldTest] Listener");
        }

        protected override void Tick(float dt)
        {
            timer += dt;
            Log.Error("[WorldTest] Tick timer" + timer);
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
                cube.Activited = false;
            }

            var sphere = actor.GetComponentByTag<StaticMeshComponent>("Sphere");
            if (sphere == null)
            {
                Log.Error("[WorldTest] sphere is null");
            }
            else
            {
                sphere.Visible = true;
                sphere.Activited = false;
            }

            actor.Root.LocalPosition = new Vector(1000, 1000, 1000);
            actor.Root.LocalScale = new Vector(5, 5, 5);
            var seq = actor.Sequencer;
            if(seq == null)
            {
                Log.Error("[WorldTest] Sequencer is null");
            }
            else
            {
                Log.Error("[WorldTest] Sequencer name:" + seq.GetType());
            }

            var init = actor.GetMonoComponent() as InitTest;
            init.Activited = false;
            //测试初始化组件值，会在initialize之后调用，beginplay之前调用
            init.TestValue = 100;
            init.SendEvent("TestEventInt", 1881);
            init.SendEvent("TestEventString", "string");

            //actor.Destroy();
            TimerTest.DelayInvoke(1.0f, () => {
                init.SendEvent("TestEventString", "timerstring");
            });
        }

        /// <summary>
        /// 测试加载关卡
        /// </summary>
        private void TestLoadLevel()
        {
            Log.Error("[WorldTest] CurrentLevelName:" + World.GetCurrentLevel());
            //要加载的窗口必须 窗口->关卡 菜单中注册
            World.LoadStreamingLevel("SubMain");
            TimerTest.DelayInvoke(5, () => {
                TestUnLoadLevel();
            });
        }

        private void TestUnLoadLevel()
        {
            World.UnLoadStreamingLevel("SubMain");
        }
    }
}
