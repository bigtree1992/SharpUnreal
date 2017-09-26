using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public enum EndPlayReason
    {
        /** When the Actor or Component is explicitly destroyed. */
        Destroyed,
        /** When the world is being unloaded for a level transition. */
        LevelTransition,
        /** When the world is being unloaded because PIE is ending. */
        EndPlayInEditor,
        /** When the level it is a member of is streamed out. */
        RemovedFromWorld,
        /** When the application is being exited. */
        Quit
    }

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
    }

    public enum RadialImpulseFalloff
    {
        /** Impulse is a constant strength, up to the limit of its range. */
        Constant,
        /** Impulse should get linearly weaker the further from origin. */
        Linear,
        MAX,
    }

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
    }

    public enum CollisionResponse
    {
        Ignore,
        Overlap,
        Block,
        MAX,
    }

    public enum BoneSpaces
    {
        /** Set absolute position of bone in world space. */
        WorldSpace,
        /** Set position of bone in components reference frame. */
        ComponentSpace
        /** Set position of bone relative to parent bone. */
        //LocalSpace		UMETA( DisplayName = "Parent Bone Space" ),
    }

    public enum PhysBodyOp
    {
        /** Don't do anything. */
        PBO_None,
        /** Terminate - if you terminate, you won't be able to re-init when unhidden. */
        PBO_Term,
        /** Disable collision - it will enable collision when unhidden. */
        PBO_Disable,
        PBO_MAX
    }

    public enum SplineCoordinateSpace
    {
        Local,
        World
    }

    public enum PathFollowingReqResult
    {
        Failed = 0,
        AlreadyAtGoal = 1,
        RequestSuccessful = 2
    }

    public enum PathFollowingStatus
    {
        /** No requests */
        Idle,

        /** Request with incomplete path, will start after UpdateMove() */
        Waiting,

        /** Request paused, will continue after ResumeMove() */
        Paused,

        /** Following path */
        Moving,
    }

    public enum SplineMeshAxis
    {
        X,
        Y,
        Z,
    }

    public enum PlaneConstraintAxisSetting
    {
        /** Lock movement to a user-defined axis. */
        Custom = 0,
        /** Lock movement in the X axis. */
        X = 1,
        /** Lock movement in the Y axis. */
        Y = 2,
        /** Lock movement in the Z axis. */
        Z = 3,
        /** Use the global physics project setting. */
        UseGlobalPhysicsSetting = 4
    }

    public enum ENetRole
    {
        /** No role at all. */
        ROLE_None,
        /** Locally simulated proxy of this actor. */
        ROLE_SimulatedProxy,
        /** Locally autonomous proxy of this actor. */
        ROLE_AutonomousProxy,
        /** Authoritative control over the actor. */
        ROLE_Authority,
        ROLE_MAX,
    };
}