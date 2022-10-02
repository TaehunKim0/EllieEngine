#pragma once
#include "Dx11.h"

class EShader
{
public:
	EShader();
	EShader(std::wstring filename);
	EShader(std::wstring filename, std::string entry, std::string profile);
	virtual ~EShader();

	virtual bool Compile(ID3D11Device* device) = 0;
	virtual bool Create(ID3D11Device* device) = 0;
	virtual void Bind(ID3D11DeviceContext* deviceContext) = 0;

	std::wstring FileName() { return filename; }
	std::string Entry() { return entry; }
	std::string Profile() { return profile; }

	ID3DBlob* ShaderBuffer() { return shaderBuffer.Get(); }

protected:
	std::wstring filename;			// 쉐이더 파일 이름.
	std::string entry;				// main 함수.
	std::string profile;			// 쉐이더 버전 정보. (ex: vs_5_0)

	ComPtr<ID3DBlob> shaderBuffer;			// 쉐이더 코드를 컴파일한 이진 코드가 저장되는 버퍼.
};