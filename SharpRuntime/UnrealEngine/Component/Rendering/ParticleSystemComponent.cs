using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class ParticleSystemComponent : PrimitiveComponent
    {
        public void ActivateSystem(bool bFlagAsJustAttached = false)
        {

        }

        public void DeactivateSystem()
        {
        }

        public void ResetToDefaults()
        {
        }

        public void SetFloatParameter(string ParameterName, float Param)
        {
        }


        public void SetVectorParameter(string ParameterName, Vector Param)
        {

        }

        public void SetColorParameter(string ParameterName, LinearColor Param)
        {

        }

        public float GetFloatParameter(string ParameterName)
        {
            return 0.0f;
        }

        public Vector GetVectorParameter(string ParameterName)
        {
            return Vector.ZeroVector;
        }

        public LinearColor GetColorParameter(string ParameterName)
        {
            return LinearColor.Black;
        }

        #region 设置事件回调
        public void RegParticleSpawn(ActorComponent _this)
        {

        }

        public void RegParticleBurst(ActorComponent _this)
        {

        }

        public void RegParticleDeath(ActorComponent _this)
        {

        }

        public void RegParticleCollide(ActorComponent _this)
        {

        }
        #endregion
    }
}
