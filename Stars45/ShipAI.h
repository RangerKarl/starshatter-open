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
    FILE:         ShipAI.h
    AUTHOR:       John DiCamillo


    OVERVIEW
    ========
    Common base class and interface for low-level ship AI
*/

#ifndef ShipAI_h
#define ShipAI_h

#include "Types.h"
#include "SteerAI.h"

// +--------------------------------------------------------------------+

class Ship;
class Shot;
class Instruction;
class TacticalAI;
class Farcaster;

// +--------------------------------------------------------------------+

class ShipAI : public SteerAI
{
public:
    ShipAI(SimObject* s);
    virtual ~ShipAI();

    virtual void      ExecFrame(double seconds);
    virtual int       Subframe()                 const { return true; }

    virtual Ship*     GetShip()                  const { return ship;    }

    virtual Ship*     GetWard()                  const;
    virtual void      SetWard(Ship* s);
    virtual Ship*     GetThreat()                const { return threat;  }
    virtual void      SetThreat(Ship* s);
    virtual Ship*     GetSupport()               const { return support; }
    virtual void      SetSupport(Ship* s);
    virtual Ship*     GetRumor()                 const { return rumor;   }
    virtual void      SetRumor(Ship* s);
    virtual Shot*     GetThreatMissile()         const { return threat_missile; }
    virtual void      SetThreatMissile(Shot* s);
    virtual Instruction* GetNavPoint()           const { return navpt; }
    virtual void      SetNavPoint(Instruction* n)      { navpt = n; }
    virtual Point     GetPatrol()                const;
    virtual void      SetPatrol(const Point& p);
    virtual void      ClearPatrol();
    virtual void      ClearRumor();
    virtual void      ClearTactical();

    virtual Farcaster* GetFarcaster() { return farcaster; }

    // convert the goal point from world to local coords:
    virtual void      FindObjective();

    virtual void      Splash(const Ship* targ);
    virtual void      SetTarget(SimObject* targ, System* sub=0);
    virtual void      DropTarget(double drop_time=1.5);
    virtual double    DropTime()                 const { return drop_time; }
    virtual void      SetBracket(bool bracket);
    virtual void      SetIdentify(bool identify);

    virtual void      SetFormationDelta(const Point& point);

    virtual bool         Update(SimObject* obj);
    virtual const char*  GetObserverName() const;

    virtual int       GetAILevel() const   { return ai_level; }

protected:
    // accumulate behaviors:
    virtual void      Navigator();

    // behaviors:
    virtual bool      AvoidTestSingleObject(SimObject*    obj,
    const Point&  bearing,
    double        avoid_dist,
    double&       avoid_time,
    Steer&        steer);

    virtual Steer     AvoidCloseObject(SimObject* obj);
    virtual Steer     AvoidCollision();
    virtual Steer     AvoidTerrain();
    virtual Steer     SeekTarget();
    virtual Steer     EvadeThreat();

    virtual Point     ClosingVelocity();

    // compute the goal point in world coords based on current ai state:
    virtual void      FindObjectiveTarget(SimObject* tgt);
    virtual void      FindObjectiveNavPoint();
    virtual void      FindObjectiveFormation();
    virtual void      FindObjectivePatrol();
    virtual void      FindObjectiveQuantum();
    virtual void      FindObjectiveFarcaster(SimRegion* src, SimRegion* dst);

    // fire on target if appropriate:
    virtual void      AdjustDefenses();
    virtual void      FireControl();
    virtual void      HelmControl();
    virtual void      ThrottleControl();
    virtual void      NavlightControl();

    virtual void      CheckTarget();

    Ship*             ship;
    Ship*             support;
    Ship*             rumor;
    Ship*             threat;
    Shot*             threat_missile;
    Instruction*      navpt;
    Point             obstacle;
    TacticalAI*       tactical;
    Farcaster*        farcaster;
    int               engaged_ship_id;
    int               splash_count;

    Point             formation_delta;
    double            slot_dist;

    double            throttle;
    double            old_throttle;
    double            seconds;
    double            drop_time;
    double            brake;
    DWORD             last_avoid_time;
    DWORD             last_call_time;

    int               element_index;
    int               too_close;
    bool              bracket;
    bool              identify;
    bool              hold;
    bool              takeoff;

    int               patrol;
    Point             patrol_loc;
    int               ai_level;
};

// +--------------------------------------------------------------------+

#endif ShipAI_h

