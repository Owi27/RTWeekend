// Simple basecode showing how to create a window and attach a GRasterSurface
#define GATEWARE_ENABLE_CORE // All libraries need this
#define GATEWARE_ENABLE_SYSTEM // Graphics libs require system level libraries
#define GATEWARE_ENABLE_MATH
#define GATEWARE_ENABLE_MATH2D
#define GATEWARE_ENABLE_GRAPHICS // Enables all Graphics Libraries
// Ignore some GRAPHICS libraries we aren't going to use
#define GATEWARE_DISABLE_GDIRECTX11SURFACE // we have another template for this
#define GATEWARE_DISABLE_GVULKANSURFACE // we have another template for this
#define GATEWARE_DISABLE_GDIRECTX12SURFACE // we have another template for this
#define GATEWARE_DISABLE_GOPENGLSURFACE // we have another template for this
// With what we want & what we don't defined we can include the API
#include "Gateware/Gateware.h"

//const double infinity = std::numeric_limits<double>::infinity();

#define _USE_MATH_DEFINES
#include <math.h>

//usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

////utility funcs
//inline float RandomFloat() //Returns a random real in [0,1).
//{
//    return rand() / (RAND_MAX + 1.0);
//}
//
//inline float RandomFloat(float min, float max) // Returns a random real in [min,max).
//{
//    return min + (max - min) * RandomFloat();
//}

//constants
//TODO: create a ve3 math buffer;

using vec2 = GW::MATH2D::GVECTOR2F;
using vec3 = GW::MATH2D::GVECTOR3F;
using vec4 = GW::MATH::GVECTORF;

//proxies
using pVec2D = GW::MATH2D::GVector2D;
#include "Ray.h"

#include "Interval.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"