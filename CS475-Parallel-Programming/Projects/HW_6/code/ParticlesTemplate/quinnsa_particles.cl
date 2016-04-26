typedef float4 point;
typedef float4 vector;
typedef float4 color;
typedef float4 sphere;


vector
Bounce( vector in, vector n )
{
	vector out = in - 2.*n*dot(in.xyz, n.xyz);
	out.w = 0.;
	return out;
}

vector
BounceSphere( point p, vector in, sphere s )
{
	vector n;
	n.xyz = fast_normalize( p.xyz - s.xyz );
	n.w = 0.;
	return Bounce( in, n );
}

bool
IsInsideSphere( point p, sphere s )
{
	float r = fast_length( p.xyz - s.xyz );
	return  ( r < s.w );
}

kernel
void
Particle( global point *dPobj, global vector *dVel, global color *dCobj )
{
	const float4 G       = (float4) ( 0., -9.8, 0., 0. );
	const float  DT      = 0.1;
	const sphere Sphere1 = (sphere)( -100., -800., 0.,  600. );
	const sphere Sphere2 = (sphere)( 800., -1000., 0.,  200. );
	const sphere Sphere3 = (sphere)( 0., -850., 1050.,  400. );
	int gid = get_global_id( 0 );

	point  p = dPobj[gid];
	vector v = dVel[gid];
    color  cp = dCobj[gid];
	point  pp = p + v*DT + .5*DT*DT*G;
	vector vp = v + G*DT;
	pp.w = 1.;
	vp.w = 0.;
    

	if( IsInsideSphere( pp, Sphere1 ) )
	{
		vp = BounceSphere( p, v, Sphere1 );
		pp = p + vp*DT + .5*DT*DT*G;
        cp = (color)(.9, 0., 0., 0.);
	}
	if( IsInsideSphere( pp, Sphere2 ) )
	{
		vp = BounceSphere( p, v, Sphere2 );
		pp = p + vp*DT + .5*DT*DT*G;
        cp = (color)(0., .9, 0., 0.);
	}
	if( IsInsideSphere( pp, Sphere3 ) )
	{
		vp = BounceSphere( p, v, Sphere3 );
		pp = p + vp*DT + .5*DT*DT*G;
        cp = (color)(0., 0., 9., 0.);
	}

	dPobj[gid] = pp;
	dVel[gid]  = vp;
    dCobj[gid] = cp;
}
