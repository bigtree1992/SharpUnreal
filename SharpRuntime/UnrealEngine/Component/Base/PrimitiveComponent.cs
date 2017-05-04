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
            var h = _GetMaterial(NativeHandler, elementIndex);
            if (h.ToInt64() == 0)
            {
                return null;
            }

            var mat = new Material();
            mat.NativeHandler = h;
            return mat;            
        }
        
        public virtual void SetMaterial(int elementIndex, Material material)
        {
            _SetMaterial(NativeHandler, elementIndex, material.NativeHandler);
        }
        
        public virtual void SetMaterialByName(string slotName, Material material)
        {
            _SetMaterialByName(NativeHandler, slotName, material.NativeHandler);
        }
        
        public int GetMaterialIndex(string slotName)
        {
            return _GetMaterialIndex(NativeHandler,slotName);
        }
        
        public bool IsMaterialSlotNameValid(string slotName)
        {
            return _IsMaterialSlotNameValid(NativeHandler,slotName);
        }
        
        public virtual DynamicMaterial CreateDynamicMaterial(int elementIndex, Material sourceMaterial)
        {
            var p = _CreateDynamicMaterial(NativeHandler, elementIndex, sourceMaterial.NativeHandler);
            if (p.ToInt64() != 0)
            {
                var m = new DynamicMaterial();
                m.NativeHandler = p;
                return m;
            }
            return null;
        }

        #endregion

        #region 设置事件回调
        public void RegComponentHit(ActorComponent _this)
        {
            _RegComponentHit(NativeHandler, _this.NativeHandler);
        }

        public void RegComponentBeginOverlap(ActorComponent _this)
        {
            _RegComponentBeginOverlap(NativeHandler, _this.NativeHandler);
        }

        public void RegComponentEndOverlap(ActorComponent _this)
        {
            _RegComponentEndOverlap(NativeHandler, _this.NativeHandler);
        }

        public void RegComponentWake(ActorComponent _this)
        {
            _RegComponentWake(NativeHandler, _this.NativeHandler);
        }

        public void RegComponentSleep(ActorComponent _this)
        {
            _RegComponentSleep(NativeHandler, _this.NativeHandler);
        }
        
        #endregion

        #region 物理部分

        public bool GenerateOverlapEvents
        {
            get { return _GetGenerateOverlapEvents(NativeHandler); }
            set { _SetGenerateOverlapEvents(NativeHandler, value); }
        }       

        public bool SimulatePhysics
        {
            set { _SetSimulatePhysics(NativeHandler,value); }
        }      

        public bool GeneratesHitEvents
        {
            set { _SetGeneratesHitEvents(NativeHandler, value); }
        }

        public CollosionEnabled CollisionEnabled
        {
            set { _SetCollisionEnabled(NativeHandler, value); }
        }

        public void IgnoreComponentWhenMoving(PrimitiveComponent component, bool shouldIgnore)
        {
            _IgnoreComponentWhenMoving(NativeHandler, component.NativeHandler, shouldIgnore);
        }
        
        public bool IsOverlappingComponent(PrimitiveComponent other)
        {
            return _IsOverlappingComponent(NativeHandler,other.NativeHandler);
        }

        public float BoundsScale
        {
            set{ _SetBoundsScale(NativeHandler, value); }
        }

        public DOFMode ConstraintMode
        {
            set { _SetConstraintMode(NativeHandler,value); }
        }

        public void AddImpulse(Vector Impulse, string BoneName = "", bool bVelChange = false)
        {
            _AddImpulse(NativeHandler, Impulse, BoneName, bVelChange);
        }
        
        public void AddImpulseAtLocation(Vector Impulse, Vector Location, string BoneName = "")
        {
            _AddImpulseAtLocation(NativeHandler, Impulse, Location, BoneName);
        }

        public void AddRadialImpulse(Vector Origin, float Radius, float Strength, RadialImpulseFalloff Falloff, bool bVelChange = false)
        {
            _AddRadialImpulse( NativeHandler,Origin,Radius, Strength,Falloff, bVelChange);
        }

        public void AddForceAtLocation(Vector Force, Vector Location, string BoneName = "")
        {
            _AddForceAtLocation(NativeHandler,  Force,  Location,  BoneName);
        }
        
        public void AddRadialForce(Vector Origin, float Radius, float Strength, RadialImpulseFalloff Falloff, bool bAccelChange = false)
        {
            _AddRadialForce(NativeHandler,  Origin,  Radius,  Strength,  Falloff,  bAccelChange);
        }
        
        public void AddTorque(Vector Torque, string BoneName = "", bool bAccelChange = false)
        {
            _AddTorque(NativeHandler,  Torque,  BoneName,  bAccelChange);
        }
        
        public void SetPhysicsLinearVelocity(Vector NewVel, bool bAddToCurrent = false, string BoneName = "")
        {
            _SetPhysicsLinearVelocity(NativeHandler,  NewVel,  bAddToCurrent, BoneName);
        }
        
        public Vector GetPhysicsLinearVelocity(string BoneName = "")
        {
            return _GetPhysicsLinearVelocity(NativeHandler, BoneName);
        }
        
        public Vector GetPhysicsLinearVelocityAtPoint(Vector Point, string BoneName = "")
        {
            return _GetPhysicsLinearVelocityAtPoint(NativeHandler, Point, BoneName);
        }
       
        public void SetAllPhysicsLinearVelocity(Vector NewVel, bool bAddToCurrent = false)
        {
            _SetAllPhysicsLinearVelocity(NativeHandler, NewVel, bAddToCurrent);
        }
        
        public void SetPhysicsAngularVelocity(Vector NewAngVel, bool bAddToCurrent = false, string BoneName = "")
        {
            _SetPhysicsAngularVelocity(NativeHandler, NewAngVel, bAddToCurrent, BoneName);
        }
        
        public void SetPhysicsMaxAngularVelocity(float NewMaxAngVel, bool bAddToCurrent = false, string BoneName = "")
        {
            _SetPhysicsMaxAngularVelocity(NativeHandler, NewMaxAngVel, bAddToCurrent , BoneName);
        }
        
        public Vector GetPhysicsAngularVelocity(string BoneName = "")
        {
            return _GetPhysicsAngularVelocity(NativeHandler, BoneName);
        }
        
        public Vector GetCenterOfMass(string BoneName = "")
        {
            return _GetCenterOfMass(NativeHandler, BoneName);
        }
        
        public void SetCenterOfMass(Vector CenterOfMassOffset, string BoneName = "")
        {
            _SetCenterOfMass(NativeHandler, CenterOfMassOffset, BoneName);
        }

        public float GetClosestPointOnCollision(Vector Point, ref Vector OutPointOnBody, string BoneName = "")
        {
            return _GetClosestPointOnCollision(NativeHandler, Point, ref OutPointOnBody, BoneName);
        }

        public void WakeAllRigidBodies()
        {
            _WakeAllRigidBodies(NativeHandler);
        }        

        public bool IsGravityEnabled        
        {
            get { return _GetIsGravityEnabled(NativeHandler); }
            set { _SetIsGravityEnabled(NativeHandler, value); }
        }     

        public float LinearDamping
        {
            get { return _GetLinearDamping(NativeHandler); }
            set { _SetLinearDamping(NativeHandler, value); }
        }       

        public float AngularDamping
        {
            get { return _GetAngularDamping(NativeHandler); }
            set { _SetAngularDamping0(NativeHandler, value); }
        }    

        public void SetMassScale(string BoneName = "", float InMassScale = 1.0f)
        {
            _SetMassScale(NativeHandler, BoneName, InMassScale);
        }
        
        public float GetMassScale(string BoneName = "")
        {
            return _GetMassScale(NativeHandler, BoneName);
        }
        
        public void SetAllMassScale(float InMassScale = 1.0f)
        {
            _SetAllMassScale(NativeHandler, InMassScale);
        }
        
        public void SetMassOverrideInKg(string BoneName = "", float MassInKg = 1.0f, bool bOverrideMass = true)
        {
            _SetMassOverrideInKg(NativeHandler, BoneName, MassInKg, bOverrideMass);
        }
        
        public float Mass
        {
            get { return _GetMass(NativeHandler); }
        }
        
        public Vector GetInertiaTensor(string BoneName = "")
        {
            return _GetInertiaTensor(NativeHandler, BoneName);
        }
        
        public Vector ScaleByMomentOfInertia(Vector InputVector, string BoneName = "")
        {
            return _SetScaleByMomentOfInertia(NativeHandler, InputVector, BoneName);
        }
        
        public void SetCollisionResponseToChannel(CollisionChannel Channel, CollisionResponse NewResponse)
        {
            _SetCollisionResponseToChannel(NativeHandler, Channel, NewResponse);
        }
        
        public void SetCollisionResponseToAllChannels(CollisionResponse NewResponse)
        {
            _SetAngularDamping1(NativeHandler, NewResponse);
        }

        #endregion

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
        private extern static IntPtr _CreateDynamicMaterial(IntPtr handler, int elementIndex, IntPtr source);
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
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetGenerateOverlapEvents(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetGenerateOverlapEvents(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetSimulatePhysics(IntPtr handler, bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetGeneratesHitEvents(IntPtr handler, bool value);
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
        private extern static void _SetCenterOfMass(IntPtr handler, Vector CenterOfMassOffset, string BoneName);
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
        private extern static void _SetAngularDamping0(IntPtr handler, float value);
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
        private extern static void _SetAngularDamping1(IntPtr handler, CollisionResponse NewResponse);
    }
}
