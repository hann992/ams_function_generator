

#ifndef ENCODER_H_
#define ENCODER_H_



// Function Prototypes
void setupInterrupts();

int getEncoderPos();
int getButtonPressed();

int getEncoderTurned();
void setEncoderPos(int pos);
void resetButton();

void resetEncoder();

int getEncoderState();

void setEncoderState(int state);
int resolveEncoderValue(int from, int to, int current);
int resolveMenuSelection(int numOfMenuItems);

#endif /* ENCODER_H_ */