using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class SplineMeshComponent : StaticMeshComponent
    {
        public void UpdateMesh()
        {

        }

        public Vector StartPosition
        {
            get;
            set;
        }

        public Vector StartTangent
        {
            get;
            set;
        }

        public Vector EndPosition
        {
            get;
            set;
        }

        public Vector GetEndTangent
        {
            get;
            set;
        }

        public Vector2D StartScale
        {
            get;
            set;
        }
    
        public float StartRoll
        {
            get;
            set;
        }

        public Vector2D StartOffset
        {
            get;
            set;
        }

        public Vector2D EndScale
        {
            get;
            set;
        }
    
        public float GetEndRoll
        {
            get;
            set;
        }
    
        public Vector2D EndOffset
        {
            get;
            set;
        }        
        
        public enum SplineMeshAxis
        {
            X,
            Y,
            Z,
        }
    
        public SplineMeshAxis ForwardAxis
        {
            get;
            set;
        }
        
        public Vector SplineUpDir
        {
            get;
            set;
        }

        public float BoundaryMin
        {
            get;
            set;
        }

        public float BoundaryMax
        {
            get;
            set;
        }

    }
}
