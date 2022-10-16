#pragma once

#include <string>
#include <d3d11.h>

class Shader
{
public:
	Shader();
	Shader(std::wstring filename);
	Shader(std::wstring filename, std::string entry, std::string profile);
	virtual ~Shader();

	virtual bool Compile(ID3D11Device* device) = 0;
	virtual bool Create(ID3D11Device* device) = 0;
	virtual void Bind(ID3D11DeviceContext* deviceContext) = 0;

	// Getter
	std::wstring FileName() { return filename; }
	std::string Entry() { return entry; }
	std::string Profile() { return profile; }

	ID3DBlob* ShaderBuffer() { return shaderBuffer; }

protected:
	std::wstring filename;			// ���̴� ���� �̸�.
	std::string entry;				// main �Լ�.
	std::string profile;			// ���̴� ���� ����. (ex: vs_5_0)

	ID3DBlob* shaderBuffer;			// ���̴� �ڵ带 �������� ���� �ڵ尡 ����Ǵ� ����.

};