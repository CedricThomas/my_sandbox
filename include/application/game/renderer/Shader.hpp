//
// Created by arzad on 17/01/2022.
//

#ifndef APP_SHADER_HPP
#define APP_SHADER_HPP

#include "lib/graphics/glad.h"
#include "application/ApplicationException.hpp"

#include "glm/glm.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID;

    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader();
    Shader(const std::string &vertexPath, const std::string &fragmentPath);

    // activate the shader
    // ------------------------------------------------------------------------
    void useProgram() const;

    // delete the program
    // ------------------------------------------------------------------------
    void deleteProgram() const;

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const;

    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const;

    void setInts(const std::string &name, int size, int *values) const;

    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const;

    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const;

    void setVec2(const std::string &name, float x, float y) const;

    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const;

    void setVec3(const std::string &name, float x, float y, float z) const;

    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const;

    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const;

    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const;

    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    static void checkCompileErrors(unsigned int shader, const std::string& type);

};

#endif //APP_SHADER_HPP
