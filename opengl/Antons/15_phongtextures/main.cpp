/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries separate legal notices                              |
|******************************************************************************|
| Using Textures for Lighting Coefficients                                     |
\******************************************************************************/
#include "maths_funcs.h"
#include "stb_image.h"
#include "gl_utils.h"
#include <assimp/cimport.h> // C importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define GL_LOG_FILE "gl.log"

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 640;
int g_gl_height = 480;
GLFWwindow* g_window = NULL;

GLfloat* g_vp = NULL; // array of vertex points
GLfloat* g_vn = NULL; // array of vertex normals
GLfloat* g_vt = NULL; // array of texture coordinates
int g_point_count = 0;

bool load_texture (const char* file_name, GLuint* tex) {
	int x, y, n;
	int force_channels = 4;
	unsigned char* image_data = stbi_load (file_name, &x, &y, &n, force_channels);
	if (!image_data) {
		fprintf (stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}
	// NPOT check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf (
			stderr, "WARNING: texture %s is not power-of-2 dimensions\n", file_name
		);
	}
	int width_in_bytes = x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = y / 2;

	for (int row = 0; row < half_height; row++) {
		top = image_data + row * width_in_bytes;
		bottom = image_data + (y - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}
	glGenTextures (1, tex);
	glBindTexture (GL_TEXTURE_2D, *tex);
	glTexImage2D (
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		x,
		y,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image_data
	);
	glGenerateMipmap (GL_TEXTURE_2D);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	GLfloat max_aniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
	// set the maximum!
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);
	return true;
}

bool load_mesh (const char* file_name) {
	const aiScene* scene = aiImportFile (file_name, aiProcess_Triangulate);
	if (!scene) {
		fprintf (stderr, "ERROR: reading mesh %s\n", file_name);
		return false;
	}
	printf ("  %i animations\n", scene->mNumAnimations);
	printf ("  %i cameras\n", scene->mNumCameras);
	printf ("  %i lights\n", scene->mNumLights);
	printf ("  %i materials\n", scene->mNumMaterials);
	printf ("  %i meshes\n", scene->mNumMeshes);
	printf ("  %i textures\n", scene->mNumTextures);
	
	// get first mesh only
	const aiMesh* mesh = scene->mMeshes[0];
	printf ("    %i vertices in mesh[0]\n", mesh->mNumVertices);
	g_point_count = mesh->mNumVertices;
	
	// allocate memory for vertex points
	if (mesh->HasPositions ()) {
		printf ("mesh has positions\n");
		g_vp = (GLfloat*)malloc (g_point_count * 3 * sizeof (GLfloat));
	}
	if (mesh->HasNormals ()) {
		printf ("mesh has normals\n");
		g_vn = (GLfloat*)malloc (g_point_count * 3 * sizeof (GLfloat));
	}
	if (mesh->HasTextureCoords (0)) {
		printf ("mesh has texture coords\n");
		g_vt = (GLfloat*)malloc (g_point_count * 2 * sizeof (GLfloat));
	}
	if (mesh->HasTangentsAndBitangents ()) {
		// NB: could allocate tangents here too
	}
	
	for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {
		if (mesh->HasPositions ()) {
			const aiVector3D* vp = &(mesh->mVertices[v_i]);
			g_vp[v_i * 3] = (GLfloat)vp->x;
			g_vp[v_i * 3 + 1] = (GLfloat)vp->y;
			g_vp[v_i * 3 + 2] = (GLfloat)vp->z;
		}
		if (mesh->HasNormals ()) {
			const aiVector3D* vn = &(mesh->mNormals[v_i]);
			g_vn[v_i * 3] = (GLfloat)vn->x;
			g_vn[v_i * 3 + 1] = (GLfloat)vn->y;
			g_vn[v_i * 3 + 2] = (GLfloat)vn->z;
		}
		if (mesh->HasTextureCoords (0)) {
			const aiVector3D* vt = &(mesh->mTextureCoords[0][v_i]);
			g_vt[v_i * 2] = (GLfloat)vt->x;
			g_vt[v_i * 2 + 1] = (GLfloat)vt->y;
		}
		if (mesh->HasTangentsAndBitangents ()) {
			// NB: could store/print tangents here
		}
	}
	
	aiReleaseImport (scene);
	
	printf ("mesh loaded\n");
	
	return true;
}

int main () {
	assert (restart_gl_log ());
	assert (start_gl ());
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

	assert (load_mesh ("untitled.obj"));

	GLuint vao;
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);

	GLuint points_vbo;
	if (NULL != g_vp) {
		glGenBuffers (1, &points_vbo);
		glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
		glBufferData (
			GL_ARRAY_BUFFER, 3 * g_point_count * sizeof (GLfloat), g_vp, GL_STATIC_DRAW
		);
		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray (0);
		printf ("enabled points\n");
	}
	
	GLuint normals_vbo;
	if (NULL != g_vn) {
		glGenBuffers (1, &normals_vbo);
		glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
		glBufferData (
			GL_ARRAY_BUFFER, 3 * g_point_count * sizeof (GLfloat), g_vn, GL_STATIC_DRAW
		);
		glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray (1);
		printf ("enabled normals\n");
	}
	
	GLuint texcoords_vbo;
	if (NULL != g_vt) {
		glGenBuffers (1, &texcoords_vbo);
		glBindBuffer (GL_ARRAY_BUFFER, texcoords_vbo);
		glBufferData (
			GL_ARRAY_BUFFER, 2 * g_point_count * sizeof (GLfloat), g_vt, GL_STATIC_DRAW
		);
		glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray (2);
		printf ("enabled texcoords\n");
	}
	
	GLuint shader_programme = create_programme_from_files (
		"test_vs.glsl", "test_fs.glsl");
	
	// load texture
	GLuint tex_diff, tex_spec, tex_amb, tex_emiss;
	glActiveTexture (GL_TEXTURE0);
	assert (load_texture ("boulder_diff.png", &tex_diff));
	glActiveTexture (GL_TEXTURE1);
	assert (load_texture ("boulder_spec.png", &tex_spec));
	glActiveTexture (GL_TEXTURE2);
	assert (load_texture ("ao.png", &tex_amb));
	glActiveTexture (GL_TEXTURE3);
	assert (load_texture ("tileable9b_emiss.png", &tex_emiss));
	
	#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444
	// input variables
	float near = 0.1f; // clipping plane
	float far = 100.0f; // clipping plane
	float fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
	float aspect = (float)g_gl_width / (float)g_gl_height; // aspect ratio
	// matrix components
	float range = tan (fov * 0.5f) * near;
	float Sx = (2.0f * near) / (range * aspect + range * aspect);
	float Sy = near / range;
	float Sz = -(far + near) / (far - near);
	float Pz = -(2.0f * far * near) / (far - near);
	GLfloat proj_mat[] = {
		Sx, 0.0f, 0.0f, 0.0f,
		0.0f, Sy, 0.0f, 0.0f,
		0.0f, 0.0f, Sz, -1.0f,
		0.0f, 0.0f, Pz, 0.0f
	};
	
		
	float cam_speed = 1.0f; // 1 unit per second
	float cam_yaw_speed = 90.0f; // 10 degrees per second
	float cam_pos[] = {0.0f, 0.0f, 5.0f}; // don't start at zero, or we will be too close
	float cam_yaw = 0.0f; // y-rotation in degrees
	mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));
	mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw);
	mat4 view_mat = R * T;
	
	int view_mat_location = glGetUniformLocation (shader_programme, "view");
	glUseProgram (shader_programme);
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
	int proj_mat_location = glGetUniformLocation (shader_programme, "proj");
	glUseProgram (shader_programme);
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat);
	
	glEnable (GL_CULL_FACE); // cull face
	glCullFace (GL_BACK); // cull back face
	glFrontFace (GL_CCW); // GL_CCW for counter clock-wise
	
	while (!glfwWindowShouldClose (g_window)) {
		static double previous_seconds = glfwGetTime ();
		double current_seconds = glfwGetTime ();
		double elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;
	
		_update_fps_counter (g_window);
		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);
		
		glUseProgram (shader_programme);
		glBindVertexArray (vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays (GL_TRIANGLES, 0, g_point_count);
		// update other events like input handling 
		glfwPollEvents ();
		
		// control keys
		bool cam_moved = false;
		if (glfwGetKey (g_window, GLFW_KEY_A)) {
			cam_pos[0] -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_D)) {
			cam_pos[0] += cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_PAGE_UP)) {
			cam_pos[1] += cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_PAGE_DOWN)) {
			cam_pos[1] -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_W)) {
			cam_pos[2] -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_S)) {
			cam_pos[2] += cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_LEFT)) {
			cam_yaw += cam_yaw_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_RIGHT)) {
			cam_yaw -= cam_yaw_speed * elapsed_seconds;
			cam_moved = true;
		}
		// update view matrix
		if (cam_moved) {
			mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2])); // cam translation
			mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw); // 
			mat4 view_mat = R * T;
			glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
		}
		
		
		if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (g_window, 1);
		}
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (g_window);
	}
	
	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}
