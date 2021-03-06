/*  Starshatter OpenSource Distribution
    Copyright (c) 1997-2004, Destroyer Studios LLC.
    All Rights Reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name "Destroyer Studios" nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.

    SUBSYSTEM:    Stars.exe
    FILE:         MFD.h
    AUTHOR:       John DiCamillo


    OVERVIEW
    ========
    Class for all Multi Function Displays
*/

#ifndef MFD_h
#define MFD_h

#include "Types.h"
#include "Geometry.h"
#include "Color.h"
#include "HUDView.h"

// +--------------------------------------------------------------------+

class Contact;
class Ship;
class Sprite;
class Window;

// +--------------------------------------------------------------------+

class MFD
{
public:
    enum Modes { MFD_MODE_OFF,  MFD_MODE_GAME, MFD_MODE_SHIP, 
        MFD_MODE_FOV,  /*MFD_MODE_FWD,  MFD_MODE_MAP,*/
        MFD_MODE_HSD,  MFD_MODE_3D
    };

    MFD(Window* c, int index);
    virtual ~MFD();

    int operator == (const MFD& that) const { return this == &that; }

    static void          Initialize();
    static void          Close();
    static void          SetColor(Color c);

    // Operations:
    virtual void         Draw();
    virtual void         DrawGameMFD();
    virtual void         DrawStatusMFD();
    virtual void         DrawSensorMFD();
    virtual void         DrawHSD();
    virtual void         Draw3D();
    virtual void         DrawSensorLabels(const char* mfd_mode);
    virtual void         DrawMap();
    virtual void         DrawGauge(int x, int y, int percent);
    virtual void         SetStatusColor(int status);

    virtual void         SetWindow(Window* w)    { window = w; }
    virtual Window*      GetWindow()             { return window; }
    virtual void         SetRect(const Rect& r);
    virtual const Rect&  GetRect() const         { return rect; }
    virtual void         SetMode(int m);
    virtual int          GetMode() const         { return mode; }
    virtual Sprite*      GetSprite()             { return sprite; }

    virtual void         SetShip(Ship* s)        { ship = s;    }
    virtual Ship*        GetShip()               { return ship; }

    virtual void         Show();
    virtual void         Hide();

    virtual void         UseCameraView(CameraView* v);
    void         DrawMFDText(int index, const char* txt, Rect& r, int align, int status=-1);
    void         HideMFDText(int index);
    void         SetText3DColor(Color c);
    void         SetCockpitHUDTexture(Bitmap* bmp) { cockpit_hud_texture = bmp; }

    bool         IsMouseLatched() const;

protected:

    enum { TXT_LAST=20 };

    Window*     window;
    Rect        rect;
    int         index;
    int         mode;
    int         lines;
    Sprite*     sprite;
    bool        hidden;
    Ship*       ship;
    HUDText     mfd_text[TXT_LAST];
    CameraView* camview;
    Bitmap*     cockpit_hud_texture;

    int         mouse_latch;
    bool        mouse_in;
};

#endif MFD_h

