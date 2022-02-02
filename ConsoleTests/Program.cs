using WolvenKit.Common.DDS;
using System;
using System.Runtime.InteropServices;
using static WolvenKit.Common.DDS.TexconvNative;



var testFile = Path.GetFullPath("Resources/q204_columbarium_1080p.tga");
Directory.CreateDirectory(Path.GetFullPath("texc"));
var bytes = File.ReadAllBytes(testFile);
var ms = new MemoryStream(bytes);

var md = TexconvNative.GetMetadataFromTGAFile(testFile);

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

{

    var buffer = Array.Empty<byte>();
    using (var blob = new ManagedBlob())
    {
        var len = TexconvNative.ConvertToDds(bytes, blob.GetBlob(), TexconvNative.ESaveFileTypes.TGA,
            DXGI_FORMAT.DXGI_FORMAT_UNKNOWN);
        buffer = blob.GetBytes();
        var outFile = Path.GetFullPath(Path.Combine("texc", "q204_columbarium_1080p_2.dds"));
        File.WriteAllBytes(outFile, buffer);
    }

    
}

{
    var blob = new Blob();
    try
    {
        
        var len = TexconvNative.ConvertToDds(bytes, blob, TexconvNative.ESaveFileTypes.TGA,
            DXGI_FORMAT.DXGI_FORMAT_UNKNOWN);
        var buffer = blob.GetBytes();
        var outFile = Path.GetFullPath(Path.Combine("texc", "q204_columbarium_1080p_1.dds"));
        File.WriteAllBytes(outFile, buffer);
    }
    finally
    {
        TexconvNative.FreeBlob(blob);
    }
}

Console.WriteLine("finished");










