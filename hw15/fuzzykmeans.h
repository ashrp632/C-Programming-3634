
#ifndef fkm_h
#define fkm_h

typedef struct{
    double x,y;
} vec;

// This function returns the Euclidean distance between v0 and v1.
double dist(vec v0, vec v1);

// This function returns the weight between one vector "vi" and one center.
// Weight is the dissimilarity function described in the assignment instructions.
// Notice that calculating weight requires knowledge of every cluster center.
// "vi" is a data point
// "centers" is an array of cluster centesr
// "j" is the center for which you want to return the weight
// "k" is the number of centers
double weight(vec vi, vec* centers, int j, int k);

// This function overwrites memory in the "centers" array instead of returning anything.
// The cluster centers are updated with one iteration of fuzzy Lloyd's algorithm.
// "data" is an array of length "n" (coordinates of data points).
// "centers" is an array of length "k" (coordinates of cluster centers).
void fuzzykmeans(vec* data, int n, vec* centers, int k);

#endif

