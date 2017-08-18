using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 粒子系统相关的接口测试
    /// </summary>
    public class ParticlesTest : ActorComponent
    {
        protected override void Initialize()
        {
            base.Initialize();
            Log.Error("[ParticleTest] Initialize");
            TestParticleSystem();
        }

        private void TestParticleSystem()
        {
            var particles = Actor.GetComponent<ParticleSystemComponent>();
            if (particles == null)
            {
                Log.Error("[ParticleTest] particle is null");
            }
            particles.RegParticleBurst(this);
            particles.RegParticleCollide(this);
            particles.RegParticleDeath(this);
            particles.RegParticleSpawn(this);
            particles.RegSystemFinished(this);

            particles.ActivateSystem();
            TimerTest.DelayInvoke(5.0f, () => {
                particles.DeactivateSystem();
                TimerTest.DelayInvoke(3.0f, () => {
                    particles.ActivateSystem();
                });
            });
        }

        public override void OnSystemFinished(string event_name)
        {
            base.OnSystemFinished(event_name);
            Log.Error("[ParticleTest] OnSystemFinished,event_name:" + event_name);
        }

        public override void OnParticleBurst(string event_name)
        {
            base.OnParticleBurst(event_name);
            Log.Error("[ParticleTest] particle is Burst");
        }

        public override void OnParticleCollide(string event_name)
        {
            base.OnParticleCollide(event_name);
            Log.Error("[ParticleTest] particle is Collide");
        }

        public override void OnParticleDeath(string event_name)
        {
            base.OnParticleDeath(event_name);
            Log.Error("[ParticleTest] particle is Death");
        }

        public override void OnParticleSpawn(string event_name)
        {
            base.OnParticleSpawn(event_name);
            Log.Error("[ParticleTest] particle is Spawn");
        }
    }
}
