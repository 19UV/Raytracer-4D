#include "object.h"

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

#include "ray.h"
#include "hit.h"
#include "vector.h"

/** [THE RAY-HYPERSPHERE INTERSECTION ALGORITHM (ooh... scary word) EXPLAINED]
 * An n-dimensional sphere can be defined as the set of points which are a set distance (r) from a point (C).
 * For the sake of simplicity, we will assume that r = 1, and that C = <0, 0, 0, 0>
 *
 * |P - C| = r
 * |P - <0, 0, 0, 0>| = 1
 * |P| = 1
 *
 * We can substitute P with the ray equation (R(t)), because we want to find the t such that the ray equation
 * makes the equality true.
 *
 * |P| = 1
 * |R(t)| = 1
 * |Dt + O| = 1
 *
 * |V| can be defined as sqrt(Vx^2 + Vy^2 + Vz^2 + Vw^2)
 * which is equal to sqrt(Vx*Vx + Vy*Vy + Vz*Vz + Vw*Vw)
 * which is equal to sqrt(V * V) (where * is the dot product operator)
 * therefore...
 *
 * |Dt + O| = 1
 * sqrt((Dt + O) * (Dt + O)) = 1
 * (Dt + O) * (Dt + O) = 1
 *
 * At this point, we are using vector addition, and dot product, which for some reason (TODO: Show why)
 * have smiliar-enough properties to addition and multiplication, that we can effectively FOIL this to
 * expand it into a polynomial.
 *
 * (Dt + O) * (Dt + O) = 1
 * (D*D)t^2 + 2(D*O)t + (O*O) = 1
 * (D*D)t^2 + 2(D*O)t + (O*O) - 1 = 0
 *
 * At this point, all vectors (D and O) are dot-product-ed with each other, meaning that all of the
 * values are scalars, so we'll just replace them with the variables a, b, and c.
 *
 * at^2 + bt + c = 0
 * a = D * D
 * b = 2(D * O)
 * c = (O * O) - 1
 *
 * Now, if you look at this hard enough, you will see that this is a trinomial that can be solved with
 * the quadratic formula (that dumb equation you learned in school).
 *
 * t = (-b +/- sqrt(b^2 - 4ac)) / 2a
 *
 * You will notice that the quadratic formula can give us three types of answers. Their meaning is explained.
 * 0 solutions - when b^2 - 4ac < 0 - This means that the ray NEVER hits the hypersphere
 * 1 solution - when b^2 - 4ac = 0 - This means that the ray hits the hypersphere at EXACTLY one point
 * 2 solutions - when b^2 - 4ac > 0 - This means that the ray hits at two points (ex. goes through the middle)
 *
 * Let's implement this!
*/

/* We can assume that object is not NULL, because this should only be called from intersect(...) */
bool hypersphere_intersect(struct Object* object, struct Ray ray, struct Hit* hit) {
	assert(object->type == OHypersphere);

	/* First, we want to calculate the a, b, and c values */
	const float a = vector_dot(ray.direction, ray.direction);
	const float b = 2.0f * vector_dot(ray.direction, ray.origin);
	const float c = vector_dot(ray.origin, ray.origin) - 1.0f;

	/* Remember that a, b, and c are all scalars, which is why the quadratic formula works! */

	/* Not we want to calculate the discriminant (b^2 - 4ac), because sqrt(-1) will result in an error */
	const float discriminant = (b * b) - (4.0f * a * c);
	if(discriminant < 0.0f) { /* No real solutions (TODO: Can we somehow render these imaginary solutions */
		return false;
	}

	/* We need to worry if a = 0 (which would result in division by zero).
	 * This will only happen if a = <0, 0, 0, 0>, which should never happen.
	 * But we'll just implement this check to make sure (better safe than sorry).
	*/

	assert(a != 0.0f);

	/* If there are two solutions, we only care about the lower one (which is closer to the origin of the ray) */
	const float t = (-b - sqrtf(discriminant)) / (2.0f * a);
	if(t <= 0.0f) { /* The hypersphere is behind/surrounding the ray/camera */
		return false;
	}

	/* After all these checks, we now know that we hit the sphere */
	if(hit != NULL) { /* Because a NULL hit is valid (we just want to know IF it hits) */
		hit->t = t;
		hit->object = object;
	}

	return true;
}
