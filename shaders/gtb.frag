#extension GL_EXT_gpu_shader4 : require
const int numShifts = 5;
uniform float inputShifts[numShifts];
uniform vec4 cameraPos;

flat varying vec4 position;
flat varying vec4 normal;
flat varying vec4 colorShift;
varying vec3 params;

void main()
{
    float dist = position.z - cameraPos.z;
    vec4 color = (normal + vec4(1))/2.;
    color += colorShift;
    
    // Color the pause menu if it is open. All
    // vertices in the pause menu have params[0] < 0
    if (params[0] < 0.) {
        // Text has params[1] < 0, background > 0
        if (params[1] < 0.) {
            color += vec4(0., 0., 1., 0.);
        } else {
            color = vec4(0., 0., 0., 1.);
        }
    }
    
    // Dissolve to black
    for (float i = 150.; i <= 300.; i += 5.) {
        if (dist > i) {
            color *= pow(i/dist, i/100.);
        }
    }
    
    // Lineify the coloration
    if (abs(params[0] - round(params[0])) > 0.1 && abs(position.z - round(position.z)) > 0.1) {
        color *= 1.-inputShifts[3];
    }

    color.a = 1.;
    gl_FragColor = color;
}
