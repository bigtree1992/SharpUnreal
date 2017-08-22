using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试运动组件相关的功能
    /// </summary>
    public class MovementTest : MonoComponent
    {
        protected override void Initialize()
        {
            base.Initialize();
            //CanEverTick = true;
        }

        protected override void BeginPlay()
        {
            base.BeginPlay();
            TestMovement();
        }

        private void TestMovement()
        {
            if (Pawn == null)
            {
                Log.Error("[MovementTest] MyPawn is null");
            }
            else
            {
                Controller con = Pawn.Controller;
                if (con == null)
                {
                    Log.Error("[MovementTest] ai is null");
                }
                else
                {
                    TimerTest.DelayInvoke(5, () => {
                        con.SimpleMoveToLocation(new Vector(1000.0f, 0, 0));
                    });
                }
            }
        }

        protected override void Tick(float dt)
        {
            base.Tick(dt);
            if (Pawn.IsControlled)
            {
                Pawn.AddMovementInput(new Vector(1.0f, 0.0f, 0.0f), 1.0f, true);
            }
        }
    }
}
