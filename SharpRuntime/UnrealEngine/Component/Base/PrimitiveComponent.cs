using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public enum CollosionEnabled
    {
        NoCollision,
        QueryQnly,
        PhysicsOnly,
        QueryAndPhysics
    }

    public enum DOFMode
    {
        /*Inherits the degrees of freedom from the project settings.*/
        Default,
        /*Specifies which axis to freeze rotation and movement along.*/
        SixDOF,
        /*Allows 2D movement along the Y-Z plane.*/
        YZPlane,
        /*Allows 2D movement along the X-Z plane.*/
        XZPlane,
        /*Allows 2D movement along the X-Y plane.*/
        XYPlane,
        /*Allows 2D movement along the plane of a given normal*/
        CustomPlane,
        /*No constraints.*/
        None
    };

    public enum RadialImpulseFalloff
    {
        /** Impulse is a constant strength, up to the limit of its range. */
        Constant,
        /** Impulse should get linearly weaker the further from origin. */
        Linear,
        MAX,
    };

    public enum CollisionChannel
    {
        WorldStatic,
        WorldDynamic,
        Pawn,
        Visibility,
        Camera,
        PhysicsBody,
        Vehicle,
        Destructible,

        /** Reserved for gizmo collision */
        EngineTraceChannel1,

        EngineTraceChannel2,
        EngineTraceChannel3,
        EngineTraceChannel4,
        EngineTraceChannel5,
        EngineTraceChannel6,

        GameTraceChannel1,
        GameTraceChannel2,
        GameTraceChannel3,
        GameTraceChannel4,
        GameTraceChannel5,
        GameTraceChannel6,
        GameTraceChannel7,
        GameTraceChannel8,
        GameTraceChannel9,
        GameTraceChannel10,
        GameTraceChannel11,
        GameTraceChannel12,
        GameTraceChannel13,
        GameTraceChannel14,
        GameTraceChannel15,
        GameTraceChannel16,
        GameTraceChannel17,
        GameTraceChannel18,

        OverlapAll_Deprecated,
        MAX,
    };
    public enum CollisionResponse
    {
        Ignore,
        Overlap,
        Block,
        MAX,
    };

    /// <summary>
    /// PrimitiveComponent 代表了某种包含几何元素的场景组件
    /// 他们通常用来被用作渲染或者碰撞使用
    /// </summary>
    public class PrimitiveComponent : SceneComponent
    {

        #region 材质部分
        public virtual Material GetMaterial(int elementIndex)
        {
            return null;
        }

        public virtual void SetMaterial(int elementIndex, Material material)
        {

        }

        public virtual void SetMaterialByName(string slotName, Material material)
        {

        }

        public int GetMaterialIndex(string slotName)
        {
            return 0;
        }

        public bool IsMaterialSlotNameValid(string slotName)
        {
            return false;
        }

        public virtual DynamicMaterial CreateDynamicMaterial(int elementIndex, Material sourceMaterial = null)
        {
            return null;
        }
        #endregion

        #region 设置事件回调
        public void RegComponentHit(ActorComponent _this)
        {
        }

        public void RegComponentBeginOverlap(ActorComponent _this)
        {
        }

        public void RegComponentEndOverlap(ActorComponent _this)
        {
        }

        public void RegComponentWake(ActorComponent _this)
        {
        }

        public void RegComponentSleep(ActorComponent _this)
        {
        }
        #endregion

        #region 物理部分

        public bool GenerateOverlapEvents
        {
            get;
            set;
        }

        public virtual void SetSimulatePhysics(bool bSimulate)
        {

        }

        
        public void SetCollisionEnabled(CollosionEnabled NewType)
        {

        }
        public void IgnoreActorWhenMoving(Actor actor, bool shouldIgnore)
        {

        }

        public void IgnoreComponentWhenMoving(PrimitiveComponent component, bool shouldIgnore)
        {

        }

        public bool IsOverlappingActor(Actor otherActor)
        {
            return false;
        }

        public bool IsOverlappingComponent(PrimitiveComponent otherActor)
        {
            return false;
        }

        public void SetBoundsScale(float NewBoundsScale = 1.0f)
        {

        }

        public void SetConstraintMode(DOFMode ConstraintMode)
        {

        }

        public void AddImpulse(Vector Impulse, string BoneName = "", bool bVelChange = false)
        {

        }

        public void AddImpulseAtLocation(Vector Impulse, Vector Location, string BoneName = "")
        {

        }

        public void AddRadialImpulse(Vector Origin, float Radius, float Strength, RadialImpulseFalloff Falloff, bool bVelChange = false)
        {
        }

        public void AddForceAtLocation(Vector Force, Vector Location, string BoneName = "")
        {

        }

        public void AddRadialForce(Vector Origin, float Radius, float Strength, RadialImpulseFalloff Falloff, bool bAccelChange = false)
        {

        }

        public void AddTorque(Vector Torque, string BoneName = "", bool bAccelChange = false)
        {

        }

        public void SetPhysicsLinearVelocity(Vector NewVel, bool bAddToCurrent = false, string BoneName = "")
        {

        }

        public Vector GetPhysicsLinearVelocity(string BoneName = "")
        {
            return Vector.ZeroVector;
        }

        public Vector GetPhysicsLinearVelocityAtPoint(Vector Point, string BoneName = "")
        {
            return Vector.ZeroVector;
        }

        public void SetAllPhysicsLinearVelocity(Vector NewVel, bool bAddToCurrent = false)
        {

        }

        public void SetPhysicsAngularVelocity(Vector NewAngVel, bool bAddToCurrent = false, string BoneName = "")
        {

        }

        public void SetPhysicsMaxAngularVelocity(float NewMaxAngVel, bool bAddToCurrent = false, string BoneName = "")
        {

        }

        public Vector GetPhysicsAngularVelocity(string BoneName = "")
        {
            return Vector.ZeroVector;
        }

        public Vector GetCenterOfMass(string BoneName = "")
        {
            return Vector.ZeroVector;
        }

        public void SetCenterOfMass(Vector CenterOfMassOffset, string BoneName = "")
        {

        }

        public float GetClosestPointOnCollision(Vector Point, ref Vector OutPointOnBody, string BoneName = "")
        {
            return 0.0f;
        }

        public void WakeAllRigidBodies()
        {

        }

        public void SetEnableGravity(bool bGravityEnabled)
        {

        }

        public bool IsGravityEnabled()
        {
            return false;
        }


        public void SetLinearDamping(float InDamping)
        {

        }

        public float GetLinearDamping()
        {
            return 0.0f;
        }

        public void SetAngularDamping(float InDamping)
        {

        }

        public float GetAngularDamping()
        {
            return 0.0f;
        }

        public void SetMassScale(string BoneName = "", float InMassScale = 1.0f)
        {
            return ;
        }

        public float GetMassScale(string BoneName = "")
        {
            return 0.0f;
        }

        public void SetAllMassScale(float InMassScale = 1.0f)
        {

        }

        public void SetMassOverrideInKg(string BoneName = "", float MassInKg = 1.0f, bool bOverrideMass = true)
        {
        }

        public float GetMass()
        {
            return 0.0f;
        }

        public Vector GetInertiaTensor(string BoneName = "")
        {
            return Vector.ZeroVector;
        }

        public Vector ScaleByMomentOfInertia(Vector InputVector, string BoneName = "")
        {
            return Vector.ZeroVector;
        }

        public void SetCollisionResponseToChannel(CollisionChannel Channel, CollisionResponse NewResponse)
        {
        }

        public void SetCollisionResponseToAllChannels(CollisionResponse NewResponse)
        {
        }

        #endregion

    }
}
