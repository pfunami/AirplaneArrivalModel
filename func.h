//
// Created on 2018/12/12.
//

#ifndef PROGRAM_FUNC_H
#define PROGRAM_FUNC_H

double toRad(double r);

double toDot(double r);

double toKm(double r);

void TimePlus();

void TerritoryDef(double x, double X, double Y, double alpha, double height, double v, double *front,
                  double *behind, double *right, double *left, double *over, double *under);

void CheckTerritory(struct _State *checkPlane, struct _State *others, int i, int *area);

void ChangeWaitOrder(struct _Memory *Memory, struct _State *Airplane);

#endif //PROGRAM_FUNC_H
