using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class Controller : Actor
    {
        public Rotator ControllerRotator
        {
            get;set;
        }

        public void SetInitialLocationAndRotation(Vector NewLocation, Rotator NewRotation)
        {

        }

        public bool AttachToPawn
        {
            get;
        }

        public bool LineOfSightTo(Actor Other, Vector ViewPoint, bool bAlternateChecks = false)
        {
            return false;
        }

        public void StopMovement()
        {

        }

        public bool IgnoreMoveInput
        {
            get;
            set;
        }

        public bool IgnoreLookInput
        {
            get;
            set;
        }
    }
}
