#pragma once

namespace DirectXTexSharp {

    public enum class DDSFLAGS : unsigned long
    {
        DDS_FLAGS_NONE = 0x0,

        DDS_FLAGS_LEGACY_DWORD = 0x1,
        // Assume pitch is DWORD aligned instead of BYTE aligned (used by some legacy DDS files)

        DDS_FLAGS_NO_LEGACY_EXPANSION = 0x2,
        // Do not implicitly convert legacy formats that result in larger pixel sizes (24 bpp, 3:3:2, A8L8, A4L4, P8, A8P8)

        DDS_FLAGS_NO_R10B10G10A2_FIXUP = 0x4,
        // Do not use work-around for long-standing D3DX DDS file format issue which reversed the 10:10:10:2 color order masks

        DDS_FLAGS_FORCE_RGB = 0x8,
        // Convert DXGI 1.1 BGR formats to DXGI_FORMAT_R8G8B8A8_UNORM to avoid use of optional WDDM 1.1 formats

        DDS_FLAGS_NO_16BPP = 0x10,
        // Conversions avoid use of 565, 5551, and 4444 formats and instead expand to 8888 to avoid use of optional WDDM 1.2 formats

        DDS_FLAGS_EXPAND_LUMINANCE = 0x20,
        // When loading legacy luminance formats expand replicating the color channels rather than leaving them packed (L8, L16, A8L8)

        DDS_FLAGS_BAD_DXTN_TAILS = 0x40,
        // Some older DXTn DDS files incorrectly handle mipchain tails for blocks smaller than 4x4

        DDS_FLAGS_FORCE_DX10_EXT = 0x10000,
        // Always use the 'DX10' header extension for DDS writer (i.e. don't try to write DX9 compatible DDS files)

        DDS_FLAGS_FORCE_DX10_EXT_MISC2 = 0x20000,
        // DDS_FLAGS_FORCE_DX10_EXT including miscFlags2 information (result may not be compatible with D3DX10 or D3DX11)

        DDS_FLAGS_FORCE_DX9_LEGACY = 0x40000,
        // Force use of legacy header for DDS writer (will fail if unable to write as such)

        DDS_FLAGS_ALLOW_LARGE_FILES = 0x1000000,
        // Enables the loader to read large dimension .dds files (i.e. greater than known hardware requirements)
    };

    public enum class TEX_DIMENSION
        // Subset here matches D3D10_RESOURCE_DIMENSION and D3D11_RESOURCE_DIMENSION
    {
        TEX_DIMENSION_TEXTURE1D = 2,
        TEX_DIMENSION_TEXTURE2D = 3,
        TEX_DIMENSION_TEXTURE3D = 4,
    };

    public enum class TEX_FILTER_FLAGS : unsigned long
    {
        TEX_FILTER_DEFAULT = 0,

        TEX_FILTER_WRAP_U = 0x1,
        TEX_FILTER_WRAP_V = 0x2,
        TEX_FILTER_WRAP_W = 0x4,
        TEX_FILTER_WRAP = (TEX_FILTER_WRAP_U | TEX_FILTER_WRAP_V | TEX_FILTER_WRAP_W),
        TEX_FILTER_MIRROR_U = 0x10,
        TEX_FILTER_MIRROR_V = 0x20,
        TEX_FILTER_MIRROR_W = 0x40,
        TEX_FILTER_MIRROR = (TEX_FILTER_MIRROR_U | TEX_FILTER_MIRROR_V | TEX_FILTER_MIRROR_W),
        // Wrap vs. Mirror vs. Clamp filtering options

        TEX_FILTER_SEPARATE_ALPHA = 0x100,
        // Resize color and alpha channel independently

        TEX_FILTER_FLOAT_X2BIAS = 0x200,
        // Enable *2 - 1 conversion cases for unorm<->float and positive-only float formats

        TEX_FILTER_RGB_COPY_RED = 0x1000,
        TEX_FILTER_RGB_COPY_GREEN = 0x2000,
        TEX_FILTER_RGB_COPY_BLUE = 0x4000,
        // When converting RGB to R, defaults to using grayscale. These flags indicate copying a specific channel instead
        // When converting RGB to RG, defaults to copying RED | GREEN. These flags control which channels are selected instead.

        TEX_FILTER_DITHER = 0x10000,
        // Use ordered 4x4 dithering for any required conversions
        TEX_FILTER_DITHER_DIFFUSION = 0x20000,
        // Use error-diffusion dithering for any required conversions

        TEX_FILTER_POINT = 0x100000,
        TEX_FILTER_LINEAR = 0x200000,
        TEX_FILTER_CUBIC = 0x300000,
        TEX_FILTER_BOX = 0x400000,
        TEX_FILTER_FANT = 0x400000, // Equiv to Box filtering for mipmap generation
        TEX_FILTER_TRIANGLE = 0x500000,
        // Filtering mode to use for any required image resizing

        TEX_FILTER_SRGB_IN = 0x1000000,
        TEX_FILTER_SRGB_OUT = 0x2000000,
        TEX_FILTER_SRGB = (TEX_FILTER_SRGB_IN | TEX_FILTER_SRGB_OUT),
        // sRGB <-> RGB for use in conversion operations
        // if the input format type is IsSRGB(), then SRGB_IN is on by default
        // if the output format type is IsSRGB(), then SRGB_OUT is on by default

        TEX_FILTER_FORCE_NON_WIC = 0x10000000,
        // Forces use of the non-WIC path when both are an option

        TEX_FILTER_FORCE_WIC = 0x20000000,
        // Forces use of the WIC path even when logic would have picked a non-WIC path when both are an option
    };

}