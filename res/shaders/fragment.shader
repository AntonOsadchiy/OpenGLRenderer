#version 330 core

	in vec2 v_tex_coord;
	in vec3 v_vertex_normal;
	in vec3 v_fragment_pos;
	in mat3 v_normal_model;

	layout (location = 0) out vec4 color;

	struct Material 
	{
		sampler2D texture_diffuse1;
		sampler2D texture_diffuse2;
		sampler2D texture_diffuse3;
		sampler2D texture_diffuse4;
		sampler2D texture_specular1;
		sampler2D texture_specular2;
		sampler2D texture_specular3;
		float shininess;
	};
	struct Light 
	{	
		vec4 pos;
		vec3 direction;
		vec3 color;

		vec3 ambient_comp;
		vec3 diffuse_comp;
		vec3 specular_comp;	

		float spot_angle;
		float spot_outer_angle;
		float attenuation_linear;
		float attenuation_quadratic;	
	};

#define N_LIGHTS 16
	uniform int u_n_lights;
	uniform Light u_lights[N_LIGHTS];

	uniform Material u_material;
	uniform vec3 u_camera_pos;



	float get_spot_coef(in float angle, in float inner_r, in float outer_r)
	{
		if( outer_r > angle )
			return 0.0;
		if( inner_r > angle )
			return ((angle - outer_r) /  ( inner_r - outer_r));
		return 1.0;
	}

	vec3 get_light_comp(Light u_light)
	{
		vec3 diffuse_comp = vec3(texture(u_material.texture_diffuse1, v_tex_coord));
		vec3 ambient_color = diffuse_comp * u_light.ambient_comp * u_light.color;

		vec3 frag_normal = normalize(v_normal_model * v_vertex_normal);
		vec3 light_dir = vec3(0.0);
		vec3 light_point_dir = vec3(0.0);
		if(u_light.pos.w == 1.0)
		{
			light_point_dir = -normalize(u_light.direction);
			light_dir = normalize(vec3(u_light.pos) - v_fragment_pos);
		}
		else
			light_dir = -normalize(u_light.direction);

		float diffuse_impact = max(dot(frag_normal, light_dir), 0);
		vec3 diffuse_color = diffuse_impact * (u_light.color * diffuse_comp * u_light.diffuse_comp);

		
		vec3 specular_comp = vec3(texture(u_material.texture_specular1, v_tex_coord));
		vec3 view_direction = normalize(u_camera_pos - v_fragment_pos);
		vec3 reflect_direction = reflect(light_dir, frag_normal);
		float spec = pow(max( -dot(view_direction, reflect_direction), 0.0 ), u_material.shininess);
		vec3 specular_color = ((specular_comp * u_light.specular_comp) * spec) * u_light.color;
		//vec3 specular_color = ((specular_comp * 0.3) * spec) * u_light.color;
		//vec3 specular_color = vec3(0.0);

		float angle = dot(light_point_dir, light_dir); 
		float spot_fade = 1.0 ;
		float d = 1.0;
		float attenuation = 1.0;
		if(u_light.pos.w == 1.0)
		{
			spot_fade = get_spot_coef(angle, u_light.spot_angle, u_light.spot_outer_angle);
			d = distance(vec3(u_light.pos), v_fragment_pos);
			attenuation = 1.0 / (1.0 + u_light.attenuation_linear*d + u_light.attenuation_quadratic*d*d);
		}
		return ambient_color + ((spot_fade * attenuation) * diffuse_color + specular_color);
	}



	void main()
	{	

		vec3 light_color = vec3(0.0);
		for(int i = 0; i < u_n_lights; i++)
		{
			light_color += get_light_comp(u_lights[i]);
		}
		//color = texture(u_material.texture_specular1, v_tex_coord);
		//color = vec4(light_color, 1.0);
		color = vec4((ambient_color + diffuse_color + specular_color), 1.0) * vec4(1.0, 1.0, 1.0, 1.0);
	}