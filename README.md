# Texconv
A c++ wrapper library around [DirectXTex and Texconv](https://github.com/microsoft/DirectXTex).

## Build instructions

1. Clone the repository into an empty folder

```cmd
git clone https://github.com/rfuzzo/TexconvLib.git
```

2. Update the submodules
```cmd
git submodule init --recursive
```

3. Build the repository with cmake

- `CMakeLists.txt` or `Source/CMakeLists.txt`

- There is also a `TexconvLib.sln` for c# interop tests. 

## Currently implemented Texconv functions:
- [ ] ConvertAndSaveDdsImage
- [ ] ConvertDdsImageToArray

- [x] Flip/Rotate
- [ ] Resize
- [ ] Swizzle
- [ ] Color rotation
- [ ] Tonemap
- [x] Convert
- [ ] Convert NormalMaps
- [ ] ColorKey/ChromaKey
- [ ] Invert Y Channel
- [ ] Reconstruct Z Channel
- [ ] Determine whether preserve alpha coverage is required
- [ ] Generate mips
- [ ] Preserve mipmap alpha coverage
- [ ] Premultiplied alpha
- [ ] Compress
- [x] Set alpha mode


## Currently implemented DirectXTex functions:
### DXGI Format Utilities
- [ ] ComputePitch
- [ ] ComputeScanlines
- [ ] ComputeScanlines


### Texture metadata
- [x] GetMetadataFromDDSMemory
- [x] GetMetadataFromDDSFile
- [ ] GetMetadataFromHDRMemory
- [ ] GetMetadataFromHDRFile
- [ ] GetMetadataFromTGAMemory
- [ ] GetMetadataFromTGAFile

### Image I/O
#### DDS operations
- [x] LoadFromDDSMemory
- [ ] LoadFromDDSFile
- [ ] SaveToDDSMemory
- [ ] SaveToDDSMemory
- [ ] SaveToDDSFile
- [ ] SaveToDDSFile

#### HDR operations

#### TGA operations
- [ ] LoadFromTGAMemory
- [ ] LoadFromTGAFile
- [ ] SaveToTGAMemory
- [x] SaveToTGAFile

### Texture conversion, resizing, mipmap generation, and block compression
- [ ] Resize
- [ ] Resize
- [x] Convert
- [ ] Convert
- [ ] ConvertToSinglePlane
- [ ] ConvertToSinglePlane
- [ ] GenerateMipMaps
- [ ] GenerateMipMaps
- [ ] GenerateMipMaps3D
- [ ] GenerateMipMaps3D
- [ ] ScaleMipMapsAlphaForCoverage

- [ ] Compress
- [ ] Compress
- [ ] Compress
- [ ] Compress
- [x] Decompress
- [ ] Decompress

### Normal map operations
- [ ] ComputeNormalMap
- [ ] ComputeNormalMap

### Misc image operations

