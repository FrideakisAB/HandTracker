#pragma once

#include <GL/glew.h>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Shader {
    unsigned int ID;
    unsigned int atts[6];

public:
    Shader()
    {
        ID = glCreateProgram();
        atts[5] = 0;
    }

    void AddShader(GLenum type, const char* source, const std::string& types)
    {
        unsigned int shad = glCreateShader(type);
        glShaderSource(shad, 1, &source, NULL);
        glCompileShader(shad);
        checkCompileErrors(shad, types);
        glAttachShader(ID, shad);
        atts[atts[5]] = shad;
        ++atts[5];
    }

    void Finish()
    {
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        for(unsigned i = 0; i < atts[5]; ++i)
            glDeleteShader(atts[i]);
    }

    void use()
    {
        glUseProgram(ID);
    }

    void setTexture2D(const std::string& name, uint32_t id, uint32_t num = 0) const
    {
        glActiveTexture(GL_TEXTURE0 + num);
        glBindTexture(GL_TEXTURE_2D, id);
        setInt(name, num);
    }

    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }

    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string& name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }

    void setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setTransformFeedbackVaryings(char** names, unsigned int count, GLenum type = GL_INTERLEAVED_ATTRIBS)
    {
        glTransformFeedbackVaryings(ID, count, names, type);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
    }

private:
    static void checkCompileErrors(GLuint shader, const std::string& type)
    {
        GLint success;
        GLchar infoLog[1024];
        if(type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "Shader error: " << type << std::endl << infoLog << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "Shader error: " << type << std::endl << infoLog << std::endl;
            }
        }
    }
};