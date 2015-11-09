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

#include "plot/CPlotAxisTime.h"
#include "plot/CPlotDistance.h"

CPlotDistance::CPlotDistance(QWidget *parent)
    : IPlot(0, CPlotData::eAxisTime, eModeNormal, parent)
{
}

CPlotDistance::~CPlotDistance()
{
}

void CPlotDistance::setTrack(CGisItemTrk * track)
{
    trk = track;
    trk->registerPlot(this);

    updateData();
}


void CPlotDistance::updateData()
{
    if(isHidden())
    {
        return;
    }

    clear();
    if(trk->getTotalElapsedSeconds() == 0)
    {
        resetZoom();
        update();
        return;
    }

    if(mode == eModeIcon)
    {
        setXLabel(trk->getName());
        setYLabel("");
    }
    else
    {
        setXLabel(tr("time"));
        setYLabel(tr("distance. [%1]").arg(IUnit::self().baseunit));
    }

    QPolygonF lineDist;

    qreal basefactor = IUnit::self().basefactor;
    const CGisItemTrk::trk_t& t = trk->getTrackData();

    foreach (const CGisItemTrk::trkseg_t& seg, t.segs)
    {
        foreach(const CGisItemTrk::trkpt_t& trkpt, seg.pts)
        {
            if(trkpt.flags & CGisItemTrk::trkpt_t::eHidden)
            {
                continue;
            }

            if(trkpt.distance != NOFLOAT)
            {
                lineDist << QPointF((qreal)trkpt.time.toTime_t(), trkpt.distance * basefactor);
            }
        }
    }


    newLine(lineDist, "GPS");
    setLimits();
    resetZoom();
}

void CPlotDistance::setMouseFocus(const CGisItemTrk::trkpt_t * ptMouseMove)
{
    if(ptMouseMove == 0)
    {
        if(posMouse != NOPOINT)
        {
            posMouse = NOPOINT;
            needsRedraw = true;
        }
    }
    else
    {
        if(posMouse == NOPOINT)
        {
            needsRedraw = true;
        }

        posMouse.rx() = left  + data->x().val2pt(ptMouseMove->time.toTime_t());
        posMouse.ry() = top  +  data->y().val2pt(ptMouseMove->distance);
    }
    update();
}


