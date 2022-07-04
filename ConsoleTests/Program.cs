using ConsoleTests;
using System.Buffers;
using System.Runtime.InteropServices;
using WolvenKit.Common.DDS;
using static WolvenKit.Common.DDS.TexconvNative;

Directory.CreateDirectory(Path.GetFullPath("texc"));


string testFile = Path.GetFullPath("Resources/q204_columbarium_1080p.tga");
byte[] bytes = File.ReadAllBytes(testFile);


TexMetadata md = GetMetadataFromTGAFile(testFile);

//{
//    using (var blob = new TexconvNative.Blob())
//    {
//        var len = TexconvNative.ConvertToDds(bytes, blob, TexconvNative.ESaveFileTypes.TGA,
//            DXGI_FORMAT.DXGI_FORMAT_UNKNOWN);
//        var buffer = blob.GetBytes();
//        var outFile = Path.GetFullPath(Path.Combine("texc", "q204_columbarium_1080p_1.dds"));
//        File.WriteAllBytes(outFile, buffer);
//    }

//}

/*
{
    using ScopedStopwatch ssw = new("DXGI_FORMAT_UNKNOWN");
    // convert to DDS

    byte[] buffer = Array.Empty<byte>();
    using ManagedBlob blob = new();

    long len = ConvertToDds(bytes, blob.GetBlob(), ESaveFileTypes.TGA, DXGI_FORMAT.DXGI_FORMAT_UNKNOWN);
    buffer = blob.GetBytes();
    string outFile = Path.GetFullPath(Path.Combine("texc", "q204_columbarium_1080p_2.dds"));
    if (File.Exists(outFile))
    {
        File.Delete(outFile);
    }
    Console.WriteLine(outFile);
    File.WriteAllBytes(outFile, buffer);
}

{
    Blob blob = new();
    try
    {
        using ScopedStopwatch ssw = new("DXGI_FORMAT_UNKNOWN");
        long len = ConvertToDds(bytes, blob, ESaveFileTypes.TGA, DXGI_FORMAT.DXGI_FORMAT_UNKNOWN);
        byte[] buffer = blob.GetBytes();
        string outFile = Path.GetFullPath(Path.Combine("texc", "q204_columbarium_1080p_1.dds"));
        if (File.Exists(outFile))
        {
            File.Delete(outFile);
        }
        Console.WriteLine(outFile);
        File.WriteAllBytes(outFile, buffer);
    }
    finally
    {
        FreeBlob(blob);
    }
}
*/

testFile = Path.GetFullPath("Resources/h0_001_wa_c__judy_d02.tga");
bytes = File.ReadAllBytes(testFile);
MemoryStream ms = new(bytes);

/*
{
    using ScopedStopwatch ssw = new("DXGI_FORMAT_BC1_UNORM");
    ms.Seek(0, SeekOrigin.Begin);
    byte[] r1 = ConvertToDdsWkit(ms, EUncookExtension.tga, DXGI_FORMAT.DXGI_FORMAT_BC1_UNORM);
    string outFile1 = Path.GetFullPath(Path.Combine("texc", "q204_columbarium_1080p_bc1.dds"));
    File.WriteAllBytes(outFile1, r1);
}

{
    using ScopedStopwatch ssw = new("DXGI_FORMAT_BC3_UNORM");
    ms.Seek(0, SeekOrigin.Begin);
    byte[] r3 = ConvertToDdsWkit(ms, EUncookExtension.tga, DXGI_FORMAT.DXGI_FORMAT_BC3_UNORM);
    string outFile3 = Path.GetFullPath(Path.Combine("texc", "q204_columbarium_1080p_bc3.dds"));
    File.WriteAllBytes(outFile3, r3);
}
*/

{
    using ScopedStopwatch ssw = new("DXGI_FORMAT_BC7_UNORM");
    ms.Seek(0, SeekOrigin.Begin);
    byte[] r7 = ConvertToDdsWkit(ms, EUncookExtension.tga, DXGI_FORMAT.DXGI_FORMAT_BC7_UNORM);
    string outFile7 = Path.GetFullPath(Path.Combine("texc", "q204_columbarium_1080p_bc7.dds"));
    File.WriteAllBytes(outFile7, r7);
}



Console.WriteLine("finished");




/// <summary>
/// Converts texture stream with given extension stream to dds
/// </summary>
byte[] ConvertToDdsWkit(Stream stream, EUncookExtension inExtension, DXGI_FORMAT? outFormat = null, bool vflip = false, bool hflip = false)
{
    if (inExtension == EUncookExtension.dds)
    {
        throw new NotSupportedException("texture to convert to dds must not be dds iteslf");
    }

    byte[] rentedBuffer = null;
    try
    {
        int offset = 0;

        int len = checked((int)stream.Length);
        rentedBuffer = ArrayPool<byte>.Shared.Rent(len);

        int readBytes;
        while (offset < len &&
               (readBytes = stream.Read(rentedBuffer, offset, len - offset)) > 0)
        {
            offset += readBytes;
        }

        DXGI_FORMAT format = outFormat ?? DXGI_FORMAT.DXGI_FORMAT_UNKNOWN;

        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
        {
            byte[] buffer = Array.Empty<byte>();
            using (ManagedBlob blob = new())
            {
                long l = TexconvNative.ConvertToDds(rentedBuffer, blob.GetBlob(), ToSaveFormat(inExtension), format, vflip, hflip);
                buffer = blob.GetBytes();
            }
            return buffer;
        }
        else
        {
            throw new NotImplementedException();
        }
    }
    finally
    {
        if (rentedBuffer is not null)
        {
            ArrayPool<byte>.Shared.Return(rentedBuffer);
        }
    }
}

ESaveFileTypes ToSaveFormat(EUncookExtension extension)
{
    return extension switch
    {
        EUncookExtension.bmp => ESaveFileTypes.BMP,
        EUncookExtension.jpg => ESaveFileTypes.JPEG,
        EUncookExtension.png => ESaveFileTypes.PNG,
        EUncookExtension.tga => ESaveFileTypes.TGA,
        EUncookExtension.tiff => ESaveFileTypes.TIFF,
        _ => throw new ArgumentOutOfRangeException(nameof(extension), extension, null)
    };
}

/// <summary>
/// Possible extensions to uncook textures
/// </summary>
internal enum EUncookExtension
{
    dds,
    tga,
    bmp,
    jpg,
    png,
    tiff
}

