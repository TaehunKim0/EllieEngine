#include"Precompiled.hpp"
#include"EShader.hpp"

EShader::EShader()
{
}

EShader::EShader(std::wstring filename)
	: filename(filename), entry("main")
{
}

EShader::EShader(std::wstring filename, std::string entry, std::string profile)
	: filename(filename), entry(entry), profile(profile)
{
}

EShader::~EShader()
{
}