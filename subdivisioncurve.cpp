#include "subdivisioncurve.h"

#include <QDebug>
#include <QTextStream>
#include <vector>


/**
 * @brief SubdivisionCurve::SubdivisionCurve Creates a new subdivision curve.
 */
SubdivisionCurve::SubdivisionCurve() {}

/**
 * @brief SubdivisionCurve::presetNet Constructs a control net preset based on a
 * dropdown index.
 * @param preset Index of the preset.
 */
void SubdivisionCurve::presetNet(int preset) {
  netCoords.clear();

  switch (preset) {
    case 0:
      // Pentagon
      netCoords.reserve(5);
      netCoords.append(QVector2D(-0.25f, -0.5f));
      netCoords.append(QVector2D(-0.75f, 0.0f));
      netCoords.append(QVector2D(-0.25f, 0.75f));
      netCoords.append(QVector2D(0.75f, 0.5f));
      netCoords.append(QVector2D(0.5f, -0.75f));
      break;
    case 1:
      // Basis
      netCoords.reserve(9);
      netCoords.append(QVector2D(-1.0f, -0.25f));
      netCoords.append(QVector2D(-0.75f, -0.25f));
      netCoords.append(QVector2D(-0.5f, -0.25f));
      netCoords.append(QVector2D(-0.25f, -0.25f));
      netCoords.append(QVector2D(0.0f, 0.50f));
      netCoords.append(QVector2D(0.25f, -0.25f));
      netCoords.append(QVector2D(0.5f, -0.25f));
      netCoords.append(QVector2D(0.75f, -0.25f));
      netCoords.append(QVector2D(1.0f, -0.25f));
      break;
    case 2:
      // G
      netCoords.reserve(14);
      netCoords.append(QVector2D(0.75f, 0.35f));
      netCoords.append(QVector2D(0.75f, 0.75f));
      netCoords.append(QVector2D(-0.75f, 0.75f));
      netCoords.append(QVector2D(-0.75f, -0.75f));
      netCoords.append(QVector2D(0.75f, -0.75f));
      netCoords.append(QVector2D(0.75f, 0.0f));
      netCoords.append(QVector2D(0.0f, 0.0f));
      netCoords.append(QVector2D(0.0f, -0.2f));
      netCoords.append(QVector2D(0.55f, -0.2f));
      netCoords.append(QVector2D(0.55f, -0.55f));
      netCoords.append(QVector2D(-0.55f, -0.55f));
      netCoords.append(QVector2D(-0.55f, 0.55f));
      netCoords.append(QVector2D(0.55f, 0.55f));
      netCoords.append(QVector2D(0.55f, 0.35f));
      break;
  }
}

/**
 * @brief SubdivisionCurve::presetCurve, This function sets the initial
 * value of the subdivision cure using curve net .
 */
void SubdivisionCurve::presetCurve(){
    curveCoords.clear();

    curveCoords=netCoords;

}

/**
 * @brief SubdivisionCurve::someSubdivideFunction, Finds the index of the point
 * using the odd/even mask using subdivisions.
 * @param steps The integer that defines the level of subdivision.
 */
void SubdivisionCurve::someSubdivideFunction(int steps) {

    stepCount=steps;
    QVector<QVector2D> tempCurveCoords;
    oddMask.clear();
    evenMask.clear();
    curveCoords.clear();

    // Identify odd/even mask using first by size() and then by checking if the first element of
    // odd mask starts with "1"
    if (secondStencil.size() > firstStencil.size() || (firstStencil.size() == secondStencil.size()
                                                       && secondStencil[0] == 1) ) {
        evenMask=firstStencil;
        oddMask=secondStencil;
     }
    else if (firstStencil.size() > secondStencil.size() || (firstStencil.size() == secondStencil.size()
                                                            && firstStencil[0] == 1) ) {
        evenMask=secondStencil;
        oddMask=firstStencil;

     }


    tempCurveCoords=netCoords;
    int lastUpdateIndex=0;
    int sum = 0;
     for(int i = 0; i<firstStencil.size() ; i++){
           sum+=firstStencil[i];
        }

   for (int k = 0; k < steps; k++ )  {
     curveCoords.clear();
     //Set first control point
     curveCoords.append(tempCurveCoords[0]);
     for (int i = 1; i < tempCurveCoords.size(); ++i) {

         // For every i value we will check if the odd/even mask can be implemented
         // Checking for even mask
         if ( i - evenMask.size()  >= -1)
         {
             //Implement even mask
            QVector2D sumEven;
             for (int j = 0; j < evenMask.size(); j++)
             {
                 //Summation of all the points
                 sumEven+= evenMask[j] * tempCurveCoords[i-j];
             }
             // Add the new control point to array
             curveCoords.append(sumEven/sum);
         }
         //Checking for odd mask
         if ( i - oddMask.size()  >= -2 && i <= tempCurveCoords.size()-2)
         {
             //Implement odd mask
             QVector2D sumOdd;
             int temp =-1;
              for (int j = 0; j < oddMask.size(); j++)
              {
                  //Summation of all the points
                  sumOdd+= oddMask[j] * tempCurveCoords[i+temp];
                  temp+=1;
              }
              // Add the new control point to array
              curveCoords.append(sumOdd/sum);

         }
         //Adding last control point
          if (i == tempCurveCoords.size() - 1)
          {
              curveCoords.append(tempCurveCoords[i]);

          }
     }
    tempCurveCoords.clear();
    tempCurveCoords=curveCoords;
    }
}
/**
 * @brief SubdivisionCurve::addPoint Adds a point to the control net.
 * @param p The point to add to the control net.
 */
void SubdivisionCurve::addPoint(QVector2D p) {

  netCoords.append(p);
  // Recalculating the curve
  someSubdivideFunction(stepCount);
  highlightInfluence(highlightPoint);

}

/**
 * @brief SubdivisionCurve::setPointPosition Changes the position of a point in
 * the control net.
 * @param idx The index of the point to update the position of.
 * @param p The new position of the point.
 */
void SubdivisionCurve::setPointPosition(int idx, QVector2D p) {

    netCoords[idx] = p;
  // Recalculating the curve
  someSubdivideFunction(stepCount);
  highlightInfluence(highlightPoint);

}

/**
 * @brief SubdivisionCurve::setPointPosition Changes the position of a point in
 * for the advance feature.
 * @param idx The index of the point to update the position of.
 * @param p The new position of the point.
 */
void SubdivisionCurve::setPointPositionInfluence(int idx, QVector2D p) {

    curveCoords[idx] = p;
  // Recalculating the curve
  highlightInfluence(highlightPoint);

}

/**
 * @brief SubdivisionCurve::removePoint Removes a point from the control net.
 * @param idx The index of the point to remove.
 */
void SubdivisionCurve::removePoint(int idx) {
  netCoords.remove(idx);
  // Recalculating the curve
  someSubdivideFunction(stepCount);
  highlightInfluence(highlightPoint);


}

/**
 * @brief SubdivisionCurve::setMask Set the first and second stencil masks based
 * on the provided string. Note that first/second stencil does not necessarily
 * correspond to odd/even stencil; it might be even/odd!
 * @param stringMask The string mask containing integers.
 */
void SubdivisionCurve::setMask(const QString& stringMask) {
  subdivMask.clear();

  QString trimmedMask = stringMask.trimmed();

  // Convert to sequence of integers
  QTextStream intSeq(&trimmedMask);
  while (!intSeq.atEnd()) {
    int k;
    intSeq >> k;
    subdivMask.append(k);
  }

  firstStencil.clear();
  secondStencil.clear();

  for (int k = 0; k < subdivMask.size(); ++k) {
    if (k % 2) {
      firstStencil.append(subdivMask[k]);
    } else {
      secondStencil.append(subdivMask[k]);
    }
  }
}

/**
 * @brief SubdivisionCurve::findClosest Finds the index of the closest point in
 * the control net to the provided point.
 * @param p The point to find the closest point to.
 * @param maxDist The maximum distance a point and the provided point can have.
 * Is a value between 0 and 1.
 * @return The index of the closest point to the provided point. Returns -1 if
 * no point was found within the maximum distance.
 */
int SubdivisionCurve::findClosest(const QVector2D& p, const float maxDist) {
  int ptIndex = -1;
  float currentDist, minDist = 4;

  for (int k = 0; k < netCoords.size(); k++) {
    currentDist = netCoords[k].distanceToPoint(p);
    if (currentDist < minDist) {
      minDist = currentDist;
      ptIndex = k;
    }
  }
  if (minDist >= maxDist) {
    return -1;
  }

  return ptIndex;
}

/**
 * @brief SubdivisionCurve::findClosestInfluence Finds the index of the closest point in
 * the influence to the provided point.
 * @param p The point to find the closest point to.
 * @param maxDist The maximum distance a point and the provided point can have.
 * Is a value between 0 and 1.
 * @return The index of the closest point to the provided point. Returns -1 if
 * no point was found within the maximum distance.
 */
int SubdivisionCurve::findClosestInfluence(const QVector2D& p, const float maxDist) {
  int ptIndex = -1;
  float currentDist, minDist = 4;

  for (int k = 0; k < curveCoords.size(); k++) {
    currentDist = curveCoords[k].distanceToPoint(p);
    if (currentDist < minDist) {
      minDist = currentDist;
      ptIndex = k;
    }
  }
  if (minDist >= maxDist) {
    return -1;
  }

  return ptIndex;
}
/**
 * @brief SubdivisionCurve::updateHighlightedPoint: Used to update the
 * value of selected point(settings->selectedPointSub). The function updates
 * the class variable highlightPoint.
 * @param point Index of the new point selected on subdivision curve.
 */
void SubdivisionCurve::updateHighlightedPoint(int point){
    highlightPoint=point;
}
/**
 * @brief SubdivisionCurve::highlightInfluence Finds the index of the points
 * that are influenced by the selected point. This function works when one point
 * is selected on the subdivision curve.
 * @param point Index of the point selected on subdivision curve.
 */
void SubdivisionCurve::highlightInfluence(int point){

    if (point > -1 && curveCoords.size() >2){
        advanceCoords.clear();

        // The control point is not at the boundary of subdivision curve
        if (point !=0 && point <= (curveCoords.size()-2)){
            advanceCoords.append(curveCoords[point-1]);
            advanceCoords.append(curveCoords[point]);
            advanceCoords.append(curveCoords[point+1]);
        }
        else if (point == 0){
            advanceCoords.append(curveCoords[point]);
            advanceCoords.append(curveCoords[point+1]);

        }
        else if (point == (curveCoords.size()-1)){
            advanceCoords.append(curveCoords[point]);
            advanceCoords.append(curveCoords[point-1]);

        }
    }

}
