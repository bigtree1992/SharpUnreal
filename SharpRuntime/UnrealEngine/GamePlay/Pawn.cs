using System;
using System.Collections.Generic;


namespace UnrealEngine
{
    public class Pawn : Actor
    {
        public PawnMovementComponent MovementComponent
        {
            get;
        }

        public bool UseCtrlRotationPith
        {
            get;
            set;
        }

        public bool UseCtrlRotationYaw
        {
            get;
            set;
        }

        public bool UseCtrlRotationRoll
        {
            get;
            set;
        }

        public bool CanAffectNavigationGeneration
        {
            get;
            set;
        }

        public float BaseEyeHeight
        {
            get;
            set;
        }

        public bool IsControlled
        {
            get;
        }

        public Controller Controller
        {
            get;
        }

        public Rotator ControllerRatator
        {
            get;
        }

        public Vector NavAgentLocatioin
        {
            get;
        }

        public Rotator BaseAimRotaion
        {
            get;
        }

        public void AddMovementInput(Vector worldDir,float scaleValue,bool force)
        {
        }

        public Vector PendingMovementInputVector
        {
            get;
        }

        public Vector LastMovementInputVector
        {
            get;
        }

        public Vector ConsumeMovementInputVector
        {
            get;
        }

        public void AddControllerPitchInput(float Val)
        {

        }

        public void AddControllerYawInput(float Val)
        {

        }

        public void AddControllerRollInput(float Val)
        {

        }

        public bool IsMoveInputIgnored
        {
            get;
        }
    }

}
