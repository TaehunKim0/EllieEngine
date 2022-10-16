#include "Shader.hpp"

Shader::Shader()
{
}

Shader::Shader(std::wstring filename)
	: filename(filename), entry("main")
{
}

Shader::Shader(std::wstring filename, std::string entry, std::string profile)
	: filename(filename), entry(entry), profile(profile)
{
}

Shader::~Shader()
{
}