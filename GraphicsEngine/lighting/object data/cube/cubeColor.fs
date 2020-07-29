#version 330 core
out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular; 
    //
    float constant;
    float linear;
    float quadratic;
};

struct Spotlight {
    vec3 direction;
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular; 
    
    float constant;
    float linear;
    float quadratic;

    //cone properties
    float cutOff;
    float outerCutOff;
};

//lights
uniform DirectionalLight dirLight; 
uniform PointLight pointLights[4];
uniform Spotlight flashlight;

//materials
uniform Material material;

uniform vec3 viewPos;
uniform float time;

vec3 calculateDirectionalLight(DirectionalLight dirLight, vec3 viewDir, vec3 normal){
    //ambient light calculation
    float ambientStrength = 0.1;
    vec3 ambient = dirLight.ambient * vec3(texture(material.diffuse, texCoords)).rgb;

     //diffused light calculation
    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = dirLight.diffuse * diff * vec3(texture(material.diffuse, texCoords)).rgb;

    //specular light calculation
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = dirLight.specular * dirLight.diffuse * spec * (vec3(texture(material.specular, texCoords))).rgb;

    return ambient + diffuse + specular;
};

vec3 calculatePointLight(PointLight pointLight, vec3 fragPos, vec3 viewDir, vec3 normal){
    //ambient light calculation
    vec3 ambient = pointLight.ambient * vec3(texture(material.diffuse, texCoords)).rgb;

    //diffused light calculation
    vec3 lightDir = normalize(pointLight.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = pointLight.diffuse * diff * vec3(texture(material.diffuse, texCoords)).rgb;

    //specular light calculation
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = pointLight.specular * pointLight.diffuse * spec * (vec3(texture(material.specular, texCoords))).rgb;

     //calculating attenuation
    float distance = length(pointLight.position - fragPos);
    float attenuation = 1.0/(pointLight.constant + (pointLight.linear * distance) + (pointLight.quadratic * (distance * distance)));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
};

vec3 calculateSpotLight(Spotlight spotlight, vec3 fragPos, vec3 viewDir, vec3 normal){
   //ambient light calculation
   vec3 ambient = spotlight.ambient * vec3(texture(material.diffuse, texCoords)).rgb;

   //diffused light calculation
   vec3 lightDir = normalize(spotlight.position - fragPos);
   float diff = max(dot(normal, lightDir), 0.0);
   vec3 diffuse = spotlight.diffuse * diff * vec3(texture(material.diffuse, texCoords)).rgb;

   //specular light calculation
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = spotlight.specular * spotlight.diffuse * spec * (vec3(texture(material.specular, texCoords))).rgb;

   //spotlight calculation (soft edges)
   float theta = dot(lightDir, normalize(-spotlight.direction));
   float epsilon = spotlight.cutOff - spotlight.outerCutOff;
   float intensity = clamp((theta - spotlight.outerCutOff) / epsilon, 0.0, 1.0);
   diffuse *= intensity;
   specular *= intensity;

   //calculating attenuation
   float distance = length(spotlight.position - fragPos);
   float attenuation = 1.0/(spotlight.constant + (spotlight.linear * distance) + (spotlight.quadratic * (distance * distance)));
   ambient *= attenuation;
   diffuse *= attenuation;
   specular *= attenuation;

   return ambient + diffuse + specular;
};

void main() {
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    //phase 1: calculate directional light
    vec3 result = calculateDirectionalLight(dirLight, viewDir, norm);
    //phase 2: calculate point lights
    for (int i = 0; i < 4; i++){
        result += calculatePointLight(pointLights[i], fragPos, viewDir, norm);
	}
    //phase 3: calculate spotlight
    result += calculateSpotLight(flashlight, fragPos, viewDir, norm);

    FragColor = vec4(result, 1.0f);
}
