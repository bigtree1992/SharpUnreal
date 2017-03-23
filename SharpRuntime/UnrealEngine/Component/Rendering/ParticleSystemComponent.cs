using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class ParticleSystemComponent : PrimitiveComponent
    {
        public void ActivateSystem(bool bFlagAsJustAttached = false)
        {
            _ActivateSystem(m_NativeHandler, bFlagAsJustAttached);
        }
        
        public void DeactivateSystem()
        {
            _DeactivateSystem(m_NativeHandler);
        }
        
        public void ResetToDefaults()
        {
            _ResetToDefaults(m_NativeHandler);
        }
        
        public void SetFloatParameter(string ParameterName, float Param)
        {
            _SetFloatParameter(m_NativeHandler, ParameterName, Param);
        }
        
        public void SetVectorParameter(string ParameterName, Vector Param)
        {
            _SetVectorParameter(m_NativeHandler, ParameterName, Param);
        }
        
        public void SetColorParameter(string ParameterName, LinearColor Param)
        {
            _SetColorParameter(m_NativeHandler,ParameterName, Param);
        }
        
        public float GetFloatParameter(string ParameterName)
        {
            return _GetFloatParameter(m_NativeHandler,ParameterName);
        }
        
        public Vector GetVectorParameter(string ParameterName)
        {
            return _GetVectorParameter(m_NativeHandler,ParameterName);
        }
        
        public LinearColor GetColorParameter(string ParameterName)
        {
            return _GetColorParameter(m_NativeHandler,ParameterName);
        }
        
        #region 设置事件回调
        public void RegParticleSpawn(ActorComponent _this)
        {
            _RegParticleSpawn(m_NativeHandler, _this.NativeHandler);
        }

        public void RegParticleBurst(ActorComponent _this)
        {
            _RegParticleBurst(m_NativeHandler, _this.NativeHandler);
        }
        
        public void RegParticleDeath(ActorComponent _this)
        {
            _RegParticleDeath(m_NativeHandler, _this.NativeHandler);
        }
        
        public void RegParticleCollide(ActorComponent _this)
        {
            _RegParticleCollide(m_NativeHandler, _this.NativeHandler);
        }
        
        public void RegSystemFinished(ActorComponent _this)
        {
            _RegSystemFinished(m_NativeHandler, _this.NativeHandler);
        }
        #endregion
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _ActivateSystem(IntPtr handler, bool bFlagAsJustAttached);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _DeactivateSystem(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _ResetToDefaults(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetFloatParameter(IntPtr handler, string ParameterName, float Param);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetVectorParameter(IntPtr handler, string ParameterName, Vector Param);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetColorParameter(IntPtr handler, string ParameterName, LinearColor Param);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetFloatParameter(IntPtr handler, string ParameterName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetVectorParameter(IntPtr handler, string ParameterName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static LinearColor _GetColorParameter(IntPtr handler, string ParameterName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegParticleSpawn(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegParticleBurst(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegParticleDeath(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegParticleCollide(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegSystemFinished(IntPtr handler, IntPtr listener);
    }
}
