#if !defined (BITMAP_H)
#define BITMAP_H
//-------------------------------------
// Copyright Reliable Software (c) 1999
//-------------------------------------
#include "WinEx.h"
#include <windows.h>
class Canvas;

class Bitmap
{
public:
    Bitmap ()
        : _hBitmap (0)
    {}
    Bitmap (Canvas & canvas, int dx, int dy)
        : _hBitmap (0)
    {
        CreateCompatible (canvas, dx, dy);
    }
    // Transfer semantics
    Bitmap (Bitmap & bmp)
        : _hBitmap (bmp.Release ())
    {}
    void operator = (Bitmap & bmp)
    {
        Free ();
        _hBitmap = bmp.Release ();
    }
    HBITMAP Release ()
    {
        HBITMAP h = _hBitmap;
        _hBitmap = 0;
        return h;
    }
    ~Bitmap ()
    {
        Free ();
    }
    // implicit conversion for use with Windows API
    operator HBITMAP () { return _hBitmap; }
    void CreateCompatible (Canvas & canvas, int width, int height);
    // Load from resources
    void Load (HINSTANCE hInst, char const * resName)
    {
        Free ();
        _hBitmap = (HBITMAP) ::LoadImage (hInst, 
            resName,
            IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        if (_hBitmap == 0)
            throw WinException ("Cannot load bitmap from resources", resName);
    }
    void Load (HINSTANCE hInst, int id)
    {
        Free ();
        _hBitmap = (HBITMAP) ::LoadImage (hInst, 
            MAKEINTRESOURCE (id),
            IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        if (_hBitmap == 0)
            throw WinException ("Cannot load bitmap from resources");
    }
    // Load from file
    void Load (char * path)
    {
        Free ();
        _hBitmap = (HBITMAP) ::LoadImage (0, path, 
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        if (_hBitmap == 0)
            throw WinException ("Cannot load bitmap from file", path);
    }
    void GetSize (int &width, int &height)
    {
        BITMAP bm;
        ::GetObject (_hBitmap, sizeof (bm), &bm);
        width = bm.bmWidth;
        height = bm.bmHeight;
    }
protected:
    Bitmap (HBITMAP hBitmap)
        : _hBitmap (hBitmap)
    {}
    void Free ()
    {
        if (_hBitmap) 
            ::DeleteObject (_hBitmap);
    }

    HBITMAP _hBitmap;
};

// Used for bit blitting
class Blitter
{
public:
    Blitter (Bitmap & bmp)
        : _bmp (bmp), _mode (SRCCOPY),
          _xDst (0), _yDst (0),
          _xSrc (0), _ySrc (0)
    {
        bmp.GetSize (_widthDst, _heightDst);
		bmp.GetSize (_widthSrc, _heightSrc);
    }
    void SetMode (DWORD mode)
    {
        _mode = mode;
    }
    void SetDest (int x, int y)
    {
        _xDst = x;
        _yDst = y;
    }
    void SetSrc (int x, int y)
    {
        _xSrc = x;
        _ySrc = y;
    }
    void SetSrcArea (int width, int height)
    {
        _widthSrc = width;
        _heightSrc = height;
    }
    void SetDstArea (int width, int height)
    {
        _widthDst = width;
        _heightDst = height;
    }

    // transfer bitmap to canvas
    void BlitTo (Canvas & canvas);

private:
    Bitmap & _bmp;
    int     _xDst, _yDst;
    int     _xSrc, _ySrc;
	int     _widthDst, _heightDst;
    int     _widthSrc, _heightSrc;
    DWORD   _mode;
};

#endif
