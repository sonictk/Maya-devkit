//-
// ==========================================================================
// Copyright 1995,2006,2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

///////////////////////////////////////////////////////////////////
// DESCRIPTION: 
//	OpenEXR Image File plugin.
//
///////////////////////////////////////////////////////////////////

#include <maya/MPxImageFile.h>
#include <maya/MImageFileInfo.h>
#include <maya/MImage.h>
#include <maya/MFnPlugin.h>
#include <maya/MStringArray.h>
#include <maya/MIOStream.h>

#if _WIN32   
#pragma warning( disable : 4290 )		// Disable STL warnings.
#pragma warning( disable : 4244 )		// Disable conversion from unsigned int to unsigned short 
#endif

#undef min
#undef max
#include <OpenEXR/ImfRgbaFile.h>
#include <OpenEXR/ImfArray.h>
#include <half.h>
#define INVALID_PIXEL_TYPE Imf::NUM_PIXELTYPES
MString kImagePluginName( "OpenEXR");

class OpenEXRImageFile : public MPxImageFile
{
public:
                    OpenEXRImageFile();
    virtual         ~OpenEXRImageFile();
    static void*	creator();
	virtual MStatus open( MString pathname, MImageFileInfo* info);
	virtual MStatus load( MImage& image, unsigned int idx);

protected:
	int				fWidth;
	int				fHeight;
	int				fChannels;
	int				fLayers;
	Imf::PixelType	fPixelType;
	Imf::RgbaInputFile*	fInputFile;
};

//
// DESCRIPTION:
///////////////////////////////////////////////////////
OpenEXRImageFile::OpenEXRImageFile()
: fInputFile( NULL), fChannels( 0), fLayers( 0), fPixelType( INVALID_PIXEL_TYPE)
{

}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
OpenEXRImageFile::~OpenEXRImageFile()
{
	if( fInputFile)
		delete fInputFile;
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
void * OpenEXRImageFile::creator()
{
    return new OpenEXRImageFile();
}

//
// DESCRIPTION:
///////////////////////////////////////////////////////
MStatus OpenEXRImageFile::open( MString pathname, MImageFileInfo* info)
{
	if( fInputFile) 
		delete fInputFile;

	try
	{
		fInputFile = new Imf::RgbaInputFile( pathname.asChar());
	}
	catch( ... )
	{
	}

	if( !fInputFile)
		return MS::kFailure;

	if( info)
	{
		const Imf::Header& header = fInputFile->header();
		fWidth = header.dataWindow().max.x - header.dataWindow().min.x + 1;
		fHeight = header.dataWindow().max.y - header.dataWindow().min.y + 1;
		info->width( fWidth);
		info->height( fHeight);
		const Imf::RgbaChannels channels = fInputFile->channels();
		//printf( "Found rgbaChannels %d\n", (int)channels);
		fChannels = channels & Imf::WRITE_A ? 4 : 3;

		info->channels( fChannels);
		info->numberOfImages( fLayers);
		info->pixelType( MImage::kFloat);
		//printf( "Successfully opened EXR image with %d channels of type %d\n", fChannels, (int)fPixelType);
	}
	return MS::kSuccess;
}


//
// DESCRIPTION:
///////////////////////////////////////////////////////
MStatus OpenEXRImageFile::load( MImage& image, unsigned int imageNumber)
{
	MStatus rval = MS::kFailure;
	Imf::Array<Imf::Rgba> pixels;
	try
	{
		// Setup a frame buffer to hold the image
		int dw = fWidth;
		int dh = fHeight;
		int dx = fInputFile->dataWindow().min.x;
		int dy = fInputFile->dataWindow().min.y;
		pixels.resizeErase (dw * dh);
		fInputFile->setFrameBuffer (pixels - dx - dy * dw, 1, dw);
		fInputFile->readPixels( fInputFile->dataWindow().min.y, fInputFile->dataWindow().max.y);

		// Configure our Maya image to hold the result
		image.create( fWidth, fHeight, fChannels, MImage::kFloat);

		// Now transfer the channels in
		bool flipVertically = true;
		float* dest = image.floatPixels();
		if( flipVertically)
		{
			Imf::Rgba* src = pixels + (fHeight - 1) * fWidth;
			for( int y = 0; y < fHeight; y++)
			{
				for( int x = 0; x < fWidth; x++)
				{
					*dest++ = src->r;
					*dest++ = src->g;
					*dest++ = src->b;
					if( fChannels == 4)
						*dest++ = src->a;
					*src++;
				}
				src -= fWidth * 2;
			}
		}
		else
		{
//			half* src = pixels;
//			for( int y = 0; y < fHeight; y++)
//				for( int x = 0; x < fWidth; x++)
//					for( int c = 0; c < fChannels; c++)
//						*dest++ = *src++;
		}

		rval = MS::kSuccess;
	}
	catch (...)
	{
		//
		// If some of the pixels in the file cannot be read,
		// print an error message, and return a partial image
		// to the caller.
		//

		cerr << "OpenEXRImageFile::load() failed to load image." << endl;
	}

	return rval;
}


//////////////////////////////////////////////////////////////////
MStatus initializePlugin( MObject obj )
{
    MFnPlugin plugin( obj, PLUGIN_COMPANY, "8.0", "Any" );
	MStringArray extensions;
	extensions.append( "exr");
    CHECK_MSTATUS( plugin.registerImageFile( 
					kImagePluginName,
					OpenEXRImageFile::creator, 
					extensions));
    
    return MS::kSuccess;
}

// DESCRIPTION:
///////////////////////////////////////////////////////
MStatus uninitializePlugin( MObject obj )
{
    MFnPlugin plugin( obj );
    CHECK_MSTATUS( plugin.deregisterImageFile( kImagePluginName ) );

    return MS::kSuccess;
}

