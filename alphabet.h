#ifndef ALPHABET_H
#define ALPHABET_H

#include<QList>
#include "stride.h"

class Alphabet : public QList<Stride>
{
public:
    Alphabet();
    QList<Stride> strides;
    Stride* addNewStride();
    Stride* getCurrentStride();

private:
    Stride* currentStride = 0;

};

#endif // ALPHABET_H
