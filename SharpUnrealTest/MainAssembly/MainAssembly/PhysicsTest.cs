using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 物理系统相关的接口测试
    /// </summary>
    public class PhysicsTest : MonoComponent
    {
        protected override void Initialize()
        {
            base.Initialize();
            TestPhysics();
        }

        private void TestPhysics()
        {
            var mesh = Actor.GetComponent<StaticMeshComponent>();
            mesh.SimulatePhysics = true;
            mesh.IsGravityEnabled = true;
            //mesh.LocalPosition
            Vector socket = mesh.GetSocketLocation("Socket");
            Vector impluse = new Vector(0.0f, 0.0f, 10000000.0f);
            /* Impluse
            mesh.AddImpulse(impluse);
            mesh.AddImpulseAtLocation(impluse, socket);
            mesh.AddRadialImpulse(socket, 100000.0f, 100000.0f, RadialImpulseFalloff.MAX);
            */

            mesh.AddForceAtLocation(impluse, socket);
            //mesh.AddRadialForce(socket, 1000000.0f, 1000000.0f, RadialImpulseFalloff.MAX);
            //mesh.AddTorque(impluse);
            TimerTest.DelayInvoke(1.0f, () => {
                Vector velocity = Vector.ZeroVector;
                //velocity = mesh.GetPhysicsLinearVelocity();
                //velocity = mesh.GetPhysicsAngularVelocity();
                //velocity = mesh.GetPhysicsLinearVelocityAtPoint(socket);
                //Log.Error("[PhysiscTest] get velocity:" + velocity);

                velocity = new Vector(0.0f, -1000000.0f, -100000.0f);
                mesh.SetPhysicsLinearVelocity(velocity);
            });
        }
    }
}
