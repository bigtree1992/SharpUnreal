using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 组件生命周期测试
    /// </summary>
    public class ComponentLifeTest : ActorComponent
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

            Actor.Root.LocalPosition = 
                Actor.Root.LocalPosition + new Vector(0, 0, 100);
            
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
