#include "genome.h"

#include <iostream>

using namespace std;

genome::genome() {
  // Constructor
  genes = NULL;
  nGenes = 0;
  mRate = 0;
};

genome::~genome() {
  // Destructor
  delocate();
}; 

void genome::allocate(int nGenes) {
  // Take input as how many Pixels to store, 
  // allocates space for them, and initializes all the RGB Pixel values to zero
  if (this->genes != NULL) {
    delocate();
  }
  
  genes = new Pixel[nGenes];
  this->nGenes = nGenes;
}; 

void genome::delocate() {
  // free up the space that is pointed to by genes and sets nGenes to zero
  if (this->genes == NULL) {
    return;
  }
  
  delete[] this->genes;
  this->genes = NULL;
  this->nGenes = 0;
  
}; 


void genome::randomize() {
  // set random values between 0 and 256 for each of the Red, Blue, and Green 
  // variables for each Pixel in the genes array
  for (int i = 0; i < this->nGenes; i++) {
    setRed(i, rand() % 256 + 1);
    setGreen(i, rand() % 256 + 1);
    setBlue(i, rand() % 256 + 1);
  };
}; 

void genome::setRed(int index, int value) {
  // set Red color
  if (0 <= index && index < this->nGenes) {
    this->genes[index].red = value;
  }
}; 

void genome::setGreen(int index, int value) {
  // set Green color
  if (0 <= index && index < this->nGenes) {
    this->genes[index].green = value;
  }
}; 

void genome::setBlue(int index, int value) {
  // set Blue color
  if (0 <= index && index < this->nGenes) {
    this->genes[index].blue = value;
  }
}; 

int genome::getRed(int index) {
  // get Red
  if (0 <= index && index < this->nGenes) {
    return this->genes[index].red;
  }
  return -1;
}; 

int genome::getGreen(int index) {
  // get Green
  if (0 <= index && index < this->nGenes) {
    return this->genes[index].green;
  }
  return -1;
}; 

int genome::getBlue(int index) {
  // get Blue
  if (0 <= index && index < this->nGenes) {
    return this->genes[index].blue;
  }
  return -1;
}; 

void genome::print() {
  cout << "GENOME: " << this->nGenes << " genes" << endl;
   for (int i = 0; i < nGenes; i ++) {
    cout << "(" << this->genes[i].red << "," << this->genes[i].blue  << "," << this->genes[i].green << ")" << endl;
  };
  cout;
};

void genome::set_mRate(double val) {
  if (0 <= val && 1 >= val) {
    this->mRate = val;
  }
};

double genome::get_mRate() {
  return this->mRate;
};

void genome::mutate_gene(int index) {
  double randNum = (double) rand()/RAND_MAX;
  cout << "RandNum: " << randNum << endl;
  if (randNum < this->mRate && index < this->nGenes) {
    setRed(index, rand() % 256 + 1);
    setGreen(index, rand() % 256 + 1);
    setBlue(index, rand() % 256 + 1);
  }
};

void genome::mutate() {
  for (int i = 0; i < nGenes; i ++) {
    mutate_gene(i);
  }
};

double genome::calculate_gene_fitness(int index, Pixel targetPixel) {
  // cout << targetPixel.red << targetPixel.blue << targetPixel.green << endl;
  double redDiff = (double) abs(this->genes[index].red - targetPixel.red) / 255;
  // cout << redDiff << endl;
  double blueDiff = (double) abs(this->genes[index].blue - targetPixel.blue) / 255;
  // cout << blueDiff << endl;
  double greenDiff = (double) abs(this->genes[index].green - targetPixel.green) / 255;
  // cout << greenDiff << endl;
  double res = (redDiff + blueDiff + greenDiff) / 3 * 100;
  return res;
};

double genome::calculate_overall_fitness(Pixel* target, int nPixels) {
  if (this->nGenes != nPixels) {
    return -1;
  }
  double sumDiff = 0;
  for (int i = 0; i < nPixels; i ++) {
    double diff = calculate_gene_fitness(i, target[i]);
    // cout << "Diff " << i << " " << diff << endl;
    sumDiff = sumDiff + diff;
    // cout << sumDiff << endl;
  }
  double res = (double) sumDiff / nPixels;
  return res;
};

void genome::set_pixel(int index, Pixel newPixel) {
  if (0 <= index && index < this->nGenes) {
    if ((0 <= newPixel.red && newPixel.red < 255) && (0 <= newPixel.blue && newPixel.blue < 255) && (0 <= newPixel.green && newPixel.green < 255)) {
      setRed(index, newPixel.red);
      setBlue(index, newPixel.blue);
      setGreen(index, newPixel.green);
    }
  }
};


