#include <comdef.h>  // Declares _com_error
#include "Texconv.h"
#include "../DirectXTex/DirectXTex/DirectXTex.h"

using namespace DirectXTexSharp;

//---------------------------------------------------------------------------------
// DXGI Format Utilities

//HRESULT __cdecl ComputePitch(
//    _In_ DXGI_FORMAT fmt, _In_ size_t width, _In_ size_t height,
//    _Out_ size_t& rowPitch, _Out_ size_t& slicePitch, _In_ CP_FLAGS flags = CP_FLAGS_NONE) noexcept;
size_t DirectXTexSharp::Format::ComputeRowPitch(DXGI_FORMAT format, const long width, const long height)
{
    size_t row_pitch;
    size_t slice_pitch;
    const auto hr = DirectX::ComputePitch(static_cast<__dxgiformat_h__::DXGI_FORMAT> (format), width, height, row_pitch, slice_pitch);

    ThrowIfFailed(hr, L"ComputeRowPitch failed");

    return row_pitch;
}

size_t DirectXTexSharp::Format::ComputeSlicePitch(DXGI_FORMAT format, const long width, const long height)
{
    size_t row_pitch;
    size_t slice_pitch;
    const auto hr = DirectX::ComputePitch(static_cast<__dxgiformat_h__::DXGI_FORMAT> (format), width, height, row_pitch, slice_pitch);

    ThrowIfFailed(hr, L"ComputeSlicePitch failed");

    return slice_pitch;
}

//size_t __cdecl BitsPerPixel(_In_ DXGI_FORMAT fmt) noexcept;
size_t DirectXTexSharp::Format::BitsPerPixel(DXGI_FORMAT format)
{
    return DirectX::BitsPerPixel(static_cast<__dxgiformat_h__::DXGI_FORMAT> (format));
}



