#include "alphabet.h"

Alphabet::Alphabet()
{

}


Stride* Alphabet::addNewStride() {

    Stride *newStride = new Stride;
    this->strides.append(*newStride);
    this->currentStride = newStride;

    return newStride;
}

Stride* Alphabet::getCurrentStride() {

    return this->currentStride;
}
