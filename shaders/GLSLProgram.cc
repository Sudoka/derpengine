#include <glm/gtc/type_ptr.hpp>

#include "GLSLProgram.h"

const char* GLSLProgram::vertex_shader_source = 
	"#version 130\n\n"

	"uniform mat4 MVP;\n"
	"in vec3 v;\n"

	"void main() {\n"
	"	gl_Position = MVP * vec4(v, 1.0);\n"
	"	gl_TexCoord[0] = gl_MultiTexCoord0;\n"
	"}";

const char* GLSLProgram::fragment_shader_source =
	"#version 130\n\n"

	"uniform sampler2D tex_sampler;\n"

	"void main() {\n"
	//"	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
	"	gl_FragColor = texture2D( tex_sampler, gl_TexCoord[0].st );\n"
	"}";

GLSLProgram::GLSLProgram()
{
	char log_buff[1024];
	GLuint vertex_shader_id = compileShader(GL_VERTEX_SHADER, vertex_shader_source);
	GLuint fragment_shader_id = compileShader(GL_FRAGMENT_SHADER, fragment_shader_source);

	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);
	glGetShaderInfoLog(vertex_shader_id, 1023, NULL, log_buff);
	puts(log_buff);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}

GLuint GLSLProgram::compileShader(GLenum type, const char* src)
{
	int log_len = 0;
	GLint compile_success = GL_TRUE;
	char *log_buff = NULL;

	GLuint shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &src, NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_success);

	if (compile_success == GL_TRUE)
		return shader_id;

	// If compilation failed, print the error log
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);
	log_buff = (char*)malloc(log_len);
	glGetShaderInfoLog(shader_id, log_len, NULL, log_buff);
	puts(log_buff);
	free(log_buff);
	return 0;
}

GLSLProgram::~GLSLProgram()
{
	glDeleteProgram(program_id);
}

void GLSLProgram::use()
{
	glUseProgram(program_id);
}

void GLSLProgram::setUniformMVP(glm::mat4 &mvp)
{
	glUniformMatrix4fv(
			glGetUniformLocation(program_id, "MVP"), 
			1, GL_FALSE, glm::value_ptr(mvp));
}

void GLSLProgram::setUniformTexSampler(GLuint i)
{
	glUniform1i(glGetUniformLocation(program_id, "tex_sampler"), i);
}

