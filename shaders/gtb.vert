#extension GL_EXT_gpu_shader4 : require
const int numShifts = 5;
const int maxPresses = 100;
uniform float frame;
uniform vec4 cameraPos;
uniform float inputShifts[numShifts];
uniform float rotation;
uniform float framesSincePress[maxPresses];

flat varying vec4 position;
flat varying vec4 normal;
flat varying vec4 colorShift = vec4(0);
varying vec3 params;

// Arguments
//   point: a point that has been projected onto the circle at the origin
//   pointOfRotation: the point to rotate 'point' about
//   zDist: how far away the original point was from the origin before
//          it was projected to the origin
//   rCenter: the radius of the circle at the origin
vec4 rotatePoint(vec4 point, vec4 pointOfRotation, float zDist, float rCenter) {
    vec4 newPoint = point;
    vec4 r = pointOfRotation - point;
    float radius = length(r);
    r = normalize(r);
    // Calculating theta in this manner ensures that points that are
    // initially opposite from one another remain so after rotation
    float theta = asin(zDist/rCenter);
    // Shift point towards point of rotation
    newPoint += (radius - radius*cos(theta))*r;
    // Shift the point forward
    newPoint.z += radius*sin(theta);
    return newPoint;
}

// Since the tunnel goes in the +z direction the x axis is flipped.
void main()
{
    // Initial stuff //
    params = gl_Normal; // passed in with glNormal3f()
    vec4 newVert = gl_Vertex;
    vec4 origin = vec4(0., 0., cameraPos.z, 1.);
    float zDist = gl_Vertex.z - origin.z;

    // Add white bands for inputShifts[4] close to 0 //
    colorShift += (1. - inputShifts[4])*(sin(gl_Vertex.z) + 1.)/4.;
    
    // Apply displacement wave //
    for (int i = 0; i < maxPresses; i++) {
        if (framesSincePress[i] != -1.) {
            vec4 outward = gl_Vertex - vec4(0., 0., gl_Vertex.z, 1.);
            float x = zDist - framesSincePress[i];
            newVert += .5*exp((-pow(x, 2.))/50.)*outward;
            colorShift.b += .8*exp((-pow(x, 2.))/20.);
        }
    }
    
    // Compute shifted tunnel vertex //
    // First calculate the point of rotation based on inputs
    vec4 dir = vec4(-sin(rotation*1.2), cos(rotation*1.2), 0., 0.);
    float curvatureFactor = sin(pow(inputShifts[0] + .01, 0.3)*1.57);
    if (params[0] < 0.) curvatureFactor = 0.; // for pause menu
    float rCenter = 7000. - 6800.*curvatureFactor;
    vec4 pointOfRotation = origin + rCenter*dir;
    // Next calculate the new center (for calculating a normal)
    // by rotating around the point of rotation
    vec4 newCenter = rotatePoint(origin, pointOfRotation, zDist, rCenter);
    // For calculating the new vertex, we have to shift
    // the point of rotation up/down relative to the axis
    // of rotation (visualized as a line of rotation)
    vec4 r = pointOfRotation - origin;
    r = normalize(r);
    // Need up relative to the axis of rotation, so
    // rotate r 90 degrees
    // Remember we have +x going left, not right
    vec4 up = vec4(r.y, -r.x, 0., 0.);
    vec4 vertAtOrigin = vec4(newVert.x, newVert.y, origin.z, 1.);
    vec4 rOrigin = vertAtOrigin - origin;
    float upDist = dot(rOrigin, up);
    pointOfRotation += up*upDist;
    newVert = rotatePoint(vertAtOrigin, pointOfRotation, zDist, rCenter);
    
    // The normal can now be calculated easily //
    normal = normalize(newCenter - newVert);

    // Position the pause menu seperately. All
    // vertices in the pause menu have params[0] < 0
    // Above computations are still done because the
    // resulting normal gives a nice coloration effect
    if (params[0] < 0.) {
        // Text has params[1] < 0, background > 0
        newVert = gl_Vertex;
        if (params[1] < 0.) {
            newVert += vec4(0., sin(frame/50.)*1.8, 0., 0.);
        }
    }
    
    // Blue-ify the coloration for inputShifts[4] close to 1 //
    // This multiplier creates an interesting spiral effect
    float multiplier = sin(sqrt(newVert.x*newVert.x + newVert.y*newVert.y) + 3.*newVert.z) + 1.;
    // This clamp allows the effect to depend on inputShifts[4]
    multiplier = clamp(multiplier, 1. - inputShifts[4],  1. + inputShifts[4]);
    normal.g *= multiplier;
    // This multiplier modulates the red values based on random input
    multiplier = (gl_Normal[1] / 150.) + 1.; // range [1, 1.67]
    multiplier = min(multiplier, 1. + inputShifts[4]/1.5);
    normal.r *= multiplier;
    normal.b += inputShifts[4]*(sin(frame/80.) + 4.)/4.;
    
    // Finish up //
    position = newVert;
    gl_Position = gl_ModelViewProjectionMatrix * newVert;
}
