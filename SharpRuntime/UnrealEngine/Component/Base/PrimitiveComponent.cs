using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    /// <summary>
    /// PrimitiveComponent 代表了某种包含几何元素的场景组件
    /// 他们通常用来被用作渲染或者碰撞使用
    /// </summary>
    public class PrimitiveComponent : SceneComponent
    {
        #region 材质部分
        public virtual Material GetMaterial(int elementIndex)
        {
            var h = _GetMaterial(m_NativeHandler, elementIndex);
            if (h.ToInt64() == 0)
            {
                return null;
            }

            var mat = new Material();
            mat.NativeHandler = _GetMaterial(m_NativeHandler, elementIndex);
            return mat;            
        }
        
        public virtual void SetMaterial(int elementIndex, Material material)
        {
            _SetMaterial(m_NativeHandler, elementIndex, material.NativeHandler);
        }
        
        public virtual void SetMaterialByName(string slotName, Material material)
        {
            _SetMaterialByName(m_NativeHandler, slotName, material.NativeHandler);
        }
        
        public int GetMaterialIndex(string slotName)
        {
            return _GetMaterialIndex(m_NativeHandler,slotName);
        }
        
        public bool IsMaterialSlotNameValid(string slotName)
        {
            return _IsMaterialSlotNameValid(m_NativeHandler,slotName);
        }
        
        public virtual DynamicMaterial CreateDynamicMaterial(int elementIndex, Material sourceMaterial)
        {
            var p = _CreateDynamicMaterial(m_NativeHandler, elementIndex, sourceMaterial.NativeHandler);
            if (p.ToInt64() != 0)
            {
                var m = new DynamicMaterial();
                m.NativeHandler = p;
                return m;
            }
            return null;
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _GetMaterial(IntPtr handler, int elementIndex);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetMaterial(IntPtr handler, int elementIndex, IntPtr material);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetMaterialByName(IntPtr handler, string slotName, IntPtr material);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static int _GetMaterialIndex(IntPtr handler, string slotName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _IsMaterialSlotNameValid(IntPtr handler, string slotName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _CreateDynamicMaterial(IntPtr handler, int elementIndex,IntPtr source);
        #endregion

        #region 设置事件回调
        public void RegComponentHit(ActorComponent _this)
        {
            _RegComponentHit(m_NativeHandler, _this.NativeHandler);
        }

        public void RegComponentBeginOverlap(ActorComponent _this)
        {
            _RegComponentBeginOverlap(m_NativeHandler, _this.NativeHandler);
        }

        public void RegComponentEndOverlap(ActorComponent _this)
        {
            _RegComponentEndOverlap(m_NativeHandler, _this.NativeHandler);
        }

        public void RegComponentWake(ActorComponent _this)
        {
            _RegComponentWake(m_NativeHandler, _this.NativeHandler);
        }

        public void RegComponentSleep(ActorComponent _this)
        {
            _RegComponentSleep(m_NativeHandler, _this.NativeHandler);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegComponentHit(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegComponentBeginOverlap(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegComponentEndOverlap(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegComponentWake(IntPtr handler, IntPtr listener);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _RegComponentSleep(IntPtr handler, IntPtr listener);
        #endregion

        #region 物理部分

        public bool GenerateOverlapEvents
        {
            get { return _GetGenerateOverlapEvents(m_NativeHandler); }
            set { _SetGenerateOverlapEvents(m_NativeHandler, value); }
        }       

        public virtual bool SimulatePhysics
        {
            set { _SetSimulatePhysics(m_NativeHandler,value); }
        }      

        public CollosionEnabled CollisionEnabled
        {
            set { _SetCollisionEnabled(m_NativeHandler, value); }
        }

        public void IgnoreComponentWhenMoving(PrimitiveComponent component, bool shouldIgnore)
        {
            _IgnoreComponentWhenMoving(m_NativeHandler, component.NativeHandler, shouldIgnore);
        }
        
        public bool IsOverlappingComponent(PrimitiveComponent other)
        {
            return _IsOverlappingComponent(m_NativeHandler,other.NativeHandler);
        }

        public float BoundsScale
        {
            set{ _SetBoundsScale(m_NativeHandler, value); }
        }

        public DOFMode ConstraintMode
        {
            set { _SetConstraintMode(m_NativeHandler,value); }
        }

        public void AddImpulse(Vector Impulse, string BoneName = "", bool bVelChange = false)
        {
            _AddImpulse(m_NativeHandler, Impulse, BoneName, bVelChange);
        }
        
        public void AddImpulseAtLocation(Vector Impulse, Vector Location, string BoneName = "")
        {
            _AddImpulseAtLocation(m_NativeHandler, Impulse, Location, BoneName);
        }

        public void AddRadialImpulse(Vector Origin, float Radius, float Strength, RadialImpulseFalloff Falloff, bool bVelChange = false)
        {
            _AddRadialImpulse( m_NativeHandler,Origin,Radius, Strength,Falloff, bVelChange);
        }

        public void AddForceAtLocation(Vector Force, Vector Location, string BoneName = "")
        {
            _AddForceAtLocation(m_NativeHandler,  Force,  Location,  BoneName);
        }
        
        public void AddRadialForce(Vector Origin, float Radius, float Strength, RadialImpulseFalloff Falloff, bool bAccelChange = false)
        {
            _AddRadialForce(m_NativeHandler,  Origin,  Radius,  Strength,  Falloff,  bAccelChange);
        }
        
        public void AddTorque(Vector Torque, string BoneName = "", bool bAccelChange = false)
        {
            _AddTorque(m_NativeHandler,  Torque,  BoneName,  bAccelChange);
        }
        


        public void SetPhysicsLinearVelocity(Vector NewVel, bool bAddToCurrent = false, string BoneName = "")
        {
            _SetPhysicsLinearVelocity(m_NativeHandler,  NewVel,  bAddToCurrent, BoneName);
        }
        
        public Vector GetPhysicsLinearVelocity(string BoneName = "")
        {
            return _GetPhysicsLinearVelocity(m_NativeHandler, BoneName);
        }
        
        public Vector GetPhysicsLinearVelocityAtPoint(Vector Point, string BoneName = "")
        {
            return _GetPhysicsLinearVelocityAtPoint(m_NativeHandler, Point, BoneName);
        }
       
        public void SetAllPhysicsLinearVelocity(Vector NewVel, bool bAddToCurrent = false)
        {
            _SetAllPhysicsLinearVelocity(m_NativeHandler, NewVel, bAddToCurrent);
        }
        
        public void SetPhysicsAngularVelocity(Vector NewAngVel, bool bAddToCurrent = false, string BoneName = "")
        {
            _SetPhysicsAngularVelocity(m_NativeHandler, NewAngVel, bAddToCurrent, BoneName);
        }
        
        public void SetPhysicsMaxAngularVelocity(float NewMaxAngVel, bool bAddToCurrent = false, string BoneName = "")
        {
            _SetPhysicsMaxAngularVelocity(m_NativeHandler, NewMaxAngVel, bAddToCurrent , BoneName);
        }
        
        public Vector GetPhysicsAngularVelocity(string BoneName = "")
        {
            return _GetPhysicsAngularVelocity(m_NativeHandler, BoneName);
        }
        
        public Vector GetCenterOfMass(string BoneName = "")
        {
            return _GetCenterOfMass(m_NativeHandler, BoneName);
        }
        
        public void SetCenterOfMass(Vector CenterOfMassOffset, string BoneName = "")
        {
            _SetCenterOfMass(m_NativeHandler, CenterOfMassOffset, BoneName);
        }

        public float GetClosestPointOnCollision(Vector Point, ref Vector OutPointOnBody, string BoneName = "")
        {
            return _GetClosestPointOnCollision(m_NativeHandler, Point, ref OutPointOnBody, BoneName);
        }

        public void WakeAllRigidBodies()
        {
            _WakeAllRigidBodies(m_NativeHandler);
        }        

        public bool IsGravityEnabled        
        {
            get { return _GetIsGravityEnabled(m_NativeHandler); }
            set { _SetIsGravityEnabled(m_NativeHandler, value); }
        }     

        public float LinearDamping
        {
            get { return _GetLinearDamping(m_NativeHandler); }
            set { _SetLinearDamping(m_NativeHandler, value); }
        }       

        public float AngularDamping
        {
            get { return _GetAngularDamping(m_NativeHandler); }
            set { _SetAngularDamping(m_NativeHandler, value); }
        }    

        public void SetMassScale(string BoneName = "", float InMassScale = 1.0f)
        {
            _SetMassScale(m_NativeHandler, BoneName, InMassScale);
        }
        
        public float GetMassScale(string BoneName = "")
        {
            return _GetMassScale(m_NativeHandler, BoneName);
        }
        
        public void SetAllMassScale(float InMassScale = 1.0f)
        {
            _SetAllMassScale(m_NativeHandler, InMassScale);
        }
        
        public void SetMassOverrideInKg(string BoneName = "", float MassInKg = 1.0f, bool bOverrideMass = true)
        {
            _SetMassOverrideInKg(m_NativeHandler, BoneName, MassInKg, bOverrideMass);
        }
        
        public float Mass
        {
            get { return _GetMass(m_NativeHandler); }
        }
        
        public Vector GetInertiaTensor(string BoneName = "")
        {
            return _GetInertiaTensor(m_NativeHandler, BoneName);
        }
        
        public Vector ScaleByMomentOfInertia(Vector InputVector, string BoneName = "")
        {
            return _SetScaleByMomentOfInertia(m_NativeHandler, InputVector, BoneName);
        }
        
        public void SetCollisionResponseToChannel(CollisionChannel Channel, CollisionResponse NewResponse)
        {
            _SetCollisionResponseToChannel(m_NativeHandler, Channel, NewResponse);
        }
        
        public void SetCollisionResponseToAllChannels(CollisionResponse NewResponse)
        {
            _SetAngularDamping(m_NativeHandler, NewResponse);
        }



        
        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetGenerateOverlapEvents(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetGenerateOverlapEvents(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetSimulatePhysics(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCollisionEnabled(IntPtr handler, CollosionEnabled value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _IgnoreComponentWhenMoving(IntPtr handler, IntPtr component, bool shouldIgnore);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _IsOverlappingComponent(IntPtr handler, IntPtr other);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBoundsScale(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetConstraintMode(IntPtr handler, DOFMode value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddImpulse(IntPtr handler, Vector Impulse, string BoneName, bool bVelChange);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddImpulseAtLocation(IntPtr handler, Vector Impulse, Vector Location, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddRadialImpulse(IntPtr handler, Vector Origin, float Radius, float Strength, RadialImpulseFalloff Falloff, bool bVelChange);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddForceAtLocation(IntPtr handler, Vector Force, Vector Location, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddRadialForce(IntPtr handler, Vector Origin, float Radius, float Strength, RadialImpulseFalloff Falloff, bool bAccelChange);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _AddTorque(IntPtr handler, Vector Torque, string BoneName, bool bAccelChange);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPhysicsLinearVelocity(IntPtr handler, Vector NewVel, bool bAddToCurrent, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetPhysicsLinearVelocity(IntPtr handler, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetPhysicsLinearVelocityAtPoint(IntPtr handler, Vector Point, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetAllPhysicsLinearVelocity(IntPtr handler, Vector NewVel, bool bAddToCurrent);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPhysicsAngularVelocity(IntPtr handler, Vector NewAngVel, bool bAddToCurrent, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetPhysicsMaxAngularVelocity(IntPtr handler, float NewMaxAngVel, bool bAddToCurrent, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetPhysicsAngularVelocity(IntPtr handler, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetCenterOfMass(IntPtr handler, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _SetCenterOfMass(IntPtr handler, Vector CenterOfMassOffset, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetClosestPointOnCollision(IntPtr handler, Vector Point, ref Vector OutPointOnBody, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _WakeAllRigidBodies(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetIsGravityEnabled(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetIsGravityEnabled(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetLinearDamping(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLinearDamping(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetAngularDamping(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetAngularDamping(IntPtr handler, float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetMassScale(IntPtr handler, string BoneName, float InMassScale);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetMassScale(IntPtr handler, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetAllMassScale(IntPtr handler, float InMassScale);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetMassOverrideInKg(IntPtr handler, string BoneName, float MassInKg, bool bOverrideMass);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetMass(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetInertiaTensor(IntPtr handler, string BoneName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _SetScaleByMomentOfInertia(IntPtr handler, Vector InputVector, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetCollisionResponseToChannel(IntPtr handler, CollisionChannel Channel, CollisionResponse NewResponse);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetAngularDamping(IntPtr handler, CollisionResponse NewResponse);
    }
}
