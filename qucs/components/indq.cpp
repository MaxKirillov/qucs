/*
* indq.cpp - Lossy capacitor implementation
*
* copyright (C) 2015 Andres Martinez-Mera <andresmartinezmera@gmail.com>
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
#include "indq.h"


indq::indq()
{
  Description = QObject::tr("Lossy inductor");

  //Spiral
  Arcs.push_back(qucs::Arc(-18, -6, 12, 12,  0, 16*180,QPen(Qt::darkBlue,2)));
  Arcs.push_back(qucs::Arc( -6, -6, 12, 12,  0, 16*180,QPen(Qt::darkBlue,2)));
  Arcs.push_back(qucs::Arc(  6, -6, 12, 12,  0, 16*180,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line(-30,  0,-18,  0,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 18,  0, 30,  0,QPen(Qt::darkBlue,2)));



  //Draw Q character
  //Horizontal lines
  Lines.push_back(qucs::Line( 10,  -10, 17,  -10,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 10,  -17, 17,  -17,QPen(Qt::darkBlue,2)));
  //Vertical lines
  Lines.push_back(qucs::Line( 17,  -10, 17,  -17,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 10,  -10, 10,  -17,QPen(Qt::darkBlue,2)));
  //Middle line
  Lines.push_back(qucs::Line( 18,  -9, 14,  -13,QPen(Qt::darkBlue,2)));



  Ports.push_back(qucs::Port(-30,  0));
  Ports.push_back(qucs::Port( 30,  0));

  x1 = -30; y1 = -13;
  x2 =  30; y2 =  13;

  tx = x1+4;
  ty = y2+4;
  Model = "INDQ";
  Name  = "INDQ";

  Props.push_back(qucs::Property("L", "1 nH", true,
		QObject::tr("Inductance")));
  Props.push_back(qucs::Property("Q", "100", true,
		QObject::tr("Quality factor")));
  Props.push_back(qucs::Property("f", "100 MHz", false,
		QObject::tr("Frequency at which Q is measured")));
  Props.push_back(qucs::Property("Mode", "Linear", false,
		QObject::tr("Q frequency profile")+
		" [Linear, SquareRoot, Constant]"));
   Props.push_back(qucs::Property("Temp", "26.85", false,
		QObject::tr("simulation temperature in degree Celsius")));
}
indq::~indq()
{
}

Component* indq::newOne()
{
  return new indq();
}

Element* indq::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("Inductor with Q");
  BitmapFile = (char *) "indq";

  if(getNewOne)  return new indq();
  return 0;
}
