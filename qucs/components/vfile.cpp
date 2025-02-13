/***************************************************************************
                                vfile.cpp
                               -----------
    begin                : Fri April 07 2007
    updated drawing      : Wed October 03 2007
    copyright            : (C) 2007 by Gunther Kraut
    email                : gn.kraut@t-online.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "vfile.h"
#include "schematic.h"
#include "misc.h"

vFile::vFile()
{
  Description = QObject::tr("file based voltage source");

  Arcs.push_back(qucs::Arc(-12,-12, 24, 24,     0, 16*360,QPen(Qt::darkBlue,2)));
  Arcs.push_back(qucs::Arc( -3, -7,  7,  7,16*270, 16*180,QPen(Qt::darkBlue,2)));
  Arcs.push_back(qucs::Arc( -3,  0,  7,  7, 16*90, 16*180,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line(-30,  0,-12,  0,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 30,  0, 12,  0,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 18,  5, 18, 11,QPen(Qt::red,1)));
  Lines.push_back(qucs::Line( 21,  8, 15,  8,QPen(Qt::red,1)));
  Lines.push_back(qucs::Line(-18,  5,-18, 11,QPen(Qt::black,1)));

  Lines.push_back(qucs::Line( -6,-17, -6,-21,QPen(Qt::darkBlue,1)));
  Lines.push_back(qucs::Line( -8,-17, -8,-21,QPen(Qt::darkBlue,1)));
  Lines.push_back(qucs::Line(-10,-17,-10,-21,QPen(Qt::darkBlue,1)));
  Lines.push_back(qucs::Line( -3,-15, -3,-23,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line(-13,-15,-13,-23,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( -3,-23,-13,-23,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( -3,-15,-13,-15,QPen(Qt::darkBlue,2)));

  Ports.push_back(qucs::Port( 30,  0));
  Ports.push_back(qucs::Port(-30,  0));

  x1 = -30; y1 = -14;
  x2 =  30; y2 =  14;

  tx = x1+4;
  ty = y2+4;
  Model = "Vfile";
  Name  = "V";

  Props.push_back(qucs::Property("File", "vfile.dat", true,
		QObject::tr("name of the sample file")));
  Props.push_back(qucs::Property("Interpolator", "linear", false,
		QObject::tr("interpolation type")+" [hold, linear, cubic]"));
  Props.push_back(qucs::Property("Repeat", "no", false,
		QObject::tr("repeat waveform")+" [no, yes]"));
  Props.push_back(qucs::Property("G", "1", false, QObject::tr("voltage gain")));
  Props.push_back(qucs::Property("T", "0", false, QObject::tr("delay time")));

  rotate();  // fix historical flaw
}

vFile::~vFile()
{
}

Component* vFile::newOne()
{
  return new vFile();
}

Element* vFile::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("File Based Voltage Source");
  BitmapFile = (char *) "vfile";

  if(getNewOne)  return new vFile();
  return 0;
}

// -------------------------------------------------------
QString vFile::getSubcircuitFile()
{
  // construct full filename
  QString FileName = Props.front().Value;
  return misc::properAbsFileName(FileName);
}

// -------------------------------------------------------
QString vFile::netlist()
{
  QString s = Model+":"+Name;

  // output all node names
  for(auto p1 = Ports.begin(); p1 != Ports.end(); ++p1)
    s += " "+p1->getConnection()->Name;   // node names

  // output file properties
  auto p2 = Props.begin();
  s += " "+p2->Name+"=\"{"+getSubcircuitFile()+"}\"";

  // output all remaining properties
  for( ; p2 != Props.end(); ++p2)
    s += " "+p2->Name+"=\""+p2->Value+"\"";

  return s + "\n";
}
