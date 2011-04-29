#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeFreeTypeFont.h"
#include <freetype/ftglyph.h>

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	FT_Library toeGetFreeTypeLibrary();

}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeFreeTypeFont);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeFreeTypeFont);

//Constructor
CtoeFreeTypeFont::CtoeFreeTypeFont()
{
	face = 0;
	isFaceLoaded = false;
}
//Constructor
CtoeFreeTypeFont::CtoeFreeTypeFont(const CIwStringL& p)
{
	face = 0;
	pathname = p;
	isFaceLoaded = false;
}
//Desctructor
CtoeFreeTypeFont::~CtoeFreeTypeFont()
{
	if (isFaceLoaded)
	{
		FT_Done_Face(face);
	}
	for (CIwArray<CtoeFreeTypeAtlas>::iterator i=atlases.begin(); i!=atlases.end(); ++i)
	{
		delete i->image;
		delete i->texture;
	}
}
bool CtoeFreeTypeAtlas::TryToAllocateRect(int16 x,int16 y,int16 w,int16 h)
{
	for (int16 yy=y; yy<y+h; ++yy)
		for (int16 xx=x; xx<x+w; ++xx)
			if (GetMask(xx,yy))
				return false;
	for (int16 yy=y; yy<y+h; ++yy)
		for (int16 xx=x; xx<x+w; ++xx)
			SetMask(xx,yy);
	return true;
}
CtoeFreeTypeAtlas* CtoeFreeTypeFont::FindSpaceOnTextureAtlas(int16 w, int16 h, int16*x,int16*y)
{
	CtoeFreeTypeAtlas*res;

	*x = 0;
	*y = 0;
	int16 blockW = (w+TOE_GLYPHSTEP-1)/TOE_GLYPHSTEP;
	int16 blockH = (h+TOE_GLYPHSTEP-1)/TOE_GLYPHSTEP;
	for (uint32 i=0; i<atlases.size(); ++i)
	{
		res = &atlases[i];
		for (int16 xx=0; xx<=TOE_GLYPHATLASSIZE/TOE_GLYPHSTEP-blockW; ++xx)
			for (int16 yy=0; yy<=TOE_GLYPHATLASSIZE/TOE_GLYPHSTEP-blockH; ++yy)
			{
				if (res->TryToAllocateRect(xx,yy,blockW,blockH))
				{
					*x = xx*TOE_GLYPHSTEP;
					*y = yy*TOE_GLYPHSTEP;
					return res;
				}
			}
	}

	atlases.push_back();
	res = &atlases.back();
	res->texture = new CIwTexture();
	res->texture->SetModifiable(true);
	res->image = new CIwImage();
	res->image->SetFormat(CIwImage::A_8);
	res->image->SetWidth(TOE_GLYPHATLASSIZE);
	res->image->SetHeight(TOE_GLYPHATLASSIZE);
	res->image->SetBuffers(0,0,0,0);
	uint8*texels = res->image->GetTexels();
	memset(texels,0,TOE_GLYPHATLASSIZE*TOE_GLYPHATLASSIZE);
	memset(res->mask,0,sizeof(res->mask));
	res->texture->SetImage(res->image);
	res->TryToAllocateRect(0,0,blockW,blockH);
	return res;
}
CtoeFreeTypeGlyph* CtoeFreeTypeFont::GetGlyph(int32 charCode, int32 size)
{
	if (charCode < 0)
		return 0;

	CtoeFreeTypeGlyphSet* set = 0;
	for (CIwArray<CtoeFreeTypeGlyphSet>::iterator iterator = glyphSets.begin(); iterator!=glyphSets.end(); ++iterator)
		if (iterator->pixelSize == size)
			set = &(*iterator);
	if (!set)
	{
		glyphSets.push_back(CtoeFreeTypeGlyphSet());
		set = &glyphSets.back();
		set->pixelSize = size;
		set->glyphs.resize(face->num_glyphs+1);
	}
	int32 glyphIndex = FT_Get_Char_Index( face, (uint32)charCode );
	if (set->glyphs.size() <= (uint32)glyphIndex)
		return 0;

	CtoeFreeTypeGlyph* glyph = &set->glyphs[glyphIndex];
	if (!glyph->isLoaded)
	{
		FT_Set_Char_Size(face, size<<6, size<<6, 96, 96);
		glyph->isLoaded = true;
		if(FT_Load_Glyph( face, glyphIndex, FT_LOAD_DEFAULT ))
		{
			IwAssertMsg(TOE,false,("Can not load glyph"));
			return glyph;
		}
		FT_Glyph ft_glyph;
		if(FT_Get_Glyph( face->glyph, &ft_glyph ))
		{
			IwAssertMsg(TOE,false,("Can not get glyph"));
			return glyph;
		}
		
		FT_Glyph_To_Bitmap( &ft_glyph, ft_render_mode_normal, 0, 1 );
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)ft_glyph;
		FT_Bitmap& bitmap=bitmap_glyph->bitmap;
		glyph->width = (int16)bitmap.width;
		glyph->height = (int16)bitmap.rows;
		glyph->advance.x = (int16)(ft_glyph->advance.x>>16);
		glyph->advance.y = (int16)(ft_glyph->advance.y>>16);
		glyph->offset.x = (int16)(bitmap_glyph->left);
	
		glyph->offset.y = (int16)(size -bitmap_glyph->top);
		CtoeFreeTypeAtlas* a = FindSpaceOnTextureAtlas(glyph->width+2,glyph->height+2,&glyph->x,&glyph->y);
		if (a)
		{
			
			glyph->texture = a->texture;
			if (a->texture)
			{
				CIwImage &image = glyph->texture->GetImage();
				uint8*texels =image.GetTexels();
				for (int yy=0; yy<bitmap.rows;++yy)
					for (int xx=0; xx<bitmap.width;++xx)
						*(texels+TOE_GLYPHATLASSIZE*(yy+glyph->y)+(xx+glyph->x)) = bitmap.buffer[xx+yy*bitmap.width];
				glyph->texture->ChangeTexels(texels, CIwImage::A_8);
				glyph->texture->Upload();
			}
			if (IsRightToLeft(charCode))
			{
				//glyph->x += glyph->width-1;
				//glyph->width = -glyph->width;
				glyph->advance.x = -glyph->advance.x;
			}
		}

		
		FT_Done_Glyph(ft_glyph);
	}
	
	return glyph;
}
bool CtoeFreeTypeFont::IsRightToLeft(int32 charCode)
{
		return (charCode >= 0x0590) && (charCode <= 0x07FA);
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeFreeTypeFont::Serialise ()
{
	CIwResource::Serialise();
	pathname.Serialise();

	if (IwSerialiseIsReading())
		LoadFace();
}
void CtoeFreeTypeFont::LoadFace()
{
	if (isFaceLoaded)
		return;
	isFaceLoaded = true;
	if (pathname.length() == 0)
		return;
	FT_Error error = FT_New_Face( toeGetFreeTypeLibrary() ,
		pathname.c_str(),
        0,
        &face );
	IwAssertMsg(FT, !error, ("Could not load face") );
}
#ifdef IW_BUILD_RESOURCES


IW_MANAGED_IMPLEMENT(CtoeFreeTypeFontResHandler)

//Constructor
CtoeFreeTypeFontResHandler::CtoeFreeTypeFontResHandler(const char * ext, const char* name): CIwResHandler(ext, "CtoeFreeTypeFont")
{
	SetName(name);
}
//Desctructor
CtoeFreeTypeFontResHandler::~CtoeFreeTypeFontResHandler()
{
}

//Buid resource method
CIwResource*	CtoeFreeTypeFontResHandler::Build(const CIwStringL& pathname)
{
	//IwGetTextParserITX()->ParseFile(pathname.c_str());
	CtoeFreeTypeFont* res = new CtoeFreeTypeFont(pathname);
	return res;
}

#endif