#version 330 core
			
out vec4 color;

in vec3 v_Position;
in vec3 v_Normal;
in vec4 v_Color;
in vec2 v_uv;

uniform vec3 cameraPoz;
uniform sampler2D myTextureSampler;
uniform bool isTextured;

vec3 lighting(vec3 pos, vec3 normal, vec3 lightPos, vec3 viewPos, vec3 ambient, vec3 diffuse, vec3 specular, float specPower);

void main()
{
    vec3 ambient = vec3(0.9);
    vec3 diffuse = vec3(2, 2, 2);
    vec3 specular = vec3(0.8);
    float specPower = 32;

    vec3 lightPos = vec3(2, 3, 6);
    
    vec3 lightColor = lighting(v_Position, v_Normal, lightPos, cameraPoz, ambient, diffuse, specular, specPower);
    
    if (!isTextured){
        color =v_Color * vec4(lightColor, 1.0);
    }
    else{
        color = texture( myTextureSampler, v_uv ).rgba ;
    }
}

vec3 lighting(vec3 pos, vec3 normal, vec3 lightPos, vec3 viewPos, vec3 ambient, vec3 diffuse, vec3 specular, float specPower)
{
    //Difuse lighting
    vec3 L = normalize(lightPos - pos );
    vec3 N = normalize(normal);
    float difusePower = 0;

    if( dot( L, N) > 0){
        difusePower = dot( L, N);
    }

    //Specular lighing
    vec3 V = normalize(viewPos - pos);
    vec3 R = reflect(-L, N);

    float spec = 0;
    float cosThetaSpec = dot( R, V);

    if( cosThetaSpec > 0){
        spec = pow(cosThetaSpec, specPower);
    } 

//	vec3 final = ambient + diffuse * difusePower + spec * specPower ;
    vec3 final = ambient + diffuse * difusePower + spec * specPower;

    return final;
}
