using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试曲线相关的接口
    /// </summary>
    public class SplineTest : ActorComponent
    {
        private StaticMeshComponent cube = null;
        private SplineComponent spline = null;
        private float timer = 0.0f;
        protected override void Initialize()
        {
            base.Initialize();
            TestSpline();
            CanEverTick = true;
        }

        private void TestSpline()
        {
            cube = Actor.GetComponent<StaticMeshComponent>();
            spline = Actor.GetComponent<SplineComponent>();
        }

        protected override void Tick(float dt)
        {
            base.Tick(dt);
            timer += dt;
            Transform trans = spline.GetTransformAtTime(timer, SplineCoordinateSpace.World, false, false);
            cube.LocalPosition = trans.GetLocation();
        }
    }
}
