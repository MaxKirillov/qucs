/*
* spiralinductor.cpp - Planar spiral inductor class implementation
*
* copyright (C) 2016 Andres Martinez-Mera <andresmartinezmera@gmail.com>
*
* This is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2, or (at your option)
* any later version.
*
* This software is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this package; see the file COPYING.  If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
* Boston, MA 02110-1301, USA.
*
*
*/

#include "spiralinductor.h"


spiralinductor::spiralinductor()
{
  Description = QObject::tr("Planar spiral inductor");

  //Spiral
  Arcs.push_back(qucs::Arc(-5, 0, 10, 10, -16*90, 16*180,QPen(Qt::darkBlue,3)));
  Arcs.push_back(qucs::Arc(-10, -10, 20, 20, 16*90, 16*180,QPen(Qt::darkBlue,3)));
  Arcs.push_back(qucs::Arc(-15, -10, 30, 30, -16*90, 16*180,QPen(Qt::darkBlue,3)));
  Arcs.push_back(qucs::Arc(-20, -20, 40, 40, 16*90, 16*180,QPen(Qt::darkBlue,3)));
  Arcs.push_back(qucs::Arc(-20, -20, 40, 40, 0, 16*90,QPen(Qt::darkBlue,3)));

  Lines.push_back(qucs::Line(-30,  0, 0,  0,QPen(Qt::black,4)));
  Lines.push_back(qucs::Line( 20,  0, 30,  0,QPen(Qt::darkBlue,2)));

  Ports.push_back(qucs::Port(-30, 0));
  Ports.push_back(qucs::Port( 30, 0));

  x1 = -30; y1 =-25;
  x2 =  30; y2 = 25;

  tx = x1;
  ty = y1+50;
  Model = "SPIRALIND";
  Name  = "SPIRALIND";

  Props.push_back(qucs::Property("Subst", "Subst1", true,
		QObject::tr("Substrate")));
  Props.push_back(qucs::Property("Geometry", "Circular", true,
		QObject::tr("Spiral type")+
+		"[Circular, Square, Hexagonal, Octogonal]"));
  Props.push_back(qucs::Property("W", "25 um", false,
		QObject::tr("Width of line")));
  Props.push_back(qucs::Property("Di", "200 um", false,
		QObject::tr("Inner diameter")));
  Props.push_back(qucs::Property("S", "25 um", false,
		QObject::tr("Spacing between turns")));
  Props.push_back(qucs::Property("N", "3", false,
		QObject::tr("Number of turns")));
  Props.push_back(qucs::Property("Temp", "26.85", false,
		QObject::tr("simulation temperature in degree Celsius")));

}

spiralinductor::~spiralinductor()
{
}

Component* spiralinductor::newOne()
{
  return new spiralinductor();
}

Element* spiralinductor::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("Spiral inductor");
  BitmapFile = (char *) "spiralinductor";

  if(getNewOne)  return new spiralinductor();
  return 0;
}
