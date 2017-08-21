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
            TestMovement();
            //CanEverTick = true;
        }

        private void TestMovement()
        {
            if (Pawn == null)
            {
                Log.Error("[MovementTest] MyPawn is null");
            }
            else
            {
                Log.Error("[MovementTest] MyPawn is not null");
                //MyPawn.AddMovementInput(new Vector(0.0f, 0.0f, 1.0f), 1.0f, true);
                if (!Pawn.IsControlled)
                {
                    Log.Error("[MovementTest] Pawn is not Controllered");
                }
                Log.Error("[MovementTest] MyPawn is Controlled");
                if (Pawn.AIController == null)
                {
                    Log.Error("[MovementTest] Controller is null");
                }
                else
                {
                    AIController ai = Pawn.AIController;
                    if (ai == null)
                    {
                        Log.Error("[MovementTest] ai is null");
                    }
                    else
                    {
                        Log.Error("[MovementTest] ai MoveToLocation");
                        ai.MoveToLocation(new Vector(4000, 4000, 100), 1.0f, true, true, true, true, true);
                    }
                }
            }
        }

        protected override void Tick(float dt)
        {
            base.Tick(dt);
            //MyPawn.AddMovementInput(new Vector(1.0f, 0.0f, 0.0f), 1.0f, true);
        }
    }
}
