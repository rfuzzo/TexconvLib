#include <comdef.h>  // Declares _com_error
#include "Texconv.h"
#include "../DirectXTex/DirectXTex/DirectXTex.h"

using namespace DirectXTexSharp;

//---------------------------------------------------------------------------------
// Texture metadata

//HRESULT __cdecl GetMetadataFromDDSFile(
//	_In_z_ const wchar_t* szFile,
//	_In_ DDS_FLAGS flags,
//	_Out_ TexMetadata& metadata) noexcept;
DirectX::TexMetadata DirectXTexSharp::Metadata::GetMetadataFromDDSFile(
        const wchar_t* szFile,
	DirectXTexSharp::DDSFLAGS flags) {

	DirectX::TexMetadata metadata;
	const auto hr = DirectX::GetMetadataFromDDSFile(
            szFile,
		static_cast<DirectX::DDS_FLAGS> (flags),
		metadata);

    ThrowIfFailed(hr, L"GetMetadataFromDDSFile");

	return metadata;
}

//HRESULT __cdecl GetMetadataFromDDSMemory(
//	_In_reads_bytes_(size) const void* pSource, _In_ size_t size,
//	_In_ DDS_FLAGS flags,
//	_Out_ TexMetadata& metadata) noexcept;
DirectX::TexMetadata DirectXTexSharp::Metadata::GetMetadataFromDDSMemory(
	byte* pSource,
	const int size,
	DirectXTexSharp::DDSFLAGS flags) {

	DirectX::TexMetadata metadata;
	const auto hr = DirectX::GetMetadataFromDDSMemory(
        pSource,
		size,
		static_cast<DirectX::DDS_FLAGS> (flags),
		metadata);

    ThrowIfFailed(hr, L"GetMetadataFromDDSMemory");

	return metadata;
}

//HRESULT __cdecl GetMetadataFromTGAFile(
//    _In_z_ const wchar_t* szFile,
//    _In_ TGA_FLAGS flags,
//    _Out_ TexMetadata& metadata) noexcept;
DirectX::TexMetadata DirectXTexSharp::Metadata::GetMetadataFromTGAFile(
        const wchar_t* szFile,
	DirectXTexSharp::TGA_FLAGS flags) {

	DirectX::TexMetadata metadata;
	const auto hr = DirectX::GetMetadataFromTGAFile(
            szFile,
		static_cast<DirectX::TGA_FLAGS> (flags),
		metadata);

    ThrowIfFailed(hr, L"GetMetadataFromTGAFile");

	return metadata;
}
