/***************************************************************************
                          mscoupled.cpp  -  description
                             -------------------
    begin                : Sat Aug 23 2003
    copyright            : (C) 2010 by Frans Schreuder
    email                : fransschreuder@lists.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "mslange.h"


MSlange::MSlange()
{
  Description = QObject::tr("microstrip lange coupler");

  Lines.push_back(qucs::Line(-30,-30,-30, 10,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line(-30, 30,-30, 20,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line(-30, 20,  0, 20,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line(-30, 10, 30, 10,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line(-25,  0, 25,  0,QPen(Qt::darkBlue,2)));      
  Lines.push_back(qucs::Line(-30,-10, 30,-10,QPen(Qt::darkBlue,2)));    
  Lines.push_back(qucs::Line(  0,-20, 30,-20,QPen(Qt::darkBlue,2)));    
  Lines.push_back(qucs::Line( 30,-30, 30,-20,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 30,-10, 30, 30,QPen(Qt::darkBlue,2)));          

  Ports.push_back(qucs::Port(-30,-30));
  Ports.push_back(qucs::Port( 30, 30));
  Ports.push_back(qucs::Port( 30,-30));
  Ports.push_back(qucs::Port(-30, 30));

  x1 = -30; y1 =-33;
  x2 =  30; y2 = 33;

  tx = x1+4;
  ty = y2+4;
  Model = "MLANGE";
  Name  = "MS";

  Props.push_back(qucs::Property("Subst", "Subst1", true,
	QObject::tr("name of substrate definition")));
  Props.push_back(qucs::Property("W", "1 mm", true,
	QObject::tr("width of the line")));
  Props.push_back(qucs::Property("L", "10 mm", true,
	QObject::tr("length of the line")));
  Props.push_back(qucs::Property("S", "1 mm", true,
	QObject::tr("spacing between the lines")));
  Props.push_back(qucs::Property("Model", "Kirschning", false,
	QObject::tr("microstrip model")+" [Kirschning, Hammerstad]"));
  Props.push_back(qucs::Property("DispModel", "Kirschning", false,
	QObject::tr("microstrip dispersion model")+
	" [Kirschning, Getsinger]"));
  Props.push_back(qucs::Property("Temp", "26.85", false,
	QObject::tr("simulation temperature in degree Celsius")));
}

MSlange::~MSlange()
{
}

Component* MSlange::newOne()
{
  return new MSlange();
}

Element* MSlange::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("Microstrip Lange Coupler");
  BitmapFile = (char *) "mslange";

  if(getNewOne)  return new MSlange();
  return 0;
}
