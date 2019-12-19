/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QTimer>
#include "xyseriesiodevice.h"
#include <QtCharts/QXYSeries>
#include <QtCore/QTime>
#include <qdebug.h>

XYSeriesIODevice::XYSeriesIODevice(QXYSeries * series, QObject *parent) :
    QIODevice(parent),
    m_series(series)
{
}

qint64 XYSeriesIODevice::readData(char * data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}
void XYSeriesIODevice::SetRefreshRate(qint32 t_rate)
{
    refre_timer = new QTimer();


    QObject::connect(refre_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));

   // refre_timer->start(t_rate);

}
void XYSeriesIODevice::handleTimeout(void)
{

  qint32 m_y = qrand()%100 -50  ;
  qDebug()<< "data"<< m_y;

  writeData((const char * )&m_y, sizeof(qint32));
}

qint64 XYSeriesIODevice::writeData(const char * data, qint64 maxSize)
{
    qint64 range = 960;
    QVector<QPointF> oldPoints = m_series->pointsVector();
    QVector<QPointF> points;
    int resolution = 8;

    if (oldPoints.count() < range)
    {
        points = m_series->pointsVector();
    } else
    {
        for (int i = maxSize/resolution; i < oldPoints.count(); i++)
        {
            points.append(QPointF(i - maxSize/resolution, oldPoints.at(i).y()));
        }
    }

    qint64 size = points.count();
    float data_samp;
    for (int k = 0; k < maxSize/resolution; k++)
    {
        data_samp = (((unsigned char)data[resolution * k+2] | ((unsigned char)data[resolution * k+3]<<8&0xFF00))  -2048)/2048.0 ;
        points.append(QPointF(k + size,data_samp ));
    }

    m_series->replace(points);
    return maxSize;
}

void XYSeriesIODevice::writeFloatData( double data_samp )
{
  qint64 range = 960;
  QVector<QPointF> oldPoints = m_series->pointsVector();
  QVector<QPointF> points;

  if (oldPoints.count() < range)
  {
      points = m_series->pointsVector();
  } else
  {

      points.append(QPointF(-1, oldPoints.at(0).y()));

  }

  qint64 size = points.count();



  points.append(QPointF( size, data_samp ));

  m_series->replace(points);

}
