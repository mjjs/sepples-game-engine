#version 460 core

precision highp float;

in vec4 colour_v;
in vec2 texture_coordinate_v;
in float texture_index_v;

out vec4 frag_color_v;

uniform sampler2D textures_u[32];

void main()
{
    vec4 color = colour_v;

    switch(int(texture_index_v)) {
        case 0: color *= texture(textures_u[0], texture_coordinate_v); break;
        case 1: color *= texture(textures_u[1], texture_coordinate_v); break;
        case 2: color *= texture(textures_u[2], texture_coordinate_v); break;
        case 3: color *= texture(textures_u[3], texture_coordinate_v); break;
        case 4: color *= texture(textures_u[4], texture_coordinate_v); break;
        case 5: color *= texture(textures_u[5], texture_coordinate_v); break;
        case 6: color *= texture(textures_u[6], texture_coordinate_v); break;
        case 7: color *= texture(textures_u[7], texture_coordinate_v); break;
        case 8: color *= texture(textures_u[8], texture_coordinate_v); break;
        case 9: color *= texture(textures_u[9], texture_coordinate_v); break;
        case 10: color *= texture(textures_u[10], texture_coordinate_v); break;
        case 11: color *= texture(textures_u[11], texture_coordinate_v); break;
        case 12: color *= texture(textures_u[12], texture_coordinate_v); break;
        case 13: color *= texture(textures_u[13], texture_coordinate_v); break;
        case 14: color *= texture(textures_u[14], texture_coordinate_v); break;
        case 15: color *= texture(textures_u[15], texture_coordinate_v); break;
        case 16: color *= texture(textures_u[16], texture_coordinate_v); break;
        case 17: color *= texture(textures_u[17], texture_coordinate_v); break;
        case 18: color *= texture(textures_u[18], texture_coordinate_v); break;
        case 19: color *= texture(textures_u[19], texture_coordinate_v); break;
        case 20: color *= texture(textures_u[20], texture_coordinate_v); break;
        case 21: color *= texture(textures_u[21], texture_coordinate_v); break;
        case 22: color *= texture(textures_u[22], texture_coordinate_v); break;
        case 23: color *= texture(textures_u[23], texture_coordinate_v); break;
        case 24: color *= texture(textures_u[24], texture_coordinate_v); break;
        case 25: color *= texture(textures_u[25], texture_coordinate_v); break;
        case 26: color *= texture(textures_u[26], texture_coordinate_v); break;
        case 27: color *= texture(textures_u[27], texture_coordinate_v); break;
        case 28: color *= texture(textures_u[28], texture_coordinate_v); break;
        case 29: color *= texture(textures_u[29], texture_coordinate_v); break;
        case 30: color *= texture(textures_u[30], texture_coordinate_v); break;
        case 31: color *= texture(textures_u[31], texture_coordinate_v); break;
    }

    frag_color_v = color;
}
