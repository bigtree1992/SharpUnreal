using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class SplineComponent : PrimitiveComponent 
    {
        public float Duration
        {
            get;
            set;
        }
   
        public bool DrawDebug
        {
            get;
            set;
        }
 
        public Vector DefaultUpVector
        {
            get;
            set;
        }

        public void UpdateSpline()
        {

        }
        
        public LinearColor UnselectedSplineSegmentColor
        {
            get;
            set;
        }

        public LinearColor SelectedSplineSegmentColor
        {
            get;
            set;
        }

        public bool ClosedLoop
        {
            get;
            set;
        }
 
        public void SetLocationAtSplinePoint(int PointIndex, Vector InLocation, SplineCoordinateSpace CoordinateSpace, bool bUpdateSpline = true)
        {

        }
               
        public int NumberOfSplinePoints
        {
            get;
        }
        
        public Transform GetTransformAtSplinePoint(int PointIndex, SplineCoordinateSpace CoordinateSpace, bool bUseScale = false)
        {
            return Transform.Identity;
        }
        
        public float GetDistanceAlongSplineAtSplinePoint(int PointIndex)
        {
            return 0.0f;
        }

        public float SplineLength
        {
            get;
        }           
                
        public Transform GetTransformAtDistanceAlongSpline(float Distance, SplineCoordinateSpace CoordinateSpace, bool bUseScale = false)
        {
            return Transform.Identity;
        }
              
        public Transform GetTransformAtTime(float Time, SplineCoordinateSpace CoordinateSpace, bool bUseConstantVelocity = false, bool bUseScale = false)
        {
            return Transform.Identity;
        }
       
        public Transform FindTransformClosestToWorldLocation(Vector WorldLocation, SplineCoordinateSpace CoordinateSpace, bool bUseScale = false)
        {
            return Transform.Identity;
        } 
    }
}
