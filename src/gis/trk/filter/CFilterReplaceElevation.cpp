/**********************************************************************************************
    Copyright (C) 2014 Oliver Eichler oliver.eichler@gmx.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

**********************************************************************************************/

#include "canvas/CCanvas.h"
#include "gis/trk/CGisItemTrk.h"
#include "gis/trk/filter/CFilterReplaceElevation.h"

CFilterReplaceElevation::CFilterReplaceElevation(CGisItemTrk &trk, QWidget *parent)
    : QWidget(parent)
    , trk(trk)
{
    setupUi(this);

    connect(toolApply, &QToolButton::clicked, this, &CFilterReplaceElevation::slotApply);
}

void CFilterReplaceElevation::slotApply()
{
    CCanvas::setOverrideCursor(Qt::WaitCursor,"CFilterReplaceElevation");
    trk.filterReplaceElevation();
    CCanvas::restoreOverrideCursor("CFilterReplaceElevation");
}
