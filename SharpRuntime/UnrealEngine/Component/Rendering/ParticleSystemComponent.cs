using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class ParticleSystemComponent : PrimitiveComponent
    {
        public void ActivateSystem(bool bFlagAsJustAttached = false)
        {
            _ActivateSystem(NativeHandler, bFlagAsJustAttached);
        }
        
        public void DeactivateSystem()
        {
            _DeactivateSystem(NativeHandler);
        }
        
        public void ResetToDefaults()
        {
            _ResetToDefaults(NativeHandler);
        }
        
        public void SetFloatParameter(string ParameterName, float Param)
        {
            _SetFloatParameter(NativeHandler, ParameterName, Param);
        }
        
        public void SetVectorParameter(string ParameterName, Vector Param)
        {
            _SetVectorParameter(NativeHandler, ParameterName, Param);
        }
        
        public void SetColorParameter(string ParameterName, LinearColor Param)
        {
            _SetColorParameter(NativeHandler,ParameterName, Param);
        }
        
        public float GetFloatParameter(string ParameterName)
        {
            return _GetFloatParameter(NativeHandler,ParameterName);
        }
        
        public Vector GetVectorParameter(string ParameterName)
        {
            return _GetVectorParameter(NativeHandler,ParameterName);
        }
        
        public LinearColor GetColorParameter(string ParameterName)
        {
            return _GetColorParameter(NativeHandler,ParameterName);
        }
        
        #region 设置事件回调
        public void RegParticleSpawn(ActorComponent _this)
        {
            _RegParticleSpawn(NativeHandler, _this.NativeHandler);
        }

        public void RegParticleBurst(ActorComponent _this)
        {
            _RegParticleBurst(NativeHandler, _this.NativeHandler);
        }
        
        public void RegParticleDeath(ActorComponent _this)
        {
            _RegParticleDeath(NativeHandler, _this.NativeHandler);
        }
        
        public void RegParticleCollide(ActorComponent _this)
        {
            _RegParticleCollide(NativeHandler, _this.NativeHandler);
        }
        
        public void RegSystemFinished(ActorComponent _this)
        {
            _RegSystemFinished(NativeHandler, _this.NativeHandler);
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
