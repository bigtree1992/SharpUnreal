using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试运动组件相关的功能
    /// </summary>
    public class MovementTest : MonoComponent
    {
        private Pawn MyPawn = null;
        protected override void Initialize()
        {
            base.Initialize();
            TestMovement();
            //CanEverTick = true;
        }

        private void TestMovement()
        {
            if(Actor == null)
            {
                Log.Error("[MovementTest] Actor is null");
            }
            MyPawn = Actor.AsPawn();
            if (MyPawn == null)
            {
                Log.Error("[MovementTest] MyPawn is null");
            }
            else
            {
                //MyPawn.AddMovementInput(new Vector(0.0f, 0.0f, 1.0f), 1.0f, true);
                if (!MyPawn.IsControlled)
                {
                    Log.Error("[MovementTest] Pawn is not Controllered");
                }
                if (MyPawn.Controller == null)
                {
                    Log.Error("[MovementTest] Controller is null");
                }
                else
                {
                    AIController ai = MyPawn.Controller.AsAIController();
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
            MyPawn.AddMovementInput(new Vector(1.0f, 0.0f, 0.0f), 1.0f, true);
        }
    }
}
