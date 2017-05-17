using System;
using System.Collections.Generic;


namespace UnrealEngine
{
    public class AIController : Controller
    {
        public PathFollowingReqResult MoveToActor(Actor actor, float accepanceRadius = -1,bool stopOnOverlap = true, bool usePathfinding = true, bool bCanStrafe = true, bool allowPartialPath = true)
        {
            return PathFollowingReqResult.Failed;
        }

        public PathFollowingReqResult MoveToLocation(Vector actor, float accepanceRadius = -1,bool stopOnOverlap = true, bool usePathfinding = true, bool bCanStrafe = true, bool allowPartialPath = true)
        {
            return PathFollowingReqResult.Failed;
        }

        public PathFollowingStatus MoveStatus
        {
            get;
        }

        public bool HasPartialPath
        {
            get;
        }

        public Vector ImmediateMoveDestination
        {
            get;
        }

        public Vector FocalPoint
        {
            get;
            set;
        }

        public Actor FocusActor
        {
            get;
            set;
        }

        public Vector GetFocalPointOnActor(Actor actor)
        {
            return Vector.ZeroVector;
        }

        public void SetMoveBlockDetection(bool value)
        {

        }



    }
}
