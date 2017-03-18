using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public partial struct Vector
    {
        /** A zero vector (0,0,0) */
        public readonly static Vector ZeroVector = new Vector(0, 0, 0);

        /** World up vector (0,0,1) */
        public readonly static Vector UpVector = new Vector(0.0f, 0.0f, 1.0f);

        /** Unreal forward vector (1,0,0) */
        public readonly static Vector ForwardVector = new Vector(1.0f, 0.0f, 0.0f);

        /** Unreal right vector (0,1,0) */
        public readonly static Vector RightVector = new Vector(0.0f, 1.0f, 0.0f);

        /**
         * Constructor initializing all components to a single float value.
         *
         * @param InF Value to set all components to.
         */
        public Vector(float InF) { X = InF; Y = InF; Z = InF; }
        /**
         * Constructor using initial values for each component.
         *
         * @param InX X Coordinate.
         * @param InY Y Coordinate.
         * @param InZ Z Coordinate.
         */
        public Vector(float InX, float InY, float InZ) 
        {
            X = InX;
            Y = InY; 
            Z = InZ; 
        }

        public Vector(Vector InVector) 
        {
            X = InVector.X;
            Y = InVector.Y; 
            Z = InVector.Z; 
        }
        /**
         * Constructor using the XYZ components from a 4D vector.
         *
         * @param V 4D Vector to copy from.
         */
        public Vector(Vector4D V)
        {
            X = V.X;
            Y = V.Y;
            Z = V.Z;
        }

        //隐式转换
        public static implicit operator Vector(Vector4D V)
        {
            return new Vector(V);
        }
        public static implicit operator Vector(Plane V)
        {
            return new Vector(V);
        }

        public override bool Equals(object obj)
        {
            Vector V = (Vector)obj;
            return X == V.X && Y == V.Y && Z == V.Z;
        }
        public override int GetHashCode()
        { return base.GetHashCode(); }
        public static bool operator ==(Vector This, Vector Other)
        {
            return This.Equals(Other);
        }

        public static bool operator !=(Vector This, Vector Other)
        {
            return !This.Equals(Other);
        }

        /**
         * Calculate cross product between this and another vector.
         *
         * @param V The other vector.
         * @return The cross product.
         */
        public static Vector operator ^(Vector A, Vector V)
        {
            return new Vector
            (
            A.Y * V.Z - A.Z * V.Y,
            A.Z * V.X - A.X * V.Z,
            A.X * V.Y - A.Y * V.X
            );
        }


        /**
         * Calculate the cross product of two vectors.
         *
         * @param A The first vector.
         * @param B The second vector.
         * @return The cross product.
         */
        public static Vector CrossProduct(Vector A, Vector B)
        {
            return A ^ B;
        }

        /**
         * Calculate the dot product between this and another vector.
         *
         * @param V The other vector.
         * @return The dot product.
         */
        public static float operator |(Vector A, Vector V)
        {
            return A.X * V.X + A.Y * V.Y + A.Z * V.Z;
        }

        /**
         * Calculate the dot product of two vectors.
         *
         * @param A The first vector.
         * @param B The second vector.
         * @return The dot product.
         */
        public static float DotProduct(Vector A, Vector B)
        {
            return A | B;
        }

        /**
         * Gets the result of component-wise addition of this and another vector.
         *
         * @param V The vector to add to this.
         * @return The result of vector addition.
         */
        public static Vector operator +(Vector A, Vector V)
        {
            return new Vector(A.X + V.X, A.Y + V.Y, A.Z + V.Z);
        }
        /**
         * Gets the result of component-wise subtraction of this by another vector.
         *
         * @param V The vector to subtract from this.
         * @return The result of vector subtraction.
         */
        public static Vector operator -(Vector A, Vector V)
        {
            return new Vector(A.X - V.X, A.Y - V.Y, A.Z - V.Z);
        }
        /**
         * Gets the result of subtracting from each component of the vector.
         *
         * @param Bias How much to subtract from each component.
         * @return The result of subtraction.
         */
        public static Vector operator -(Vector A, float Bias)
        {
            return new Vector(A.X - Bias, A.Y - Bias, A.Z - Bias);
        }
        /**
         * Gets the result of adding to each component of the vector.
         *
         * @param Bias How much to add to each component.
         * @return The result of addition.
         */
        public static Vector operator +(Vector A, float Bias)
        {
            return new Vector(A.X + Bias, A.Y + Bias, A.Z + Bias);
        }
        /**
         * Gets the result of scaling the vector (multiplying each component by a value).
         *
         * @param Scale What to multiply each component by.
         * @return The result of multiplication.
         */
        public static Vector operator *(Vector A, float Scale)
        {
            return new Vector(A.X * Scale, A.Y * Scale, A.Z * Scale);
        }
        /**
         * Gets the result of dividing each component of the vector by a value.
         *
         * @param Scale What to divide each component by.
         * @return The result of division.
         */
        public static Vector operator /(Vector A, float Scale)
        {
            float RScale = 1.0f / Scale;
            return new Vector(A.X * RScale, A.Y * RScale, A.Z * RScale);
        }
        /**
         * Gets the result of component-wise multiplication of this vector by another.
         *
         * @param V The vector to multiply with.
         * @return The result of multiplication.
         */
        public static Vector operator *(Vector A, Vector V)
        {
            return new Vector(A.X * V.X, A.Y * V.Y, A.Z * V.Z);
        }
        /**
         * Gets the result of component-wise division of this vector by another.
         *
         * @param V The vector to divide by.
         * @return The result of division.
         */
        public static Vector operator /(Vector A, Vector V)
        {
            return new Vector(A.X / V.X, A.Y / V.Y, A.Z / V.Z);
        }

        
	    /**
	     * Get a negated copy of the vector.
	     *
	     * @return A negated copy of the vector.
	     */
	    public static Vector operator-(Vector V)
        {
            return new Vector(-V.X,-V.Y,-V.Z);
        }

	    /**
	     * Gets specific component of the vector.
	     *
	     * @param Index the index of vector component
	     * @return reference to component.
	     */
	    public float this[int Index]
        {
            get{
                switch(Index)
                {
                    case 0:
                        return X;
                    case 1:
                        return Y;
                    case 2:
                        return Z;
                    default:
                        throw new System.ArgumentOutOfRangeException();
                }
            }
            set{
                switch(Index)
                {
                    case 0:
                        X = value;
                        break;
                    case 1:
                        Y = value;
                        break;
                    case 2:
                        Z = value;
                        break;
                    default:
                        throw new System.ArgumentOutOfRangeException();
                }
            }
        }


        
	    /**
	     * Set the values of the vector directly.
	     *
	     * @param InX New X coordinate.
	     * @param InY New Y coordinate.
	     * @param InZ New Z coordinate.
	     */
	    public void Set( float InX, float InY, float InZ )
        {
            X = InX; Y=InY; Z=InZ;
        }

	    /**
	     * Get the maximum value of the vector's components.
	     *
	     * @return The maximum value of the vector's components.
	     */
	    public float GetMax()
        {
            return Math.Max(Math.Max(X,Y),Z);
        }

	    /**
	     * Get the maximum absolute value of the vector's components.
	     *
	     * @return The maximum absolute value of the vector's components.
	     */
	    public float GetAbsMax()
        {
            return System.Math.Max(System.Math.Max(System.Math.Abs(X),System.Math.Abs(Y)), System.Math.Abs(Z));
        }

	    /**
	     * Get the minimum value of the vector's components.
	     *
	     * @return The minimum value of the vector's components.
	     */
	    public float GetMin()
        {
            return System.Math.Min(System.Math.Min(X,Y),Z);
        }

	    /**
	     * Get the minimum absolute value of the vector's components.
	     *
	     * @return The minimum absolute value of the vector's components.
	     */
	    public float GetAbsMin()
        {
            return System.Math.Min(System.Math.Min(System.Math.Abs(X), System.Math.Abs(Y)), System.Math.Abs(Z));
        }

	    /** Gets the component-wise min of two vectors. */
	    public Vector ComponentMin(Vector Other)
        {
            return new Vector(System.Math.Min(X, Other.X), System.Math.Min(Y, Other.Y), System.Math.Min(Z, Other.Z));
        }

	    /** Gets the component-wise max of two vectors. */
	    public Vector ComponentMax(Vector Other)
        {
            return new Vector(System.Math.Max(X, Other.X), System.Math.Max(Y, Other.Y), System.Math.Max(Z, Other.Z));
        }

	    /**
	     * Get a copy of this vector with absolute value of each component.
	     *
	     * @return A copy of this vector with absolute value of each component.
	     */
	    public Vector GetAbs()
        {
            return new Vector(System.Math.Abs(X), System.Math.Abs(Y), System.Math.Abs(Z));
        }

	    /**
	     * Get the length (magnitude) of this vector.
	     *
	     * @return The length of this vector.
	     */
	    public float Size()
        {
            return (float)System.Math.Sqrt( X*X + Y*Y + Z*Z );
        }

	    /**
	     * Get the squared length of this vector.
	     *
	     * @return The squared length of this vector.
	     */
	    public float SizeSquared()
        {
            return X*X + Y*Y + Z*Z;
        }

	    /**
	     * Get the length of the 2D components of this vector.
	     *
	     * @return The 2D length of this vector.
	     */
	    public float Size2D()
        {
            return (float)System.Math.Sqrt( X*X + Y*Y );
        }

	    /**
	     * Get the squared length of the 2D components of this vector.
	     *
	     * @return The squared 2D length of this vector.
	     */
	    public float SizeSquared2D()
        {
            return X*X + Y*Y;
        }

	    /**
	     * Checks whether all components of the vector are exactly zero.
	     *
	     * @return true if the vector is exactly zero, false otherwise.
	     */
	    public bool IsZero()
        {
            return X==0.0f && Y==0.0f && Z==0.0f;
        }

	    /**
	     * Normalize this vector in-place if it is large enough, set it to (0,0,0) otherwise.
	     *
	     * @param Tolerance Minimum squared length of vector for normalization.
	     * @return true if the vector was normalized correctly, false otherwise.
	     */
	    public bool Normalize(float Tolerance=Const.SMALL_NUMBER)
        {
            float SquareSum = X*X + Y*Y + Z*Z;
	        if( SquareSum > Tolerance )
	        {
		        float Scale = (float)(1.0f/ System.Math.Sqrt(SquareSum));
		        X *= Scale; Y *= Scale; Z *= Scale;
		        return true;
	        }
	        return false;
        }

	    /**
	     * Checks whether vector is normalized.
	     *
	     * @return true if Normalized, false otherwise.
	     */
	    public bool IsNormalized()
        {
            return (System.Math.Abs(1.0f - SizeSquared()) < Const.THRESH_VECTOR_NORMALIZED);
        }

	    /**
	     * Util to convert this vector into a unit direction vector and its original length.
	     *
	     * @param OutDir Reference passed in to store unit direction vector.
	     * @param OutLength Reference passed in to store length of the vector.
	     */
	    public void ToDirectionAndLength(out Vector OutDir,out float OutLength)
        {
            OutLength = Size();
	        if (OutLength > Const.SMALL_NUMBER)
	        {
		        float OneOverLength = 1.0f/OutLength;
		        OutDir = new Vector(X*OneOverLength, Y*OneOverLength,
			        Z*OneOverLength);
	        }
	        else
	        {
		        OutDir = Vector.ZeroVector;
	        }
        }

	    /**
	     * Get a copy of the vector as sign only.
	     * Each component is set to +1 or -1, with the sign of zero treated as +1.
	     *
	     * @param A copy of the vector with each component set to +1 or -1
	     */
	    public Vector GetSignVector()
        {
            return new Vector
		    (
                System.Math.Sign(X),
                System.Math.Sign(Y),
                System.Math.Sign(Z)
		    );
        }

	    /**
	     * Projects 2D components of vector based on Z.
	     *
	     * @return Projected version of vector based on Z.
	     */
	    public Vector Projection()
        {
            float RZ = 1.0f/Z;
	        return new Vector( X*RZ, Y*RZ, 1 );
        }

	    /**
	     * Calculates normalized version of vector without checking for zero length.
	     *
	     * @return Normalized version of vector.
	     * @see GetSafeNormal()
	     */
	    public Vector GetUnsafeNormal()
        {
            float Scale = (float)(1.0f/ System.Math.Sqrt(X*X+Y*Y+Z*Z));
	        return new Vector( X*Scale, Y*Scale, Z*Scale );
        }
	    /**
	     * Gets the reciprocal of this vector, avoiding division by zero.
	     * Zero components are set to BIG_NUMBER.
	     *
	     * @return Reciprocal of this vector.
	     */
	    public Vector Reciprocal()
        {
            Vector RecVector;
	        if (X!=0.0f)
	        {
		        RecVector.X = 1.0f/X;
	        }
	        else 
	        {
		        RecVector.X = Const.BIG_NUMBER;
	        }
	        if (Y!=0.0f)
	        {
		        RecVector.Y = 1.0f/Y;
	        }
	        else 
	        {
		        RecVector.Y = Const.BIG_NUMBER;
	        }
	        if (Z!=0.0f)
	        {
		        RecVector.Z = 1.0f/Z;
	        }
	        else 
	        {
		        RecVector.Z = Const.BIG_NUMBER;
	        }

	        return RecVector;
        }

	    /**
	     * Check whether X, Y and Z are nearly equal.
	     *
	     * @param Tolerance Specified Tolerance.
	     * @return true if X == Y == Z within the specified tolerance.
	     */
	    public bool IsUniform(float Tolerance=Const.KINDA_SMALL_NUMBER)
        {
            return AllComponentsEqual(Tolerance);
        }

        bool AllComponentsEqual(float Tolerance)
        {
	        return System.Math.Abs( X - Y ) <= Tolerance && System.Math.Abs( X - Z ) <= Tolerance && System.Math.Abs( Y - Z ) <= Tolerance;
        }
	    /**
	     * Mirror a vector about a normal vector.
	     *
	     * @param MirrorNormal Normal vector to mirror about.
	     * @return Mirrored vector.
	     */
	    public Vector MirrorByVector(Vector MirrorNormal )
        {
            return this - MirrorNormal * (2.0f * (this | MirrorNormal));
        }

	    /**
	     * Mirrors a vector about a plane.
	     *
	     * @param Plane Plane to mirror about.
	     * @return Mirrored vector.
	     */
	    public Vector MirrorByPlane(Plane Plane )
        {
            Plane TempPlane = Plane * (2.0f * Plane.PlaneDot(this) );
            return this - TempPlane;//new FVector(TempPlane.X,TempPlane.Y,TempPlane.Z);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Vector RotateAngleAxis(ref Vector _this, float AngleDeg, Vector Axis);
	    /**
	     * Rotates around Axis (assumes Axis.Size() == 1).
	     *
	     * @param Angle Angle to rotate (in degrees).
	     * @param Axis Axis to rotate around.
	     * @return Rotated Vector.
	     */
	    public Vector RotateAngleAxis(float AngleDeg,Vector Axis )
        {
            return RotateAngleAxis(ref this, AngleDeg, Axis);
        }

        /**
	     * Gets a normalized copy of the vector, checking it is safe to do so based on the length.
	     * Returns zero vector if vector length is too small to safely normalize.
	     *
	     * @param Tolerance Minimum squared vector length.
	     * @return A normalized copy if safe, (0,0,0) otherwise.
	     */
        public Vector GetSafeNormal(float Tolerance = Const.SMALL_NUMBER)
        {
	        float SquareSum = X*X + Y*Y + Z*Z;

	        // Not sure if it's safe to add tolerance in there. Might introduce too many errors
	        if( SquareSum == 1.0f )
	        {
		        return this;
	        }		
	        else if( SquareSum < Tolerance )
	        {
		        return Vector.ZeroVector;
	        }
	        float Scale = (float)(1.0f/ System.Math.Sqrt(SquareSum));
	        return new Vector(X*Scale, Y*Scale, Z*Scale);
        }
        /**
	     * Gets a copy of this vector projected onto the input vector.
	     *
	     * @param A	Vector to project onto, does not assume it is normalized.
	     * @return Projected vector.
	     */    
        public Vector ProjectOnTo(Vector A ) 
        { 
	        return (A * ((this | A) / (A | A))); 
        }
        /**
         * Gets a copy of this vector projected onto the input vector, which is assumed to be unit length.
         * 
         * @param  Normal Vector to project onto (assumed to be unit length).
         * @return Projected vector.
         */
        public Vector ProjectOnToNormal(Vector Normal)
        {
	        return (Normal * (this | Normal));
        }

        public override string ToString()
        {
	        return string.Format("X={0} Y={1} Z={2}", X, Y, Z);
        }

        
	    /**
	     * Compare two points and see if they're the same, using a threshold.
	     *
	     * @param P First vector.
	     * @param Q Second vector.
	     * @return Whether points are the same within a threshold. Uses fast distance approximation (linear per-component distance).
	     */
	    public static bool PointsAreSame( Vector P, Vector Q )
        {
        	float Temp;
	        Temp=P.X-Q.X;
	        if( (Temp > -Const.THRESH_POINTS_ARE_SAME) && (Temp < Const.THRESH_POINTS_ARE_SAME) )
	        {
		        Temp=P.Y-Q.Y;
		        if( (Temp > -Const.THRESH_POINTS_ARE_SAME) && (Temp < Const.THRESH_POINTS_ARE_SAME) )
		        {
			        Temp=P.Z-Q.Z;
			        if( (Temp > -Const.THRESH_POINTS_ARE_SAME) && (Temp < Const.THRESH_POINTS_ARE_SAME) )
			        {
				        return true;
			        }
		        }
	        }
	        return false;
        }
	
	    /**
	     * Compare two points and see if they're within specified distance.
	     *
	     * @param Point1 First vector.
	     * @param Point2 Second vector.
	     * @param Dist Specified distance.
	     * @return Whether two points are within the specified distance. Uses fast distance approximation (linear per-component distance).
	     */
	    public static bool PointsAreNear(Vector Point1,Vector Point2, float Dist )
        {
            float Temp;
	        Temp=(Point1.X - Point2.X); if (System.Math.Abs(Temp)>=Dist) return false;
	        Temp=(Point1.Y - Point2.Y); if (System.Math.Abs(Temp)>=Dist) return false;
	        Temp=(Point1.Z - Point2.Z); if (System.Math.Abs(Temp)>=Dist) return false;
	        return true;
        }

	    /**
	     * Calculate the signed distance (in the direction of the normal) between a point and a plane.
	     *
	     * @param Point The Point we are checking.
	     * @param PlaneBase The Base Point in the plane.
	     * @param PlaneNormal The Normal of the plane (assumed to be unit length).
	     * @return Signed distance between point and plane.
	     */
	    public static float PointPlaneDist(Vector Point,Vector PlaneBase,Vector PlaneNormal )
        {
            return (Point - PlaneBase) | PlaneNormal;
        }

	    /**
	     * Calculate the projection of a point on the given plane.
	     *
	     * @param Point The point to project onto the plane
	     * @param Plane The plane
	     * @return Projection of Point onto Plane
	     */
        public static Vector PointPlaneProject(Vector Point, Plane Plane)
        {
            return Point - Plane * Plane.PlaneDot(Point);
        }

	    /**
	     * Calculate the projection of a point on the plane defined by counter-clockwise (CCW) points A,B,C.
	     *
	     * @param Point The point to project onto the plane
	     * @param A 1st of three points in CCW order defining the plane 
	     * @param B 2nd of three points in CCW order defining the plane
	     * @param C 3rd of three points in CCW order defining the plane
	     * @return Projection of Point onto plane ABC
	     */
        public static Vector PointPlaneProject( Vector Point,  Vector A,  Vector B,  Vector C)
        {
	        //Compute the plane normal from ABC
	        Plane Plane = new Plane(A, B, C);

	        //Find the distance of X from the plane
	        //Add the distance back along the normal from the point
            return Point - Plane * Plane.PlaneDot(Point);
        }

	    /**
	    * Calculate the projection of a point on the plane defined by PlaneBase and PlaneNormal.
	    *
	    * @param Point The point to project onto the plane
	    * @param PlaneBase Point on the plane
	    * @param PlaneNorm Normal of the plane (assumed to be unit length).
	    * @return Projection of Point onto plane
	    */
	    public static Vector PointPlaneProject( Vector Point,  Vector PlaneBase,  Vector PlaneNormal)
        {
            //Find the distance of X from the plane
	        //Add the distance back along the normal from the point
	        return Point - PlaneNormal * Vector.PointPlaneDist(Point,PlaneBase,PlaneNormal);
        }

	    /**
	     * Calculate the projection of a vector on the plane defined by PlaneNormal.
	     * 
	     * @param  V The vector to project onto the plane.
	     * @param  PlaneNormal Normal of the plane (assumed to be unit length).
	     * @return Projection of V onto plane.
	     */
	    public static  Vector VectorPlaneProject(Vector V ,Vector PlaneNormal)
        {
            return V - V.ProjectOnToNormal(PlaneNormal);
        }

	    /**
	     * Euclidean distance between two points.
	     *
	     * @param V1 The first point.
	     * @param V2 The second point.
	     * @return The distance between two points.
	     */
	    public static float Dist( Vector V1, Vector V2 )
        {
            return (float)System.Math.Sqrt( (V2.X-V1.X)*(V2.X-V1.X) + (V2.Y-V1.Y)*(V2.Y-V1.Y) + (V2.Z-V1.Z)*(V2.Z-V1.Z) );
        }

	    /**
	     * Squared distance between two points.
	     *
	     * @param V1 The first point.
	     * @param V2 The second point.
	     * @return The squared distance between two points.
	     */
	    public static float DistSquared( Vector V1, Vector V2 )
        {
            return (V2.X-V1.X)*(V2.X-V1.X) + (V2.Y-V1.Y)*(V2.Y-V1.Y) + (V2.Z-V1.Z)*(V2.Z-V1.Z);
        }

	    /**
	     * Squared distance between two points in the XY plane only.
	     *	
	     * @param V1 The first point.
	     * @param V2 The second point.
	     * @return The squared distance between two points in the XY plane
	     */
	    public static float DistSquaredXY(Vector V1, Vector V2 )
        {
            //return FMath::Square(V2.X-V1.X) + FMath::Square(V2.Y-V1.Y);
            return (V2.X-V1.X) * (V2.X-V1.X) + (V2.Y-V1.Y)*(V2.Y-V1.Y);
        }

        /**
	     * Converts a vector containing radian values to a vector containing degree values.
	     *
	     * @param RadVector	Vector containing radian values
	     * @return Vector  containing degree values
	     */
	    public static Vector RadiansToDegrees(Vector RadVector)
        {
            return RadVector * (180.0f / Const.PI);
        }

	    /**
	     * Converts a vector containing degree values to a vector containing radian values.
	     *
	     * @param DegVector	Vector containing degree values
	     * @return Vector containing radian values
	     */
	    public static Vector DegreesToRadians( Vector DegVector)
        {
            return DegVector * (Const.PI / 180.0f);
        }
    }



}
