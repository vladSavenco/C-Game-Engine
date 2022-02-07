#pragma once
#include "Event.h"

enum gEvent { spawn, move, rotate, scale, deleteObj };

class GraphicsEvent :
    public Event
{
public:
   int objId;
   bool isPlayer = false;
   bool isEnemy = false;

   std::string eMeshPath;
   std::string eTexPath;
  
   Vector3 ePos;
   Vector3 eRot;
   Vector3 eScale;
  
   gEvent eSpec;
  
   GraphicsEvent();

   //spawn object
   GraphicsEvent(int id, std::string etype, gEvent spec, Vector3 pos, Vector3 rot, Vector3 scale, std::string meshPath, std::string texPath,bool ply,bool enem);

   //delete enemy
   GraphicsEvent(std::string typ, gEvent spec, int id);
};

