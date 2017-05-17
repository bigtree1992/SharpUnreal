using System;
using System.Collections.Generic;


namespace UnrealEngine
{
    public class PawnMovementComponent : NavMovementComponent 
    {
        public void AddInputVector(Vector WorldVector, bool bForce = false)
        {

        }

        public Vector PendingInputVector
        {
            get;
        }

        public Vector LastInputVector
        {
            get;
        }

        public Vector ConsumeInputVector
        {
            get;
        }

        public bool IsMoveInputIgnored
        {
            get;
        }
    }
}
