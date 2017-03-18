using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public partial struct Quat
    {
        public readonly static Quat Identity = new Quat(0, 0, 0, 1);

        //public FQuat() { X = 0; Y = 0; Z = 0; W = 0; }

        public Quat(EForceInit init) { X = 0; Y = 0; Z = 0; W = init == EForceInit.ForceInitToZero ? 0 : 1; }

        public Quat(float InX, float InY, float InZ, float InW)
        {
            X = InX;
            Y = InY;
            Z = InZ;
            W = InW;
        }

        public Quat(Quat Q)
        {
            X = Q.X;
            Y = Q.Y;
            Z = Q.Z;
            W = Q.W;
        }

        public Quat(Matrix M)
        {
            this = MakeFromMatrix(M);
        }
        public Quat(Rotator R)
        {
            this = R.Quaternion();
        }
        public Quat(Vector Axis, float AngleRad)
        {
            float half_a = 0.5f * AngleRad;
            float s, c;
            Math.SinCos(out s, out c, half_a);

            X = s * Axis.X;
            Y = s * Axis.Y;
            Z = s * Axis.Z;
            W = c;

            //DiagnosticCheckNaN();
        }

        /**
	     * Gets the result of adding a Quaternion to this.
	     * This is a component-wise addition; composing quaternions should be done via multiplication.
	     *
	     * @param Q The Quaternion to add.
	     * @return The result of addition.
	     */
        public static Quat operator +(Quat A,Quat Q)
        {
            return new Quat(A.X + Q.X, A.Y + Q.Y, A.Z + Q.Z, A.W + Q.W);
        }

        /**
         * Gets the result of subtracting a Quaternion to this.
         * This is a component-wise subtraction; composing quaternions should be done via multiplication.
         *
         * @param Q The Quaternion to subtract.
         * @return The result of subtraction.
         */
        public static Quat operator -(Quat A, Quat Q)
        {
            return new Quat(A.X - Q.X, A.Y - Q.Y, A.Z - Q.Z, A.W - Q.W);
        }

        /**
         * Checks whether another Quaternion is equal to this, within specified tolerance.
         *
         * @param Q The other Quaternion.
         * @param Tolerance Error Tolerance.
         * @return true if two Quaternion are equal, within specified tolerance, otherwise false.
         */
        public override bool Equals(object Obj)
        {
            Quat Q = (Quat)Obj;
            float Tolerance = Const.KINDA_SMALL_NUMBER;
            return (System.Math.Abs(X - Q.X) <= Tolerance && System.Math.Abs(Y - Q.Y) <= Tolerance && System.Math.Abs(Z - Q.Z) <= Tolerance && System.Math.Abs(W - Q.W) <= Tolerance)
        || (System.Math.Abs(X + Q.X) <= Tolerance && System.Math.Abs(Y + Q.Y) <= Tolerance && System.Math.Abs(Z + Q.Z) <= Tolerance && System.Math.Abs(W + Q.W) <= Tolerance);
        }
        public override int GetHashCode()
        { return base.GetHashCode(); }
        /**
         * Checks whether this Quaternion is an Identity Quaternion.
         * Assumes Quaternion tested is normalized.
         *
         * @return true if Quaternion is a normalized Identity Quaternion.
         */
        public bool IsIdentity()
        {
            return ((W * W) > ((1.0f - Const.DELTA) * (1.0f - Const.DELTA)));
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Quat Multiply(ref Quat _this,ref Quat Other);
        /**
         * Gets the result of multiplying this by another quaternion (this * Q).
         *
         * Order matters when composing quaternions: C = A * B will yield a quaternion C that logically
         * first applies B then A to any subsequent transformation (right first, then left).
         *
         * @param Q The Quaternion to multiply this by.
         * @return The result of multiplication (this * Q).
         */
        public static Quat operator*(Quat A, Quat Q )
        {
            return Multiply(ref A,ref Q);
        }

        /**
         * Rotate a vector by this quaternion.
         *
         * @param V the vector to be rotated
         * @return vector after rotation
         * @see RotateVector()
         */
        public static Vector operator *(Quat A, Vector V)
        {
            return A.RotateVector(V);
        }

        /** 
         * Multiply this by a matrix.
         * This matrix conversion came from
         * http://www.m-hikari.com/ija/ija-password-2008/ija-password17-20-2008/aristidouIJA17-20-2008.pdf
         * used for non-uniform scaling transform.
         *
         * @param M Matrix to multiply by.
         * @return Matrix result after multiplication.
         */
        //FMatrix operator*( const FMatrix& M ) const;

        /**
         * Get the result of scaling this quaternion.
         *
         * @param Scale The scaling factor.
         * @return The result of scaling.
         */
        public static Quat operator *(Quat A, float Scale)
        {
            A.X *= Scale;
            A.Y *= Scale;
            A.Z *= Scale;
            A.W *= Scale;

            //DiagnosticCheckNaN();

            return A;
        }

        /**
         * Divide this quaternion by scale.
         *
         * @param Scale What to divide by.
         * @return new Quaternion of this after division by scale.
         */
        public static Quat operator /(Quat A, float Scale)
        {
            float Recip = 1.0f / Scale;
            return new Quat(A.X * Recip, A.Y * Recip, A.Z * Recip, A.W * Recip);
        }

        /**
         * Checks whether two quaternions are identical.
         * This is an exact comparison per-component;see Equals() for a comparison
         * that allows for a small error tolerance and flipped axes of rotation.
         *
         * @param Q The other quaternion.
         * @return true if two quaternion are identical, otherwise false.
         * @see Equals()
         */
        public static bool operator ==(Quat A, Quat Q)
        {
            return A.Equals(Q);
        }

        /**
         * Checks whether two quaternions are not identical.
         *
         * @param Q The other quaternion.
         * @return true if two quaternion are not identical, otherwise false.
         */
        public static bool operator !=(Quat A, Quat Q)
        {
            return !A.Equals(Q);
        }

        /**
         * Calculates dot product of two quaternions.
         *
         * @param Q The other quaternions.
         * @return The dot product.
         */
        public static float operator |(Quat A, Quat Q)
        {
            return A.X * Q.X + A.Y * Q.Y + A.Z * Q.Z + A.W * Q.W;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Quat MakeFromMatrix(ref Matrix Matrix);
        public static Quat MakeFromMatrix(Matrix Matrix)
        {
            return MakeFromMatrix(ref Matrix);
        }
        /**
	     * Convert a vector of floating-point Euler angles (in degrees) into a Quaternion.
	     * 
	     * @param Euler the Euler angles
	     * @return constructed FQuat
	     */
        public static Quat MakeFromEuler(Vector Euler)
        {
            return UnrealEngine.Rotator.MakeFromEuler(Euler).Quaternion();
        }

        /** Convert a Quaternion into floating-point Euler angles (in degrees). */
        public Vector Euler()
        {
            return Rotator().Euler();
        }

        /**
         * Normalize this quaternion if it is large enough.
         * If it is too small, returns an identity quaternion.
         *
         * @param Tolerance Minimum squared length of quaternion for normalization.
         */
        public void Normalize(float Tolerance = Const.SMALL_NUMBER)
        {
            float SquareSum = X * X + Y * Y + Z * Z + W * W;

            if (SquareSum >= Tolerance)
            {
                float Scale = Math.InvSqrt(SquareSum);

                X *= Scale;
                Y *= Scale;
                Z *= Scale;
                W *= Scale;
            }
            else
            {
                this = Quat.Identity;
            }
        }

        /**
         * Get a normalized copy of this quaternion.
         * If it is too small, returns an identity quaternion.
         *
         * @param Tolerance Minimum squared length of quaternion for normalization.
         */
        public Quat GetNormalized(float Tolerance = Const.SMALL_NUMBER)
        {
            Quat Result = this;
            Result.Normalize(Tolerance);
            return Result;
        }

        // Return true if this quaternion is normalized
        public bool IsNormalized()
        {
            return (System.Math.Abs(1.0f - SizeSquared()) < Const.THRESH_QUAT_NORMALIZED);
        }

        /**
         * Get the length of this quaternion.
         *
         * @return The length of this quaternion.
         */
        public float Size()
        {
            return (float)(System.Math.Sqrt(X * X + Y * Y + Z * Z + W * W));
        }

        /**
         * Get the length squared of this quaternion.
         *
         * @return The length of this quaternion.
         */
        public float SizeSquared()
        {
            return (X * X + Y * Y + Z * Z + W * W);
        }

        /** 
         * get the axis and angle of rotation of this quaternion
         *
         * @param Axis{out] vector of axis of the quaternion
         * @param Angle{out] angle of the quaternion
         * @warning : assumes normalized quaternions.
         */
        public void ToAxisAndAngle(out Vector Axis, out float Angle)
        {
            Angle = (float)(2.0f * System.Math.Acos(W));
            Axis = GetRotationAxis();
        }

        /**
         * Rotate a vector by this quaternion.
         *
         * @param V the vector to be rotated
         * @return vector after rotation
         */
        public Vector RotateVector(Vector V)
        {
            // http://people.csail.mit.edu/bkph/articles/Quaternions.pdf
            // V' = V + 2w(Q x V) + (2Q x (Q x V))
            // refactor:
            // V' = V + w(2(Q x V)) + (Q x (2(Q x V)))
            // T = 2(Q x V);
            // V' = V + w*(T) + (Q x T)

            Vector Q = new Vector(X, Y, Z);
            Vector T = UnrealEngine.Vector.CrossProduct(Q, V) * 2.0f;
            Vector Result = V + (T * W) + UnrealEngine.Vector.CrossProduct(Q, T);
            return Result;
        }

        /**
         * Rotate a vector by the inverse of this quaternion.
         *
         * @param V the vector to be rotated
         * @return vector after rotation by the inverse of this quaternion.
         */
        public Vector UnrotateVector(Vector V)
        {
            Vector Q = new Vector(-X, -Y, -Z); // Inverse
            Vector T = UnrealEngine.Vector.CrossProduct(Q, V) * 2.0f;
            Vector Result = V + (T * W) + UnrealEngine.Vector.CrossProduct(Q, T);
            return Result;
        }

        /**
         * @return quaternion with W=0 and V=theta*v.
         */
        public Quat Log()
        {
            Quat Result = new UnrealEngine.Quat();
            Result.W = 0.0f;

            if (System.Math.Abs(W) < 1.0f)
            {
                float Angle = (float)System.Math.Acos(W);
                float SinAngle = (float)System.Math.Sin(Angle);

                if (System.Math.Abs(SinAngle) >= Const.SMALL_NUMBER)
                {
                    float Scale = Angle / SinAngle;
                    Result.X = Scale * X;
                    Result.Y = Scale * Y;
                    Result.Z = Scale * Z;

                    return Result;
                }
            }

            Result.X = X;
            Result.Y = Y;
            Result.Z = Z;

            return Result;
        }

        /**
         * @note Exp should really only be used after Log.
         * Assumes a quaternion with W=0 and V=theta*v (where |v| = 1).
         * Exp(q) = (sin(theta)*v, cos(theta))
         */
        public Quat Exp()
        {
            float Angle = (float)System.Math.Sqrt(X * X + Y * Y + Z * Z);
            float SinAngle = (float)System.Math.Sin(Angle);

            Quat Result = new Quat();
            Result.W = (float)System.Math.Cos(Angle);

            if (System.Math.Abs(SinAngle) >= Const.SMALL_NUMBER)
            {
                float Scale = SinAngle / Angle;
                Result.X = Scale * X;
                Result.Y = Scale * Y;
                Result.Z = Scale * Z;
            }
            else
            {
                Result.X = X;
                Result.Y = Y;
                Result.Z = Z;
            }

            return Result;
        }

        /**
         * @return inverse of this quaternion
         */
        public Quat Inverse()
        {
            return new Quat(-X, -Y, -Z, W);
        }

        /**
         * Enforce that the delta between this Quaternion and another one represents
         * the shortest possible rotation angle
         */
        public void EnforceShortestArcWith(Quat OtherQuat)
        {
            float DotResult = (OtherQuat | this);
            float Bias = DotResult > 0 ? 1.0f : -1.0f;

            X *= Bias;
            Y *= Bias;
            Z *= Bias;
            W *= Bias;
        }

        /** Get the forward direction (X axis) after it has been rotated by this Quaternion. */
        public Vector GetAxisX()
        {
            return RotateVector(new Vector(1.0f, 0.0f, 0.0f));
        }

        /** Get the right direction (Y axis) after it has been rotated by this Quaternion. */
        public Vector GetAxisY()
        {
            return RotateVector(new Vector(0.0f, 1.0f, 0.0f));
        }

        /** Get the up direction (Z axis) after it has been rotated by this Quaternion. */
        public Vector GetAxisZ()
        {
            return RotateVector(new Vector(0.0f, 0.0f, 1.0f));
        }

        /** Get the forward direction (X axis) after it has been rotated by this Quaternion. */
        public Vector GetForwardVector()
        {
            return GetAxisX();
        }

        /** Get the right direction (Y axis) after it has been rotated by this Quaternion. */
        public Vector GetRightVector()
        {
            return GetAxisY();
        }

        /** Get the up direction (Z axis) after it has been rotated by this Quaternion. */
        public Vector GetUpVector()
        {
            return GetAxisZ();
        }

        /** Convert a rotation into a unit vector facing in its direction. Equivalent to GetForwardVector(). */
        public Vector Vector()
        {
            return GetAxisX();
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Rotator Rotator(ref Quat _this);
        /** Get the FRotator representation of this Quaternion. */
        public Rotator Rotator()
        {
            return Rotator(ref this);
        }

        /**
         * Get the axis of rotation of the Quaternion.
         * This is the axis around which rotation occurs to transform the canonical coordinate system to the target orientation.
         * For the identity Quaternion which has no such rotation, FVector(1,0,0) is returned.
         */
        public Vector GetRotationAxis()
        {
            // Ensure we never try to sqrt a neg number
            float S = (float)(System.Math.Sqrt(Math.Max(1.0f - (W * W), 0.0f)));

            if (S >= 0.0001f)
            {
                return new Vector(X / S, Y / S, Z / S);
            }

            return new Vector(1.0f, 0.0f, 0.0f);
        }

        /**
         * Get a textual representation of the vector.
         *
         * @return Text describing the vector.
         */
        public override string ToString()
        {
            return string.Format("X={0} Y={1} Z={2} W={3}", X, Y, Z, W);
        }
    }
}
