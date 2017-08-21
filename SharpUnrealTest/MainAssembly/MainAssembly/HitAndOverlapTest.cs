using System;
using System.Collections.Generic;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试碰撞跟触发相关的接口
    /// </summary>
    public class HitAndOverlapTest : MonoComponent
    {
        protected override void Initialize()
        {
            var mesh = Actor.GetComponent<StaticMeshComponent>();
            //设置是否进行物理仿真
            mesh.SimulatePhysics = true;
            //设置是否生成重叠事件
            mesh.GenerateOverlapEvents = true;
            //设置是否生成碰撞事件
            mesh.GeneratesHitEvents = true;

            //注册碰撞事件
            mesh.RegComponentHit(this);
            //注册开始重叠事件
            mesh.RegComponentBeginOverlap(this);
            //注册结束重叠事件
            mesh.RegComponentEndOverlap(this);

        }

        public override void OnComponentBeginOverlap(PrimitiveComponent self, PrimitiveComponent comp, Vector impact)
        {
            Log.Debug("[OnComponentBeginOverlap] : " +  self.Actor.Name + " | " + comp.Actor.Name);
        }

        public override void OnComponentEndOverlap(PrimitiveComponent self, PrimitiveComponent comp)
        {
            Log.Debug("[OnComponentEndOverlap] : " + self.Actor.Name + " | " + comp.Actor.Name);
        }

        public override void OnComponentHit(PrimitiveComponent self, PrimitiveComponent comp, Vector impact)
        {
            Log.Debug("[OnComponentHit] : " + self.Actor.Name + " | " + comp.Actor.Name);
        }
    }
}
