#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>
// Length of the accelerator input sequence expected by the model
#define SEQUENCE_LENGTH         30
#define ACCELEROMETER_CHANNELS   3

// Inference it triggered by a periodic timer, this configuration is the time
// between each trigger
#define INFERENCE_PERIOD_MS    250

//Anomaly detection parameters
#define THRESHOLD 1.304539
#define SCALE 0.252201

#define MEAN_X -0.00026546
#define MEAN_Y 0.00064621
#define MEAN_Z 0.00027006
#define STD_X 11.74652882
#define STD_Y 6.16848353
#define STD_Z 5.39212678
#define SIGMOID(x) 1.0 / (1.0 + exp(-(x - THRESHOLD) / SCALE))

#endif // CONSTANTS_H
