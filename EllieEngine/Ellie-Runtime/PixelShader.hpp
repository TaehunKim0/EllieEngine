#pragma once
#include "Dx11.hpp"
#include "EShader.hpp"
#include "ETexture.hpp"

class PixelShader : public EShader
{
public:
	PixelShader();
	PixelShader(std::wstring filename);
	PixelShader(std::wstring filename, std::string entry, std::string profile);
	~PixelShader();

	bool Compile(ID3D11Device* device) override;
	bool Create(ID3D11Device* device) override;
	void Bind(ID3D11DeviceContext* deviceContext) override;

	bool CreateSamplerState(ID3D11Device* device);
	void BindSamplerState(ID3D11DeviceContext* deviceContext);

	bool LoadTexture(ID3D11Device* device, std::wstring filename);
	void BindTextures(ID3D11DeviceContext* deviceContext);

	ID3D11PixelShader* GetPixelShader() { return _PixelShader.Get(); }

private:
	ComPtr<ID3D11PixelShader> _PixelShader;

	// 텍스쳐 관련 변수.
	std::vector<ETexture> _Textures;
	ComPtr<ID3D11SamplerState> _SamplerState;
};