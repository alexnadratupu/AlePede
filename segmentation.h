#ifndef SEGMENTATION_H
#define SEGMENTATION_H


#include "imagenpgm.h"
#include "imagenppm.h"

struct color
{
    int r;
    int g;
    int b;
};


typedef struct color color;


class Segmentation
{
    private:
        int distanceGray(int x,
                         int y);
        int distanceColor(color a,
                          color b);
        bool equalsGray(int * centroid,
                        int * oldcentroid,
                        int   size);
        bool equalsColor(color * centroid,
                         color * oldcentroid,
                         int     size);
        color getColor(Image * img,
                       int     x,
                       int     y);

    public:
        Segmentation();

        Image * kmeansPGM(Image * img,
                          int     clusters);
        Image * kmeansPPM(Image * img,
                          int     clusters);
        Image * removeCap(Image * img);
        Image * whiteTissue(Image * img);
        Image * grayTissue(Image * img);
};

#endif // SEGMENTATION_H
