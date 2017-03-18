namespace UnrealEngine
{
    public partial struct Plane
    {

        /**
	     * Gets specific component of the vector.
	     *
	     * @param Index the index of vector component
	     * @return reference to component.
	     */
        public float this[int Index]
        {
            get
            {
                switch (Index)
                {
                    case 0:
                        return X;
                    case 1:
                        return Y;
                    case 2:
                        return Z;
                    case 3:
                        return W;
                    default:
                        throw new System.ArgumentOutOfRangeException();
                }
            }
            set
            {
                switch (Index)
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
                    case 3:
                        W = value;
                        break;
                    default:
                        throw new System.ArgumentOutOfRangeException();
                }
            }
        }


        
	    /**
	     * Constructor.
	     *
	     * @param V 4D vector to set up plane.
	     */
	    public Plane(Vector4D V )
        {
            X = V.X;
            Y = V.Y;
            Z = V.Z;
            W = V.W;
        }

	    /**
	     * Constructor.
	     *
	     * @param InX X Coordinate.
	     * @param InY Y Coordinate.
	     * @param InZ Z Coordinate.
	     * @param InW W Coordinate.
	     */
	    public Plane( float InX, float InY, float InZ, float InW )
        {
            X = InX;
            Y = InY;
            Z = InZ;
            W = InW;
        }

	    /**
	     * Constructor.
	     *
	     * @param InNormal Plane Normal Vector.
	     * @param InW Plane W Coordinate.
	     */
	    public Plane( Vector InNormal, float InW )
        {
            X = InNormal.X;
            Y = InNormal.Y;
            Z = InNormal.Z;
            W = InW;
        }

	    /**
	     * Constructor.
	     *
	     * @param InBase Base point in plane.
	     * @param InNormal Plane Normal Vector.
	     */
	    public Plane( Vector InBase,Vector InNormal )
        {
            X = InBase.X;
            Y = InBase.Y;
            Z = InBase.Z;
            W = (InBase | InNormal);
        }

	    /**
	     * Constructor.
	     *
	     * @param A First point in the plane.
	     * @param B Second point in the plane.
	     * @param C Third point in the plane.
	     */
	    public Plane( Vector A, Vector B, Vector C )
        {
            Vector This = new Vector( ((B-A)^(C-A)).GetSafeNormal() );
            X = This.X;
            Y = This.Y;
            Z = This.Z;
            W = A | This;
        }

	    // Functions.

	    /**
	     * Calculates distance between plane and a point.
	     *
	     * @param P The other point.
	     * @return >0: point is in front of the plane, <0: behind, =0: on the plane.
	     */
	    public float PlaneDot(Vector P )
        {
            return X*P.X + Y*P.Y + Z*P.Z - W;
        }

	    /**
	     * Get a flipped version of the plane.
	     *
	     * @return A flipped version of the plane.
	     */
	    public Plane Flip()
        {
            return new Plane(-X,-Y,-Z,-W);
        }

	    /**
	     * Get the result of transforming the plane by a Matrix.
	     *
	     * @param M The matrix to transform plane with.
	     * @return The result of transform.
	     */
	    public Plane TransformBy(Matrix M )
        {
            Matrix tmpTA = M.TransposeAdjoint();
            float DetM = M.Determinant();
            return this.TransformByUsingAdjointT(M, DetM, tmpTA);
        }

	    /**
	     * You can optionally pass in the matrices transpose-adjoint, which save it recalculating it.
	     * MSM: If we are going to save the transpose-adjoint we should also save the more expensive
	     * determinant.
	     *
	     * @param M The Matrix to transform plane with.
	     * @param DetM Determinant of Matrix.
	     * @param TA Transpose-adjoint of Matrix.
	     * @return The result of transform.
	     */
	    public Plane TransformByUsingAdjointT(Matrix M, float DetM,Matrix TA )
        {
            Vector newNorm = TA.TransformVector(new Vector(X,Y,Z)).GetSafeNormal();

            if (DetM < 0.0f)
            {
                newNorm *= -1.0f;
            }

            return new Plane(M.TransformPosition(this * W), newNorm);
        }

	    /**
	     * Check if two planes are identical.
	     *
	     * @param V The other plane.
	     * @return true if planes are identical, otherwise false.
	     */
	    public static bool operator==(Plane A,Plane V )
        {
            return A.Equals(V);
        }

	    /**
	     * Check if two planes are different.
	     *
	     * @param V The other plane.
	     * @return true if planes are different, otherwise false.
	     */
	    public static bool operator!=(Plane A,Plane V ) 
        {
            return !A.Equals(V);
        }

	    /**
	     * Checks whether two planes are equal within specified tolerance.
	     *
	     * @param V The other plane.
	     * @param Tolerance Error Tolerance.
	     * @return true if the two planes are equal within specified tolerance, otherwise false.
	     */
	    public bool Equals(Plane V, float Tolerance=Const.KINDA_SMALL_NUMBER)
        {
            return System.Math.Abs(X-V.X) < Tolerance && System.Math.Abs(Y-V.Y) < Tolerance && System.Math.Abs(Z-V.Z) < Tolerance && System.Math.Abs(W-V.W) < Tolerance;
        }

        public override bool Equals(object obj)
        {
 	         return Equals((Plane)obj);
        }
        public override int GetHashCode()
        { return base.GetHashCode(); }
	    /**
	     * Calculates dot product of two planes.
	     *
	     * @param V The other plane.
	     * @return The dot product.
	     */
	    public static float operator|(Plane A,Plane V )
        {
            return A.X*V.X + A.Y*V.Y + A.Z*V.Z + A.W*V.W;
        }

	    /**
	     * Gets result of adding a plane to this.
	     *
	     * @param V The other plane.
	     * @return The result of adding a plane to this.
	     */
	    public static Plane operator+(Plane A,Plane V )
        {
            return new Plane( A.X + V.X, A.Y + V.Y, A.Z + V.Z, A.W + V.W );
        }

	    /**
	     * Gets result of subtracting a plane from this.
	     *
	     * @param V The other plane.
	     * @return The result of subtracting a plane from this.
	     */
	    public static Plane operator-(Plane A,Plane V )
        {
            return new Plane( A.X - V.X, A.Y - V.Y, A.Z - V.Z, A.W - V.W );
        }

	    /**
	     * Gets result of dividing a plane.
	     *
	     * @param Scale What to divide by.
	     * @return The result of division.
	     */
	    public static Plane operator/(Plane A, float Scale )
        {
            float RScale = 1.0f/Scale;
	        return new Plane( A.X * RScale, A.Y * RScale, A.Z * RScale, A.W * RScale );
        }

	    /**
	     * Gets result of scaling a plane.
	     *
	     * @param Scale The scaling factor.
	     * @return The result of scaling.
	     */
	    public static Plane operator*(Plane A, float Scale )
        {
            return new Plane( A.X * Scale, A.Y * Scale, A.Z * Scale, A.W * Scale );
        }

	    /**
	     * Gets result of multiplying a plane with this.
	     *
	     * @param V The other plane.
	     * @return The result of multiplying a plane with this.
	     */
        public static Plane operator *(Plane A, Plane V)
        {
            return new Plane(A.X * V.X, A.Y * V.Y, A.Z * V.Z, A.W * V.W);
        }
    }
}
