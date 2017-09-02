using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 组件生命周期测试
    /// </summary>
    public class ComponentLifeTest : MonoComponent
    {
        protected override void OnRegister()
        {
            Log.Error("[ComponentLifeTest] OnRegister");
        }

        protected override void OnUnregister()
        {
            Log.Error("[ComponentLifeTest] OnUnregister");
        }

        protected override void Initialize()
        {
            Log.Error("[ComponentLifeTest] Initialize");
            if (Actor.Root.HasTag("Hello"))
            {
                Log.Error("[ComponentLifeTest] True! Hello!");
            }
            else
            {
                Log.Error("[ComponentLifeTest] False! Hello!");
            }


            var testint = Actor.FindIntProperty("TestInt");
            var TestString = Actor.FindStringProperty("TestString");
            var TestFloat = Actor.FindFloatProperty("TestFloat");
            if (testint == null)
            {
                Log.Error("can not find property TestInt");
            }
            else
            {
                Log.Error(testint.Value.ToString());
            }

            if (TestString == null)
            {
                Log.Error("can not find property TestString");
            }
            else
            {
                Log.Error(TestString.Value.ToString());
            }

            if (TestFloat == null)
            {
                Log.Error("can not find property TestFloat");
            }
            else
            {
                Log.Error(TestFloat.Value.ToString());
            }

            //Actor.Root.LocalPosition = 
            //    Actor.Root.LocalPosition + new Vector(0, 0, 100);
            //Log.Error("[ComponentLifeTest] Set Vector");

            //Log.Error("[ComponentLifeTest] localQuat:" + Actor.Root.LocalRotation + ",Quat:" + Actor.Root.Rotation);
            //Log.Error("[ComponentLifeTest] scale:" + Actor.Root.Scale + ",localScale:" + Actor.Root.LocalScale);
            //Actor.Root.LocalRotation = new Rotator(0, 0, 0);
            //Actor.Root.Rotation = new Quat(0, 0, 0, 0);
            //Actor.Root.LocalScale = new Vector(0, 0, 0);
            //Actor.Root.Scale = new Vector(0, 0, 0);

            //测试Tick
            //CanEverTick = true;

            // 测试未捕捉异常
            /* 
                Actor a = null;
                a.Destroy();
            */
        }

        protected override void Uninitialize()
        {
            Log.Error("[ComponentLifeTest] Uninitialize");
        }

        protected override void Tick(float dt)
        {
            Log.Error("[ComponentLifeTest] Tick ");
        }

        protected override void BeginPlay()
        {
            Log.Error("[ComponentLifeTest] [BeginPlay] ");
        }

        protected override void EndPlay(EndPlayReason reason)
        {
            Log.Error("[ComponentLifeTest] [EndPlay] " + reason);
        }
    }
}
