#ifndef SUBDIVISIONCURVE_H
#define SUBDIVISIONCURVE_H

#include <QString>
#include <QVector2D>
#include <QVector>
#include <settings.h>

/**
 * @brief The SubdivisionCurve class contains the data of a 2D subdivision
 * curve.
 */
class SubdivisionCurve {
 public:
  SubdivisionCurve();

  inline QVector<QVector2D> getNetCoords() { return netCoords; }
  inline QVector<QVector2D> getCurveCoords() { return curveCoords; }
  inline QVector<QVector2D> getAdvanceCoords() { return advanceCoords; }



  void setMask(const QString& stringMask);
  void presetNet(int preset);
  void presetCurve();

  int findClosest(const QVector2D& p, const float maxDist);
  int findClosestInfluence(const QVector2D& p, const float maxDist);


  void addPoint(QVector2D p);
  void someSubdivideFunction(int steps);
  void highlightInfluence(int point);
  void updateHighlightedPoint(int point);
  void setPointPosition(int idx, QVector2D p);
  void setPointPositionInfluence(int idx, QVector2D p);
  void removePoint(int idx);


 private:
  QVector<int> subdivMask, firstStencil, secondStencil, oddMask, evenMask;
  int stepCount;
  int highlightPoint;

  QVector<QVector2D> curveCoords;
  Settings settings;

  QVector<QVector2D> netCoords;
  QVector<QVector2D> advanceCoords;

};

#endif  // SUBDIVISIONCURVE_H
